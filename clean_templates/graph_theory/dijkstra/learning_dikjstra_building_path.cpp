#include <bits/stdc++.h>
using namespace std;

#define int long long

struct node { int idx, cost, par; };
struct cmp { bool operator()(const node &a, const node &b) const { return a.cost > b.cost; } };

const int NMAX = 200005;
vector<vector<node>> adj(NMAX);
vector<bool> vis(NMAX, false);
vector<int> parent(NMAX, -1);

int dijkstra(int src, int target) {
    priority_queue<node, vector<node>, cmp> pq;
    pq.push({src, 0, -1});
    while (!pq.empty()) {
        node u = pq.top(); pq.pop();
        if (vis[u.idx]) continue;
        vis[u.idx] = true;
        parent[u.idx] = u.par;
        if (u.idx == target) return u.cost;
        for (auto &v : adj[u.idx]) {
            if (!vis[v.idx]) pq.push({v.idx, u.cost + v.cost, u.idx});
        }
    }
    return -1;
}

void graph_clear(int n){
    for (int i = 1; i <= n; i++){
        adj[i].clear(); vis[i]=false; parent[i]=-1;
    }
}

void solve(){
    int n,m; cin>>n>>m; int src=1, target=n;
    graph_clear(n);
    for (int i=0;i<m;i++){int u,v,w;cin>>u>>v>>w; adj[u].push_back({v,w,-1}); adj[v].push_back({u,w,-1}); }
    int ans = dijkstra(src,target);
    if (ans==-1) cout<<-1<<"\n";
    else {
        vector<int> path; int cur=target; while(cur!=-1){ path.push_back(cur); cur=parent[cur]; }
        reverse(path.begin(), path.end()); for (auto &s: path) cout<<s<<' '; cout<<"\n";
    }
}

signed main(){ ios::sync_with_stdio(false); cin.tie(nullptr); solve(); return 0; }
