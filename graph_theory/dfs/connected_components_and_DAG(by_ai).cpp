#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> vis;

//--------------------------------------------------
// DFS
//--------------------------------------------------
void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u])
        if (!vis[v])
            dfs(v);
}

//--------------------------------------------------
// Connected Components (Undirected)
// Returns a list of components.
// Each component is a vector of its vertices.
//--------------------------------------------------
void dfs_component(int u, vector<int>& comp) {
    vis[u] = true;
    comp.push_back(u);

    for (int v : adj[u])
        if (!vis[v])
            dfs_component(v, comp);
}

vector<vector<int>> connected_components(int n) {
    vis.assign(n + 1, false);

    vector<vector<int>> comps;

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vector<int> comp;
            dfs_component(i, comp);
            comps.push_back(comp);
        }
    }

    return comps;
}

//--------------------------------------------------
// Topological Sort (DAG)
//--------------------------------------------------
void topo_dfs(int u, vector<int>& topo) {
    vis[u] = true;

    for (int v : adj[u])
        if (!vis[v])
            topo_dfs(v, topo);

    topo.push_back(u);
}

vector<int> topological_sort(int n) {
    vis.assign(n + 1, false);

    vector<int> topo;

    for (int i = 1; i <= n; i++)
        if (!vis[i])
            topo_dfs(i, topo);

    reverse(topo.begin(), topo.end());
    return topo;
}

//--------------------------------------------------

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.assign(n + 1, {});

    while (m--) {
        int u, v;
        cin >> u >> v;

        // Directed graph:
        adj[u].push_back(v);

        // For an undirected graph, uncomment:
        // adj[v].push_back(u);
    }

    // Example: DFS from node 1
    vis.assign(n + 1, false);
    dfs(1);

    // Example: Connected Components
    // auto comps = connected_components(n);

    // Example: Topological Sort
    // auto topo = topological_sort(n);

    return 0;
}
