#include <bits/stdc++.h>
using namespace std;

// bool multicases_=true;
bool multicases_=false;

#define int long long



struct node{
	int idx,cost,par;//
};

struct cmp{
	bool operator()(node&a,node&b){
		return a.cost>b.cost;
	}
};

int N=2e5+5;
vector<vector<node>>adj(N);
vector<bool>vis(N,false);
vector<int>parent(N,-1);
int n,m;

int dijkstra (int src, int target){
	priority_queue<node,vector<node>,cmp>pq;
	
	pq.push({src,0,-1});//src parent is -1
	
	while(!pq.empty()){
		node u = pq.top();
		pq.pop();
		
		if(u.idx==target)return u.cost;
		
		if(vis[u.idx]) continue;
		vis[u.idx]=true;//mark as visited
		parent[u.idx]=u.par;//////
				//the popped one is the optimal one , so
					// use it as the parent for its children
		
		for(auto&v:adj[u.idx]){
			if(!vis[v.idx]){
				parent[v.idx]=u.idx;
				pq.push({v.idx,u.cost+v.cost,u.idx});//
										//add u.idx as parent for v.idx 
			}
		}
		
	}
	
	return -1;
}

void graph_clear(int n){
	for(int i = 1 ; i <= n; i++){
		adj[i].clear();
		vis[i]=false;
		parent[i]=-1;
		
	}
}

void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	// graph_clear(n);
	
	int src,target;
	// cin>>n>>m>>src>>target;
	cin>>n>>m; src=1,target=n;
	
	for(int i = 1 ,u,v,w ; i<=m ;i++){
		cin>>u>>v>>w;
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
	}
	
	int ans = dijkstra(src,target);
	
	if(ans==-1){
		
		// cout<<"Not Reachable"<<'\n';
		cout<<-1<<'\n';
		
	} else {
		
		// cout<<ans<<'\n';
		
		vector<int>path;
		int cur=target;
		while(cur!=-1){
			path.push_back(cur);
			cur=parent[cur];
		}
		reverse(path.begin(),path.end());
		
		for(auto&step:path)cout<<step<<' ';
		
		cout<<'\n';
		
	}
	
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	
	//pre computations:
	
	
	int tc=1;
	if(multicases_)cin>>tc;
	int total_tcs=tc;
	while(tc--){
		solve(total_tcs-tc);
	}
	return 0;
}
