#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct DirectedEdge {
    int from;
    int to;
    int weight;
};

struct ClassifiedEdges {
    vector<DirectedEdge> discovery;
    vector<DirectedEdge> forward;
    vector<DirectedEdge> back;
    vector<DirectedEdge> cross;
    int discovery_total_distance = 0;
};

class Graph {
   public:
    explicit Graph(vector<string> city_names)
        : city_names_(move(city_names)), adjacency_(city_names_.size())
    {
        for (int i = 0; i < static_cast<int>(city_names_.size()); ++i)
        {
            city_id_[city_names_[i]] = i;
        }
    }

    void AddDirectedEdge(const string& from, const string& to, int weight)
    {
        const int u = city_id_.at(from);
        const int v = city_id_.at(to);

        adjacency_[u].push_back({u, v, weight});
    }

    void Finalize()
    {
        for (auto& edges : adjacency_)
        {
            sort(edges.begin(), edges.end(), [&](const DirectedEdge& a, const DirectedEdge& b)
            {
                if (a.weight != b.weight)
                {
                    return a.weight < b.weight;
                }
                return city_names_[a.to] < city_names_[b.to];
            });
        }
    }

    int GetCityId(const string& name) const { return city_id_.at(name); }

    const string& GetCityName(int id) const { return city_names_[id]; }

    int VertexCount() const { return static_cast<int>(city_names_.size()); }

    const vector<DirectedEdge>& Neighbors(int id) const { return adjacency_[id]; }

    ClassifiedEdges ClassifyDfsFrom(int start) const
    {
        ClassifiedEdges result;
        const int n = VertexCount();
        vector<int> color(n, 0);  // 0=white, 1=gray, 2=black
        vector<int> tin(n, -1);
        vector<int> tout(n, -1);
        vector<DirectedEdge> black_target_edges;
        int timer = 0;

        function<void(int)> dfs = [&](int u)
        {
            color[u] = 1;
            tin[u] = ++timer;

            for (const DirectedEdge& edge : adjacency_[u])
            {
                const int v = edge.to;
                if (color[v] == 0)
                {
                    result.discovery.push_back(edge);
                    result.discovery_total_distance += edge.weight;
                    dfs(v);
                }
                else if (color[v] == 1)
                {
                    result.back.push_back(edge);
                }
                else
                {
                    black_target_edges.push_back(edge);
                }
            }

            color[u] = 2;
            tout[u] = ++timer;
        };

        dfs(start);

        for (const DirectedEdge& edge : black_target_edges)
        {
            if (tin[edge.from] < tin[edge.to] && tout[edge.to] < tout[edge.from])
            {
                result.forward.push_back(edge);
            }
            else
            {
                result.cross.push_back(edge);
            }
        }

        return result;
    }

    ClassifiedEdges ClassifyBfsFrom(int start) const
    {
        ClassifiedEdges result;
        const int n = VertexCount();
        vector<bool> visited(n, false);
        vector<int> parent(n, -1);
        vector<int> level(n, -1);
        queue<int> q;

        visited[start] = true;
        level[start] = 0;
        q.push(start);

        while (!q.empty())
        {
            const int u = q.front();
            q.pop();

            for (const DirectedEdge& edge : adjacency_[u])
            {
                const int v = edge.to;
                if (!visited[v])
                {
                    visited[v] = true;
                    parent[v] = u;
                    level[v] = level[u] + 1;
                    q.push(v);

                    result.discovery.push_back(edge);
                    result.discovery_total_distance += edge.weight;
                }
            }
        }

        vector<vector<int>> tree_children(n);
        for (int v = 0; v < n; ++v)
        {
            if (parent[v] != -1)
            {
                tree_children[parent[v]].push_back(v);
            }
        }

        vector<int> tin(n, -1), tout(n, -1);
        int timer = 0;
        function<void(int)> mark_tree_time = [&](int u)
        {
            tin[u] = ++timer;
            for (int child : tree_children[u])
            {
                mark_tree_time(child);
            }
            tout[u] = ++timer;
        };
        mark_tree_time(start);

        auto is_ancestor = [&](int a, int b)
        {
            if (a < 0 || b < 0 || tin[a] == -1 || tin[b] == -1)
            {
                return false;
            }
            return tin[a] <= tin[b] && tout[b] <= tout[a];
        };

        for (int u = 0; u < n; ++u)
        {
            if (!visited[u])
            {
                continue;
            }

            for (const DirectedEdge& edge : adjacency_[u])
            {
                const int v = edge.to;
                if (!visited[v])
                {
                    continue;
                }

                if (parent[v] == u)
                {
                    continue; // already counted as discovery edge
                }

                if (is_ancestor(v, u))
                {
                    result.back.push_back(edge);
                }
                else if (is_ancestor(u, v))
                {
                    result.forward.push_back(edge);
                }
                else
                {
                    result.cross.push_back(edge);
                }
            }
        }

        return result;
    }

    int ReachableCountFrom(int start) const
    {
        const int n = VertexCount();
        vector<bool> visited(n, false);
        function<void(int)> dfs = [&](int u)
        {
            visited[u] = true;
            for (const DirectedEdge& edge : adjacency_[u])
            {
                if (!visited[edge.to])
                {
                    dfs(edge.to);
                }
            }
        };

        dfs(start);

        int reachable_count = 0;
        for (bool ok : visited)
        {
            if (ok)
            {
                ++reachable_count;
            }
        }
        return reachable_count;
    }

   private:
    vector<string> city_names_;
    unordered_map<string, int> city_id_;
    vector<vector<DirectedEdge>> adjacency_;

};

void PrintEdgeGroup(const Graph& graph, const string& label, const vector<DirectedEdge>& edges)
{
    cout << label << ":\n";
    if (edges.empty())
    {
        cout << "(none)\n";
        return;
    }

    for (const DirectedEdge& edge : edges)
    {
        cout << graph.GetCityName(edge.from) << " -> " << graph.GetCityName(edge.to) << "\n";
    }
}

void PrintPartResult(const Graph& graph, const string& title, const ClassifiedEdges& edges)
{
    cout << title << "\n";
    PrintEdgeGroup(graph, "Discovery edges", edges.discovery);
    PrintEdgeGroup(graph, "Forward edges", edges.forward);
    PrintEdgeGroup(graph, "Back edges", edges.back);
    PrintEdgeGroup(graph, "Cross edges", edges.cross);
    cout << "Total distance travelled (discovery edges): " << edges.discovery_total_distance << "\n";
}

int main()
{
    Graph graph({"Seattle", "San Francisco", "Los Angeles", "Denver",   "Chicago",
                 "Kansas City", "Dallas",    "Houston",     "Atlanta",  "Miami",
                 "New York",    "Boston"});
    Graph reverse_graph({"Seattle", "San Francisco", "Los Angeles", "Denver",   "Chicago",
                         "Kansas City", "Dallas",    "Houston",     "Atlanta",  "Miami",
                         "New York",    "Boston"});


    const vector<tuple<string, string, int>> edges = {
        {"Seattle", "San Francisco", 807},
        {"Seattle", "Denver", 1331},

        {"San Francisco", "Los Angeles", 381},

        {"Los Angeles", "Denver", 1015},

        {"Denver", "Chicago", 1003},
        {"Denver", "San Francisco", 1267},

        {"Chicago", "Seattle", 2097},
        {"Chicago", "Boston", 983},

        {"Kansas City", "Denver", 599},
        {"Kansas City", "Chicago", 533},
        {"Kansas City", "Los Angeles", 1663},
        {"Kansas City", "Atlanta", 864},
        {"Kansas City", "New York", 1260},

        {"Dallas", "Atlanta", 781},
        {"Dallas", "Kansas City", 496},
        {"Dallas", "Los Angeles", 1435},

        {"Houston","Dallas", 239},
        {"Houston", "Atlanta", 810},

        {"Miami","Houston",  1187},

        {"Atlanta", "Miami", 661},

        {"New York","Atlanta", 888},
        {"New York", "Chicago", 787},

        {"Boston", "New York", 214},
    };

    for (const auto& [from, to, weight] : edges)
    {
        graph.AddDirectedEdge(from, to, weight);
        reverse_graph.AddDirectedEdge(to, from, weight);
    }
    graph.Finalize();
    reverse_graph.Finalize();

    const int start = graph.GetCityId("Denver");

    const ClassifiedEdges dfs_edges = graph.ClassifyDfsFrom(start);
    const ClassifiedEdges bfs_edges = graph.ClassifyBfsFrom(start);
    const ClassifiedEdges reversed_dfs_edges = reverse_graph.ClassifyDfsFrom(start);

    PrintPartResult(graph, "Part A - DFS starting at Denver", dfs_edges);
    cout << "\n";
    PrintPartResult(graph, "Part B - BFS starting at Denver", bfs_edges);
    cout << "\n\nPart C - Strong Connectivity\n";
    const bool original_reaches_all = graph.ReachableCountFrom(start) == graph.VertexCount();
    const bool reverse_reaches_all = reverse_graph.ReachableCountFrom(start) == reverse_graph.VertexCount();
    if (original_reaches_all && reverse_reaches_all)
    {
        cout << "Yes. DFS from Denver reaches every city in the original graph, and DFS from Denver also reaches every city in the reversed graph.\n";
    }
    else
    {
        cout << "No. Either the original graph or the reversed graph cannot reach every city from Denver, so the graph is not strongly connected.\n";
    }
    cout << "\n";
    PrintPartResult(reverse_graph, "Reversed Graph - DFS starting at Denver", reversed_dfs_edges);

    return 0;
}
