#include <bits/stdc++.h>
using namespace std;

// BFS utilities: undirected/directed, shortest levels, parent path reconstruction, multi-source.

struct node {
    int index, cost;
};

int n, m;
vector<vector<int>> adj;
vector<bool> vis;
vector<int> lvls;
vector<int> parent;
vector<int> path;

void bfs(int src) {
    vis.assign(n + 1, false);
    queue<int> q;
    vis[src] = true;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &v : adj[u]) {
            if (!vis[v]) {
                q.push(v);
                vis[v] = true;
            }
        }
    }
}

void bfs_shortest_path(int src) {
    lvls.assign(n + 1, -1);
    queue<int> q;
    lvls[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &v : adj[u]) {
            if (lvls[v] == -1) {
                lvls[v] = lvls[u] + 1;
                q.push(v);
            }
        }
    }
}

void bfs_build_shortest_path(int src) {
    lvls.assign(n + 1, -1);
    parent.assign(n + 1, -1);
    queue<int> q;
    lvls[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &v : adj[u]) {
            if (lvls[v] == -1) {
                lvls[v] = lvls[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

void bfs_get_shortest_path(int target) {
    path.clear();
    if (lvls[target] == -1)
        return;
    int cur = target;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());
}

bool has_cycle_undirected_bfs() {
    vis.assign(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (vis[i])
            continue;
        queue<pair<int, int>> q;
        q.push({i, -1});
        vis[i] = true;
        while (!q.empty()) {
            auto [u, p] = q.front();
            q.pop();
            for (auto &v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push({v, u});
                } else if (v != p) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool has_cycle_directed_bfs() {
    vector<int> indegree(n + 1, 0);
    for (int i = 1; i <= n; i++)
        for (auto &v : adj[i])
            indegree[v]++;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indegree[i] == 0)
            q.push(i);
    int processed = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        processed++;
        for (auto &v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0)
                q.push(v);
        }
    }
    return processed != n;
}

vector<int> topo_sort_bfs() {
    vector<int> indegree(n + 1, 0);
    vector<int> topo;
    for (int i = 1; i <= n; i++)
        for (auto &v : adj[i])
            indegree[v]++;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indegree[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        for (auto &v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0)
                q.push(v);
        }
    }
    if ((int)topo.size() != n)
        return {};
    return topo;
}

bool is_bipartite() {
    vector<int> color(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (color[i] != -1)
            continue;
        queue<int> q;
        color[i] = 0;
        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}

/* Error/debug notes:
- Minor naming fixes consolidated into code (e.g., parent usage); no functional changes.
*/
