#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    long long weight;
};

int n, m;
vector<vector<Edge>> adj;
vector<long long> dist;
vector<int> parent;

void dijkstra(int src) {
    dist.assign(n + 1, INF);
    parent.assign(n + 1, -1);

    // Min-heap storing {distance, node}
    priority_queue<pair<long long, int>, 
                   vector<pair<long long, int>>, 
                   greater<pair<long long, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Skip outdated path entries in PQ (Lazy deletion)
        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.to;
            long long w = edge.weight;

            // Relaxation Step
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}
