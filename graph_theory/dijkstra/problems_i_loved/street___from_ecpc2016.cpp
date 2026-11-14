//problem : https://codeforces.com/gym/101147/problem/B
//submission : https://codeforces.com/gym/101147/submission/398566613


// Problem: J - Street
// Contest: Virtual Judge - Dijkstra
// URL: https://vjudge.net/contest/867000#problem/J
// Memory Limit: 256 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

bool multicases_=true;

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



const long long oo = 1e18;


// long long fastpow(long long a,long long b){
// 	
	// long long ans=1;
// 	
	// while(b){
		// if(b&1)ans*=a;
		// a*=a;
		// b>>=1;
	// }
// 	
	// return ans;
// }



struct rect{
	int x1,x2,y1,y2;
};

struct edge{
	int to;
	
	///////fix:::make it long double
	long double w;
	
	bool operator<(const edge& other)const{
		return w>other.w;
	}
	
};

int n,l,u;
vector<vector<edge>>adj;


//////fix::::make it long double:

vector<long double>dist;

/////////take care order is not the same as edge , so i made it alone
/////////////////always focus which is first , is it weight or childer????!!!!!!<<<<<
priority_queue<pair<long double,int>,
                   vector<pair<long double,int>>,
                   greater<pair<long double,int>>> q;

//////fix::::make dijkstra returns long double
long double dijkstra(int src, int tar){
	
	
	//////fix::make the dist with enough size
	dist.assign(n+3,oo);
	
	
	q={};///////////fix:::::clear the q /////////////////////////
	
	
	q.push({0,src});
	dist[src]=0;
	
	while(!q.empty()){
		
		//////fix::::it is better to name it node, as the name "u" was used before
		auto [cost,node]=q.top();
		q.pop();
		
		
		if(cost>dist[node]) continue;
		
		///////fix::::v,w not w,v  (due to the struct)
		for(auto&[v,w]:adj[node]){
			if(dist[node]+w<dist[v]){
				dist[v]=dist[node]+w;
				q.push({dist[v],v});
			}
		}
		
	}
	
	return dist[tar];
	
}

void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	
	cin>>n>>l>>u; //number of spots, length of street , width of street
	
	adj.assign(n+3,{});
	
	
	vector<rect>v(n+3);// 1+n+1  (start+points+end) n+2
	
	int h,	// height
		w,	// width
		d,	// distance between beginning and the spot
		k;	// 0/1 which side does it share with the street (1->right,0->left)
	
	for(int i=1 ;i<=n;i++){
		
		cin>>h>>w>>d>>k;
		
		v[i]={(k?u-w:0),(k?u:w),d,d+h};
		
	}
	
	
	//fix::don't forget to add the values of start and end points
	v[0]=	{0,u,0,0};
	v[n+1]=	{0,u,l,l};
	
	
	auto cost = [&](const rect& a, const rect& b){
		
		int dx= max(0LL, max(a.x1,b.x1)-min(a.x2,b.x2) )  ;
		int dy= max(0LL, max(a.y1,b.y1)-min(a.y2,b.y2) )  ;
		
		return sqrtl( (long double)dx*dx+(long double)dy*dy );
	};
	
	
	/////fix:::::start with 0 not 1 and end with n+1 not n
	for(int i=0;i<=n+1;i++){
		for(int j=0;j<=n+1;j++){
			
			if(i==j)continue;
			
			int start = i,target=j;
			
			/////fixed::::long double not int for cost
			long double w =  cost(v[start],v[target]);
			
			adj[start].push_back({target,w});
			adj[target].push_back({start,w});
			
		}
	}
	
	
	long double ans;
	
	ans=dijkstra(0,n+1);
	
	
	cout<<fixed<<setprecision(6)<<ans<<'\n';
	
	
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	
	//setIO("problemname");
	
	//the following output way overwrites the file:
	
	
	
	/////////don't forget it:
	freopen("street.in","r",stdin);
	
	
	
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
