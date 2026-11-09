#include <bits/stdc++.h>
using namespace std;

// bool multicases_=true;
bool multicases_=false;

////////////////////////////
//#define int long long

struct point {
	int x,y;
};

struct node{
	int x,y;
	long long cost;//
};





vector<int>dx = {-1, 1, 0, 0};
vector<int>dy = {0, 0, -1, 1};


/*
//vector<int> dx = {-1, 1, 0, 0, -1, -1, 1, 1};
vector<int> dy = {0, 0, -1, 1, -1, 1, -1, 1};
*/
/*
//if diagonal has extra cost:
const double diagonal_bonus = sqrt(2.0); // ~1.41421356
vector<int> diagonal_cost = {0, 0, 0, 0, diagonal_bonus, diagonal_bonus, diagonal_bonus, diagonal_bonus};

*/







struct cmp{
	bool operator()(const node&a,const node&b)const{
		return a.cost>b.cost;
	}
};










/*
//////////////////////////////////////////////////////////////////take care here : what is the maximum rows and columns????????
	///is it good or some test cases with larger rows and fewer columns (and vice versa) ?????????
int Nx=5e3+5;
int Ny=5e3+5;
vector<vector<int>>grid(Nx,vector<int>(Ny,0));
//vector<bool>vis(N,false);
vector<vector<point>>parent(Nx,vector<point>(Ny,{-1,-1}) );

vector<vector<long long>>dis(Nx,vector<long long>(Ny,1e18));
*/

vector<vector<int>> grid;
vector<vector<point>> parent;
vector<vector<long long>> dis;







int R,C;

// Helper to validate boundary limits
bool isvalid(int row, int col) {
	return (row >= 1 && row <= R && col >= 1 && col <= C);
}

long long dijkstra (point src, point target){
	priority_queue<node,vector<node>,cmp>pq;
	
	dis[src.x][src.y]=0;////////////////  
	pq.push({src.x,src.y,0});
	
	while(!pq.empty()){
		node u = pq.top();
		pq.pop();
		
		
		if(u.cost > dis[u.x][u.y]) continue;	
		
		if(u.x==target.x&&u.y==target.y)return u.cost;	
		
		//if(vis[u.idx]) continue;
		//vis[u.idx]=true;
		
		for(int i = 0 ;i < (int)dx.size() ; i ++){
			int nx=u.x+dx[i];
			int ny=u.y+dy[i];

			if(isvalid(nx,ny)){
				long long edgeCost = grid[nx][ny];
				long long newDist = u.cost + edgeCost;
				
				//////// if there  is a diagonal cost if 8 movement directions allowed 
				// int edgeCost = grid[nx][ny] + diagonal_cost[i];
				
				if(newDist<dis[nx][ny]){
					dis[nx][ny]=newDist;
					parent[nx][ny]={u.x,u.y};
					pq.push({nx,ny,newDist});
				}
				;
			}
			
		}
		
	}
	
	return -1LL;
}





void grid_clear(int R,int C){
	for(int row = 1; row <= R; row++){
		for(int col = 1; col <= C; col++){
			parent[row][col]={-1,-1};
			dis[row][col]=1e18;
		}
	}
}



// Dynamically allocates memory based EXACTLY on current R and C values
void grid_resize_and_clear(int rows, int cols) {
	// Size dynamically up to rows + 1 / cols + 1 to perfectly handle 1-based indexing
	grid.assign(rows + 1, vector<int>(cols + 1, 0));
	dis.assign(rows + 1, vector<long long>(cols + 1, 1e18));
	parent.assign(rows + 1, vector<point>(cols + 1, {-1, -1}));
}











void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	// cin>>n>>m>>src>>target;
	cin>>R>>C;
	
	
	
	///////////which one is used???mmm..
	// grid_clear(R,C);
	grid_resize_and_clear(R,C); 
	
	
	
		
	point src={1,1};
	
	point target={R,C};
	
	
	for(int i = 1; i <= R; i++) {
		for(int j = 1; j <= C; j++) {
			cin >> grid[i][j];
		}
	}
	
	long long ans = dijkstra(src,target);
	
	if(ans==-1){
		
		// cout<<"Not Reachable"<<'\n';
		cout<<-1<<'\n';
		
	} else {
		
		// cout<<ans<<'\n';
		
		vector<point>path;
		point cur=target;
		while(cur.x != -1 && cur.y != -1){    //while(cur!={-1,-1}){ //< this is not correct unless operators define for != with the struct
			path.push_back(cur);
			cur=parent[cur.x][cur.y];
		}
		reverse(path.begin(),path.end());
		
		for(auto&step:path) cout << "(" << step.x << "," << step.y << ") ";
		
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
