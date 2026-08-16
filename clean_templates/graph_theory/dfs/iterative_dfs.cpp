#include <bits/stdc++.h>
using namespace std;

// Iterative DFS using explicit stack (simulates recursion).

void DFS_iterative(int start, const vector<vector<int>>& adj, vector<bool>& vis) {
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int v : adj[u]) {
            if (!vis[v]) st.push(v);
        }
    }
}

/* Error/debug notes:
None preserved.
*/
