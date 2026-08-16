
// Dijkstra: non-negative weights. Returns shortest distance from src to target or -1 if unreachable.
#include <bits/stdc++.h>
using namespace std;

struct Node { int idx, cost; };
struct Cmp { bool operator()(const Node& a, const Node& b) const { return a.cost > b.cost; } };

int dijkstra(int n, const vector<vector<pair<int,int>>>& adj, int src, int target) {
    vector<bool> vis(n+1,false);
    priority_queue<Node, vector<Node>, Cmp> pq;
    pq.push({src,0});
    while (!pq.empty()) {
        auto u = pq.top(); pq.pop();
        if (vis[u.idx]) continue;
        vis[u.idx] = true;
        if (u.idx == target) return u.cost;
        for (auto &e : adj[u.idx]) {
            int v = e.first, w = e.second;
            if (!vis[v]) pq.push({v, u.cost + w});
        }
    }
    return -1;
}

int main(){ return 0; }
