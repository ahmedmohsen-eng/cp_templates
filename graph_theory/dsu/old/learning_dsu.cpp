#include <bits/stdc++.h>
using namespace std;

bool multicases_=true;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class  T>using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T>using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

using ll = long long;
// #define int long long

void pre_compute(){
	
}

/*

dsu is an online query which means that current action affect future queries

dsu depends on connecting components using each component root

there are two optimizations implmented for it :
1- Union by Size
2- Path Compression


explanation by ai is below 


*/


//dsu template:
struct DSU {
    int cnt;
    vector<int>parent, sizes;
    void init(int n)
    {
        cnt = n;//initally all are disconnected compmonents so number of connected components is 1
        parent.resize(n + 1);
        sizes.resize(n + 1);
        
		//sometimes intializing with n+3 is good if you need to check after and before (and also 1-indexed)
		
		for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
            sizes[i] = 1;
        }
    }
 
    int find_root(int u)
    {
        if (parent[u] == u)
            return u;
        return parent[u] = find_root(parent[u]);
    }
 
    int merge(int u, int v)
    {
        int root_u = find_root(u);
        int root_v = find_root(v);
 
        if (root_u == root_v)
            return 0;
 
        if (sizes[root_u] > sizes[root_v])
            swap(root_u, root_v);
 
        parent[root_u] = root_v;
        sizes[root_v] += sizes[root_u];
        
        --cnt;//number of connected components decreased by 1 after merging 2 components into 1 component
        return 1;
    }
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////example:

void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	int n,q;cin>>n>>q;
	//n elements from 1 to n (or use map instead of vector int the dsu struct)
	//then q queries
	
	
	DSU d;
	d.init(n);
	
	int qq,u,v;//query type, first point , second point(or node)
	while(q--){
		cin>>qq>>u>>v;
		if      (qq==1)d.merge(u,v);
		else if (qq==2)cout<<(d.find_root(u)==d.find_root(v)?"YES":"NO")<<'\n';
	}
	
	
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	
	pre_compute();
	
	int tc=1;
	if(multicases_)cin>>tc;
	int total_tcs=tc;
	while(tc--){
		solve(total_tcs-tc);
	}
	return 0;
}





















/*
DSU (Disjoint Set Union)

DSU is used to maintain multiple disjoint components while processing
online queries, meaning that the result of a current operation can
affect future operations.

The main idea is that every component has a representative (root),
and each node eventually points toward the root of its component.

There are two main optimizations:

1- Union by Size

When merging two components, we always attach the smaller tree to
the larger tree.

Why does this give O(log n) height?

Initially, every node is a separate tree of size 1.

For example:

{1} {2} {3} {4}

Merge 1 and 2:

{1, 2}        -> size = 2

Merge 3 and 4:

{3, 4}        -> size = 2

Now merge the two components:

{1, 2} + {3, 4} -> size = 4

Whenever a node becomes deeper, its component is merged into a
component of at least the same size, so the size of its component
at least doubles.

Therefore, a node's depth can increase at most:

log₂(n)

times.

So union by size guarantees a tree height of O(log n).

2- Path Compression

When we call find(x), we traverse from x toward the root.

After finding the root, we make every node on the path point
directly to the root.

For example:

Before:
1 -> 2 -> 3 -> 4

After find(1):
1 -> 4
2 -> 4
3 -> 4

This makes future find operations much faster.

When union by size and path compression are used together,
the amortized complexity of each operation is:

O(α(n))

where α(n) is the inverse Ackermann function, which grows
extremely slowly and is practically constant for all realistic n.
*/
