#include <bits/stdc++.h>
using namespace std;

// Recursive DFS: mark visited before exploring children.

void DFS_recursive(int u, vector<vector<int>>& adj, vector<bool>& vis) {
    vis[u] = true;
    for (auto v : adj[u])
        if (!vis[v])
            DFS_recursive(v, adj, vis);
}

/* Error/debug notes:
None preserved.
*/
