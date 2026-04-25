#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

class DisjointSet {
   public:
    explicit DisjointSet(int n) : parent_(n), rank_(n, 0)
    {
        iota(parent_.begin(), parent_.end(), 0);
    }

    int Find(int x)
    {
        if (parent_[x] != x)
        {
            parent_[x] = Find(parent_[x]);
        }
        return parent_[x];
    }

    bool Union(int a, int b)
    {
        int root_a = Find(a);
        int root_b = Find(b);
        if (root_a == root_b)
        {
            return false;
        }

        if (rank_[root_a] < rank_[root_b])
        {
            swap(root_a, root_b);
        }
        parent_[root_b] = root_a;
        if (rank_[root_a] == rank_[root_b])
        {
            ++rank_[root_a];
        }
        return true;
    }

   private:
    vector<int> parent_;
    vector<int> rank_;
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

    void AddUndirectedEdge(const string& from, const string& to, int weight)
    {
        const int u = city_id_.at(from);
        const int v = city_id_.at(to);

        adjacency_[u].push_back({u, v, weight});
        adjacency_[v].push_back({v, u, weight});
        edges_.push_back({u, v, weight});
    }

    int GetCityId(const string& name) const { return city_id_.at(name); }

    const string& GetCityName(int id) const { return city_names_[id]; }

    int VertexCount() const { return static_cast<int>(city_names_.size()); }

    vector<int> Dijkstra(int start, vector<int>& previous) const
    {
        const int n = VertexCount();
        const int infinity = numeric_limits<int>::max();
        vector<int> distance(n, infinity);
        previous.assign(n, -1);

        using QueueItem = pair<int, int>;  // distance, vertex
        priority_queue<QueueItem, vector<QueueItem>, greater<QueueItem>> pq;

        distance[start] = 0;
        pq.push({0, start});

        while (!pq.empty())
        {
            const auto [current_distance, u] = pq.top();
            pq.pop();

            if (current_distance != distance[u])
            {
                continue;
            }

            for (const Edge& edge : adjacency_[u])
            {
                const int v = edge.to;
                if (distance[u] + edge.weight < distance[v])
                {
                    distance[v] = distance[u] + edge.weight;
                    previous[v] = u;
                    pq.push({distance[v], v});
                }
            }
        }

        return distance;
    }

    vector<Edge> KruskalMst(int& total_weight) const
    {
        vector<Edge> sorted_edges = edges_;
        sort(sorted_edges.begin(), sorted_edges.end(), [&](const Edge& a, const Edge& b)
        {
            if (a.weight != b.weight)
            {
                return a.weight < b.weight;
            }
            if (city_names_[a.from] != city_names_[b.from])
            {
                return city_names_[a.from] < city_names_[b.from];
            }
            return city_names_[a.to] < city_names_[b.to];
        });

        DisjointSet sets(VertexCount());
        vector<Edge> mst_edges;
        total_weight = 0;

        for (const Edge& edge : sorted_edges)
        {
            if (sets.Union(edge.from, edge.to))
            {
                mst_edges.push_back(edge);
                total_weight += edge.weight;
            }
        }

        return mst_edges;
    }

   private:
    vector<string> city_names_;
    unordered_map<string, int> city_id_;
    vector<vector<Edge>> adjacency_;
    vector<Edge> edges_;
};

vector<int> BuildPath(int destination, const vector<int>& previous)
{
    vector<int> path;
    for (int current = destination; current != -1; current = previous[current])
    {
        path.push_back(current);
    }
    reverse(path.begin(), path.end());
    return path;
}

void PrintPath(const Graph& graph, const vector<int>& path)
{
    for (int i = 0; i < static_cast<int>(path.size()); ++i)
    {
        if (i > 0)
        {
            cout << " -> ";
        }
        cout << graph.GetCityName(path[i]);
    }
}

int main()
{
    Graph graph({"Seattle", "San Francisco", "Los Angeles", "Denver", "Chicago",
                 "Kansas City", "Dallas", "Houston", "Atlanta", "Miami",
                 "New York", "Boston"});

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
        {"Houston", "Dallas", 239},
        {"Houston", "Atlanta", 810},
        {"Miami", "Houston", 1187},
        {"Atlanta", "Miami", 661},
        {"New York", "Atlanta", 888},
        {"New York", "Chicago", 787},
        {"Boston", "New York", 214},
    };

    for (const auto& [from, to, weight] : edges)
    {
        graph.AddUndirectedEdge(from, to, weight);
    }

    const int start = graph.GetCityId("Kansas City");
    vector<int> previous;
    const vector<int> distances = graph.Dijkstra(start, previous);

    cout << "Part 1 - Dijkstra shortest paths from Kansas City\n";
    for (int city = 0; city < graph.VertexCount(); ++city)
    {
        cout << graph.GetCityName(city) << ": ";
        PrintPath(graph, BuildPath(city, previous));
        cout << " (" << distances[city] << " miles)\n";
    }

    int mst_total = 0;
    const vector<Edge> mst_edges = graph.KruskalMst(mst_total);

    cout << "\nPart 2 - Minimum Spanning Tree\n";
    for (const Edge& edge : mst_edges)
    {
        cout << graph.GetCityName(edge.from) << " - " << graph.GetCityName(edge.to)
             << " (" << edge.weight << " miles)\n";
    }
    cout << "Total mileage: " << mst_total << "\n";

    return 0;
}
