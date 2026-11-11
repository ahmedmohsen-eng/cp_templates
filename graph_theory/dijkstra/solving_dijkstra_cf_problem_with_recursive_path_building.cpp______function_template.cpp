
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

struct state{
	
	int w, u;
	
	bool operator<(const state&other)const{
		return w>other.w;
	}
	
};




//////////////

const long long oo = 1e18;

int n,m,src,tar;
vector<vector<state>>adj;
vector<int>dist,parent;
priority_queue<state>q;


////////////.


int dijkstra(int src, int tar){
	
	dist.assign(n+1,oo);
	parent.assign(n+1,-1);
	q={};///////////fix:::::clear the q /////////////////////////
	
	q.push({0,src});
	dist[src]=0;
	
	while(!q.empty()){
		
		auto [cost,u]=q.top();
		q.pop();
		
		//you can return the cost if you found the tar. (target) ,    but i chose to get all distances (choose whatever you want)
		
		if(cost>dist[u]) continue;
		
		for(auto&[w,v]:adj[u]){
			if(dist[u]+w<dist[v]){
				dist[v]=dist[u]+w;
				q.push({dist[v],v});
				parent[v]=u;
			}
		}
		
	}
	
	return dist[tar];
	
}

void print_path(int tar){
	 if(tar==-1)return;
	 print_path(parent[tar]);
	 cout<<tar<<' ';
}

void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	cin>>n>>m;
	src=1,tar=n;
	adj.assign(n+1,{});
	for(int i=1 ,u,v,w ;i<=m;i++){
		cin>>u>>v>>w;
		adj[u].push_back({w,v});
		adj[v].push_back({w,u});////////////////don't forget it
	}
	
	int ans = dijkstra(src,tar);
	if(ans==oo) cout<<-1;///////fix:::::::don't forget that case!!!!!!
	else print_path(tar);
	
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
