#include <bits/stdc++.h>
using namespace std;

bool multicases_=false;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
// template<class  T>using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T>using ordered_multiset = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

using ll = long long;
#define int long long//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<??
typedef unsigned long long u64;//this or the one  below
#define ull unsigned long long

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int get_first_bit(long long n){
	return 63 - __builtin_clzll(n);
}

int get_bit_count(long long n){
	return __builtin_popcountll(n);
}

void pre_compute(){
	
}

struct State{
	int d,v;//weight,node
	bool operator<(const State&other)const{
		return d>other.d;
	}
};



vector<int>parent;
///recusive method without (storing the path and reversing)
void print(int u){
	if(u==-1) return;
	print(parent[u]);
	cout<<u<<'\n';
}


void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	int n,m;cin>>n>>m;
	vector<vector<State>>adj(n+1);
	
	for(int i = 0 ;i<m;i++){
		int u,v,w;cin>>u>>v>>w;
		adj[u].push_back({w,v});
	//take care if the graph is directed or no
		adj[v].push_back({w,u});
	}
	
	
	///////take care that oo is not small!!
	const int oo =1e18;
	
	
	
	vector<int>dist(n+1,oo);
	parent.assign(n+1,-1);
	priority_queue<State>pq;
	
	/////fix::::don't forget to inialize
	dist[1]=0;
	pq.push({0,1});
	
	while(pq.size()){
		auto [cost,u]=pq.top();
		pq.pop();
		
		if(cost>dist[u])continue;
		
		for(auto [w,v]:adj[u]){
			if(dist[u]+w < dist[v]){
				dist[v]=dist[u]+w;
				parent[v]=u;
				pq.push({dist[v],v});
			}
		}
		
	}
	
	
	//take care if you can't reach it
	
	if(dist[n]==oo){
		cout<<-1<<'\n';
		return;
	}
	
	vector<int>path;
	int u = n;
	while(u!=-1){
		path.push_back(u);
		u=parent[u];
	}
	
	reverse(path.begin(),path.end());
	
	for(auto&x:path)cout<<x<<' ';
	
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	
	//setIO("problemname");
	
	//the following output way overwrites the file:
	
	// freopen("problemname.in", "r", stdin);
	// // the following line creates/overwrites the output file
	// freopen("problemname.out", "w", stdout);
	
	
	
	pre_compute();
	
	int tc=1;
	if(multicases_)cin>>tc;
	int total_tcs=tc;
	while(tc--){
		solve(total_tcs-tc);
	}
	return 0;
}
