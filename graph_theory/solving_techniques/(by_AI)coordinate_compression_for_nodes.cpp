/*
    ============================================================
                  GRAPH COORDINATE COMPRESSION
    ============================================================

    Use when vertex labels are large, sparse, or unknown.

    Process:
        1. Read and store all edges.
        2. Collect all vertices.
        3. Sort and remove duplicates.
        4. Compress vertices using lower_bound.
        5. Build the adjacency list.

    Mapping:
        nodes[i] = original label of compressed vertex i
        comp(x)   = compressed index of original vertex x

    Supports:
        - Directed / Undirected
        - Weighted / Unweighted

    Complexity:
        Compression: O(V log V)
        Building:    O(E log V)
*/


#include <bits/stdc++.h>
using namespace std;

using ll = long long;


// ======================= INPUT =======================

int m;
cin >> m;


// ======================= EDGES =======================

// Unweighted:
vector<pair<ll, ll>> edges(m);

// Weighted:
// vector<tuple<ll, ll, ll>> edges(m);


// ======================= COLLECT VERTICES =======================

vector<ll> nodes;

for (auto &[u, v] : edges) {
    cin >> u >> v;

    nodes.push_back(u);
    nodes.push_back(v);
}

// Weighted:
// for (auto &[u, v, w] : edges) {
//     cin >> u >> v >> w;
//
//     nodes.push_back(u);
//     nodes.push_back(v);
// }


// ======================= COMPRESSION =======================

sort(nodes.begin(), nodes.end());
nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

auto comp = [&](ll x) {
    return lower_bound(nodes.begin(), nodes.end(), x) - nodes.begin();
};


// ======================= ADJACENCY LIST =======================

// Unweighted:
vector<vector<int>> adj(nodes.size());

// Weighted:
// vector<vector<pair<int, ll>>> adj(nodes.size());


// ======================= BUILD GRAPH =======================

for (auto [u, v] : edges) {
    int cu = comp(u);
    int cv = comp(v);

    adj[cu].push_back(cv);

    // Undirected:
    // adj[cv].push_back(cu);
}

// Weighted:
// for (auto [u, v, w] : edges) {
//     int cu = comp(u);
//     int cv = comp(v);
//
//     adj[cu].push_back({cv, w});
//
//     // Undirected:
//     // adj[cv].push_back({cu, w});
// }


// ======================= ORIGINAL LABEL =======================

// nodes[i] = original label of compressed vertex i.

// Example:
// int compressed = comp(1000000000);
// ll original = nodes[compressed];
