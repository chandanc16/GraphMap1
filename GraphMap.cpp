#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <climits>  // For INT_MAX
using namespace std;

typedef pair<int, int> pii;  // pair of (cityIndex, distance)

class GraphMap {
    map<string, int> cityToIndex;
    vector<string> indexToCity;
    vector<vector<pii> > adjList;  // note the space between > >
    int cityCount;

public:
    GraphMap() : cityCount(0) {}

    // Add a city, return its index
    int addCity(const string& city) {
        if (cityToIndex.find(city) == cityToIndex.end()) {
            cityToIndex[city] = cityCount++;
            indexToCity.push_back(city);
            adjList.push_back(vector<pii>());  // add empty adjacency list for new city
        }
        return cityToIndex[city];
    }

    // Add a road (edge) from city u to city v with given distance
    void addRoad(const string& cityU, const string& cityV, int distance) {
        int u = addCity(cityU);
        int v = addCity(cityV);
        adjList[u].push_back(make_pair(v, distance));
        // If undirected graph, also add the reverse edge:
        // adjList[v].push_back(make_pair(u, distance));
    }

    // Dijkstra's algorithm to find shortest paths from source city
    void shortestPaths(const string& sourceCity) {
        if (cityToIndex.find(sourceCity) == cityToIndex.end()) {
            cout << "Source city not found!\n";
            return;
        }
        int src = cityToIndex[sourceCity];

        vector<int> dist(cityCount, INT_MAX);
        dist[src] = 0;

        // Min-heap priority queue: (distance, cityIndex)
        priority_queue< pii, vector<pii>, greater<pii> > pq;
        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            pii top = pq.top();
            pq.pop();

            int uDist = top.first;
            int u = top.second;

            if (uDist > dist[u])
                continue;

            // Iterate over neighbors
            for (vector<pii>::iterator it = adjList[u].begin(); it != adjList[u].end(); ++it) {
                int v = it->first;
                int weight = it->second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        // Print shortest distances
        cout << "Shortest distances from " << sourceCity << ":\n";
        for (int i = 0; i < cityCount; i++) {
            cout << indexToCity[i] << " : ";
            if (dist[i] == INT_MAX)
                cout << "Unreachable\n";
            else
                cout << dist[i] << "\n";
        }
    }
};

int main() {
    GraphMap graph;

    // Example roads
    graph.addRoad("A", "B", 5);
    graph.addRoad("A", "C", 10);
    graph.addRoad("B", "C", 3);
    graph.addRoad("C", "D", 1);

    string source;
    cout << "Enter source city: ";
    cin >> source;

    graph.shortestPaths(source);

    return 0;
}
