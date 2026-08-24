///iterative dfs topological sort



// Problem: E - Friends UVA 10608
// Contest: Virtual Judge - Graph representation & DFS
// URL: https://vjudge.net/contest/838294#problem/E
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

void pre_compute(){
	
}

vector<vector<int>>adj;
vector<bool>vis;
int n,m;

vector<int>topo;

void dfs(int u){
	
	stack<pair<int,bool>>st;
	
	st.push({u,false});
	
	while(!st.empty()){
		
		auto&[u,finished]=st.top();
		st.pop();
		
		if(finished){
			topo.push_back(u);
			continue;
		}
		
		if(vis[u])continue;
		
		vis[u]=true;
		
		//finish dependencies and come to take it to the topo vector
		st.push({u,true});
		
		for(auto&v:adj[u]){
			if(!vis[v]){
				st.push({v,false});//fix : v not u
			}
		}
		
		
		
		
	}
	
	
	
}

void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	while(cin>>n>>m&&(n||m)){
		adj.assign(n+1,{});
		vis.assign(n+1,false);
		topo.clear();
		
		for(int i = 1 ,u,v;i <= m ; i++){
			cin>>u>>v;
			adj[v].push_back(u);
		}
		
		for(int i= 1 ;i<=n ;i++){
			if(!vis[i]){
				dfs(i);
			}
		}
		
		
		for(auto&el:topo)cout<<el<<' ';
		cout<<'\n';
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
