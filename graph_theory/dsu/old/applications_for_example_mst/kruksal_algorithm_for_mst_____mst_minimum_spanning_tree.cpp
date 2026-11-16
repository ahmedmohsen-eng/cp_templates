/*

now you have a connected weighted graph and you want the tree with the minimum cost

idea:
for tree with n nodes the number of edges is n-1
you must avoid cycles
so order by cost
then take if merging these nodes(building this edge) doesn't make a cycle (by checking if it is in the same component using dsu)
otherwise leave
.................it is greedy
*/

#include <bits/stdc++.h>
using namespace std;

bool multicases_=false; ///////????????

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class  T>using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T>using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

using ll = long long;
// #define int long long

void pre_compute(){
	
}





struct DSU {
    int cnt;
    vector<int>parent, sizes;
    void init(int n)
    {
        cnt = n;
        parent.resize(n + 1);
        sizes.resize(n + 1);
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
        
        --cnt;
        return 1;
    }
};





struct edge{
	int u,v,cost;
};

struct cmp{
	
	bool operator()(edge&a,edge&b){
		return a.cost>b.cost; // here it means start with smaller
	}
	
};



priority_queue<edge,vector<edge>,cmp>pq;






//if you only want the path this could be enough !!!!!!!!!!!!!!!!!!!!!!!!!

void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	int n,m;
	cin>>n>>m;
	edge tmp;
	while(m--){
		cin>>tmp.u>>tmp.v>>tmp.cost;
		pq.push(tmp);
	}
	
	DSU d;
	d.init(n);
	
	int taken=0;
	vector<edge>path;
	while(!pq.empty()&&taken!=n-1){
		
		auto [u,v,c] = pq.top();
		pq.pop();
		
		if(d.merge(u,v)){
			taken++;
			path.push_back({u,v,c});
		}
		
	}
	
	int total_cost=0;
	for(auto&[u,v,c]:path)cout<<u<<' '<<v<<" and cost is : "<<c<<'\n'  
							,  total_cost+=c;
	
	cout<<"total cost is : "<<total_cost<<'\n';
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
