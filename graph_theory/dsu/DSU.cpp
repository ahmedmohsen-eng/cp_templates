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
	if(n == 0) return -1;///////
	return 63 - __builtin_clzll(n);
}

int get_bit_count(long long n){
	return __builtin_popcountll(n);
}

void pre_compute(){
	
}



struct DSU {
	
	vector<int>parent,sz;
	
	int cmps;//number of connected components
	
	DSU(int n){
		sz.assign(n+1,1);
		
		parent.resize(n+1);
		iota(parent.begin(),parent.end(),0);
		//
		// parent.assign(n+1,0);
		// for(int i=1;i<=n;i++){
			// parent[i]=i;
		// }
		
		cmps=n;
		
	}
	
	int get_leader(int u){
		if(parent[u]==u)
			return u;
		
		//after we understood the small to large that reduces to log compexity :
		//path compression (ofcourse after using small to large) : O(1)amortized     : actually O(alpha(n)) amortized per operation
				////amortized means number of operations / number of queries
					//depends on inverse ackerman function (dp-like thinking):
						//maximum 4 for usual large n
			//whenever you walk on some path assign the children to the parent where you have reached using the recursion
		
		return parent[u]=get_leader(parent[u]);///part of path compression trick here is : parent[u]=
		
	}
	
	bool is_connected(int u, int v){
		u = get_leader(u);
		v = get_leader(v);
		return u == v;
	}
	
	int get_size(int u){
		u=get_leader(u);
		return sz[u];
	}
	
	bool merge(int u, int v){
		//common mistake is to forget these two lines in any of these helper function : merge,is_connected
		u = get_leader(u);
		v = get_leader(v);
		
		if(u == v) return 0;
		
		
		
		
		///small to large:
		/////it is about :
			//doubling the size if both sizes are equal 
			// /or/ 
			//the bigger has the same depth if they are not equal
				////so it is log complexity because it is increaseing by doubling
		
		if(sz[u]<sz[v])/////putting the small into the large one is the small to large trick
			swap(u,v);
						//now u is the bigger one
		
		
		parent[v]=u;
		sz[u]+=sz[v];
		
		cmps--;//number of connected components decreases by one if two nodes that are not in same component has been connected
		return 1;
	}
	
	
	
};




void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	
	
	
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
