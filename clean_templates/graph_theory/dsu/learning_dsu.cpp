#include <bits/stdc++.h>
using namespace std;

// DSU (Union-Find) learning implementation
struct DSU {
    int n;
    vector<int> p, r;
    DSU(int n=0): n(n), p(n+1), r(n+1,0) { for (int i=0;i<=n;i++) p[i]=i; }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a,int b){ a=find(a); b=find(b); if (a==b) return false; if (r[a]<r[b]) swap(a,b); p[b]=a; if (r[a]==r[b]) r[a]++; return true; }
};

/* Error/debug notes:
None preserved.
*/
