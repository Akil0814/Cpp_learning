#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
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

    void AddBidirectionalEdge(const string& from, const string& to, int weight)
    {
        const int u = city_id_.at(from);
        const int v = city_id_.at(to);
        adjacency_[u].push_back({u, v, weight});
        adjacency_[v].push_back({v, u, weight});
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
        vector<bool> visited(n, false);
        unordered_set<long long> classified_edges;

        function<void(int)> dfs = [&](int u)
        {
            visited[u] = true;

            for (const DirectedEdge& edge : adjacency_[u])
            {
                const long long key = EdgeKey(edge.from, edge.to);
                if (!classified_edges.insert(key).second)
                {
                    continue;
                }

                const int v = edge.to;
                if (!visited[v])
                {
                    result.discovery.push_back(edge);
                    result.discovery_total_distance += edge.weight;
                    dfs(v);
                }
                else
                {
                    result.back.push_back(edge);
                }
            }
        };

        dfs(start);
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

    bool IsStronglyConnected() const
    {
        const int n = VertexCount();
        if (n == 0)
        {
            return true;
        }

        auto dfs_reach = [&](const vector<vector<DirectedEdge>>& graph, int start)
        {
            vector<bool> visited(n, false);
            function<void(int)> dfs = [&](int u)
            {
                visited[u] = true;
                for (const DirectedEdge& edge : graph[u])
                {
                    if (!visited[edge.to])
                    {
                        dfs(edge.to);
                    }
                }
            };
            dfs(start);
            return visited;
        };

        const vector<bool> from_zero = dfs_reach(adjacency_, 0);
        for (bool ok : from_zero)
        {
            if (!ok)
            {
                return false;
            }
        }

        vector<vector<DirectedEdge>> reversed(n);
        for (int u = 0; u < n; ++u)
        {
            for (const DirectedEdge& edge : adjacency_[u])
            {
                reversed[edge.to].push_back({edge.to, u, edge.weight});
            }
        }

        const vector<bool> to_zero = dfs_reach(reversed, 0);
        for (bool ok : to_zero)
        {
            if (!ok)
            {
                return false;
            }
        }
        return true;
    }

   private:
    vector<string> city_names_;
    unordered_map<string, int> city_id_;
    vector<vector<DirectedEdge>> adjacency_;

    static long long EdgeKey(int a, int b)
    {
        const int x = min(a, b);
        const int y = max(a, b);
        return (static_cast<long long>(x) << 32) | static_cast<unsigned int>(y);
    }
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

    const vector<tuple<string, string, int>> edges = {
        {"Seattle", "San Francisco", 807}, {"Seattle", "Denver", 1331},
        {"Seattle", "Chicago", 2097},      {"San Francisco", "Los Angeles", 381},
        {"San Francisco", "Denver", 1267}, {"Los Angeles", "Denver", 1015},
        {"Los Angeles", "Kansas City", 1663},
        {"Los Angeles", "Dallas", 1435},
        {"Denver", "Chicago", 1003},
        {"Denver", "Kansas City", 599},
        {"Chicago", "Kansas City", 533},
        {"Chicago", "New York", 787},
        {"Chicago", "Boston", 983},
        {"Kansas City", "Dallas", 496},
        {"Kansas City", "New York", 1260},
        {"Kansas City", "Atlanta", 864},
        {"Dallas", "Houston", 239},
        {"Dallas", "Atlanta", 781},
        {"Houston", "Atlanta", 810},
        {"Houston", "Miami", 1187},
        {"Atlanta", "Miami", 661},
        {"Atlanta", "New York", 888},
        {"New York", "Boston", 214},
    };

    for (const auto& [from, to, weight] : edges)
    {
        graph.AddBidirectionalEdge(from, to, weight);
    }
    graph.Finalize();

    const int start = graph.GetCityId("Denver");

    const ClassifiedEdges dfs_edges = graph.ClassifyDfsFrom(start);
    const ClassifiedEdges bfs_edges = graph.ClassifyBfsFrom(start);

    PrintPartResult(graph, "Part A - DFS starting at Denver", dfs_edges);
    cout << "\n";
    PrintPartResult(graph, "Part B - BFS starting at Denver", bfs_edges);
    cout << "\n\nPart C - Strong Connectivity\n";
    if (graph.IsStronglyConnected())
    {
        cout << "The map in the PDF is drawn as an undirected graph, so the most precise answer is that it is connected, not \"strongly connected.\"\n";
        cout << "If every road is treated as two directed edges, one in each direction, then it is strongly connected because every city can reach every other city.\n";
    }
    else
    {
        cout << "No. At least one city cannot be reached from another in the directed graph.\n";
    }

    return 0;
}
