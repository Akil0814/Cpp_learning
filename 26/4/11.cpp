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

struct Edge {
    int to;
    int weight;
};

struct ClassifiedEdge {
    int from;
    int to;
    int weight;
};

struct TraversalResult {
    vector<ClassifiedEdge> discovery_edges;
    vector<ClassifiedEdge> non_tree_edges;
    int discovery_total_distance = 0;
};

class Graph {
   public:
    explicit Graph(vector<string> city_names)
        : city_names_(move(city_names)),
          adjacency_list_(city_names_.size()),
          adjacency_matrix_(city_names_.size(), vector<int>(city_names_.size(), kInf))
    {
        for (int i = 0; i < static_cast<int>(city_names_.size()); ++i)
        {
            city_id_[city_names_[i]] = i;
            adjacency_matrix_[i][i] = 0;
        }
    }

    void AddUndirectedEdge(const string& from, const string& to, int weight)
    {
        int u = city_id_.at(from);
        int v = city_id_.at(to);

        adjacency_list_[u].push_back({v, weight});
        adjacency_list_[v].push_back({u, weight});

        adjacency_matrix_[u][v] = weight;
        adjacency_matrix_[v][u] = weight;
    }

    void Finalize()
    {
        for (auto& neighbors : adjacency_list_)
        {
            sort(neighbors.begin(), neighbors.end(), [&](const Edge& a, const Edge& b) {
                if (a.weight != b.weight) {
                    return a.weight < b.weight;
                }
                return city_names_[a.to] < city_names_[b.to];
            });
        }
    }

    int GetCityId(const string& city) const { return city_id_.at(city); }

    const string& GetCityName(int city_id) const { return city_names_[city_id]; }

    TraversalResult DfsWithAdjacencyList(int start) const
    {
        TraversalResult result;
        vector<bool> visited(city_names_.size(), false);
        unordered_set<long long> classified;

        function<void(int, int)> dfs = [&](int u, int parent)
        {
            visited[u] = true;
            for (const auto& edge : adjacency_list_[u])
            {
                int v = edge.to;
                int w = edge.weight;
                long long key = EdgeKey(u, v);

                if (!visited[v])
                {
                    if (classified.insert(key).second)
                    {
                        result.discovery_edges.push_back({u, v, w});
                        result.discovery_total_distance += w;
                    }
                    dfs(v, u);
                } else if (v != parent)
                {
                    if (classified.insert(key).second)
                        result.non_tree_edges.push_back({u, v, w});
                }
            }
        };

        dfs(start, -1);
        return result;
    }

    TraversalResult BfsWithAdjacencyMatrix(int start) const
    {
        TraversalResult result;
        vector<bool> visited(city_names_.size(), false);
        unordered_set<long long> classified;
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            vector<Edge> neighbors = GetSortedMatrixNeighbors(u);
            for (const auto& edge : neighbors)
            {
                int v = edge.to;
                int w = edge.weight;
                long long key = EdgeKey(u, v);

                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                    if (classified.insert(key).second)
                    {
                        result.discovery_edges.push_back({u, v, w});
                        result.discovery_total_distance += w;
                    }
                }
                else if (classified.insert(key).second)
                {
                    result.non_tree_edges.push_back({u, v, w});
                }
            }
        }

        return result;
    }

   private:
    static constexpr int kInf = 1'000'000'000;

    vector<string> city_names_;
    unordered_map<string, int> city_id_;
    vector<vector<Edge>> adjacency_list_;
    vector<vector<int>> adjacency_matrix_;

    static long long EdgeKey(int a, int b)
    {
        int x = min(a, b);
        int y = max(a, b);
        return (static_cast<long long>(x) << 32) | static_cast<unsigned int>(y);
    }

    vector<Edge> GetSortedMatrixNeighbors(int u) const
    {
        vector<Edge> neighbors;
        for (int v = 0; v < static_cast<int>(city_names_.size()); ++v)
        {
            if (v != u && adjacency_matrix_[u][v] < kInf)
            {
                neighbors.push_back({v, adjacency_matrix_[u][v]});
            }
        }

        sort(neighbors.begin(), neighbors.end(), [&](const Edge& a, const Edge& b)
        {
            if (a.weight != b.weight)
            {
                return a.weight < b.weight;
            }
            return city_names_[a.to] < city_names_[b.to];
        });
        return neighbors;
    }
};

void PrintTraversalResult(const Graph& graph, const string& part_title, const string& non_tree_label,
                          int start, const TraversalResult& result)
{
    cout << part_title << ", start: " << graph.GetCityName(start) << "\n";
    cout << "Discovery edges:\n";
    for (const auto& edge : result.discovery_edges) {
        cout << graph.GetCityName(edge.from) << " -> " << graph.GetCityName(edge.to) << "\n";
    }

    cout << non_tree_label << ":\n";
    for (const auto& edge : result.non_tree_edges) {
        cout << graph.GetCityName(edge.from) << " -> " << graph.GetCityName(edge.to) << "\n";
    }

    cout << "Total distance on discovery edges: " << result.discovery_total_distance << "\n";
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
        graph.AddUndirectedEdge(from, to, weight);
    }
    graph.Finalize();

    const int start = graph.GetCityId("Dallas");
    const TraversalResult dfs_result = graph.DfsWithAdjacencyList(start);
    const TraversalResult bfs_result = graph.BfsWithAdjacencyMatrix(start);

    PrintTraversalResult(graph, "Part A - DFS (Adjacency List)", "Back edges", start, dfs_result);
    cout << "\n";
    PrintTraversalResult(graph, "Part B - BFS (Adjacency Matrix)", "Cross edges", start, bfs_result);

    return 0;
}
