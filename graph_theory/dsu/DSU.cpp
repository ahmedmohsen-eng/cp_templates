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
	if(n == 0) return -1;///////
	return 63 - __builtin_clzll(n);
}

int get_bit_count(long long n){
	return __builtin_popcountll(n);
}

void pre_compute(){
	
}



///whenever you want any information on the component (sum/max/min/etc...)
	//you can make vector of what you want , then :
	//and keep storing the information you want in the leader of the component while merging

struct DSU {
	
	vector<int>parent,sz;
	//don't forget here to put the array you want (if needed), for ex: max,min,sum,etc....
	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
	
	int cmps;//number of connected components
	
	
	
	
	//////////////////////////////////
	///now we want to have the ability to know all nodes in a component
	//so we can use the logic of the linked list to use merge in O(1) instead of vector which takes more time
	//so we have three vectors: 
		// 1- next (acts as the pointer)
		// 2- tail (to know the tail fast)
		// 3- head (to know the head fast)
	////merge happens by connecting ones head to another tail
	/////////////also we can put the big on the left and other on the right 
		//////////////so that always the lead is the head
	vector<int>head,tail,nxt;///take care :::::::::::::: it is nxt not nextxxxxxxxxxxxxxxxxxxxx!!!!!!
	
	
	
	
	DSU(int n){
		
		cmps=0;
		
		sz.assign(n+1,0);
		parent.assign(n+1,0);
		
		//////////////////////////////////
		head.assign(n+1,0);
		tail.assign(n+1,0);
		//nxt assigned with -1! as indicator of tail
		nxt.assign(n+1,-1);
		
		
		////////////////take care :::::::::::::::::::::::::::::::::::::::::::::
		////////////if graph is empty at the beginning , so comment the follwoing for loop:
		///so this assumes there are nodes from 1 to n at the beginning:<<<<<<<<<<<<<<<<<<<<<<
		for(int i=1;i<=n;i++){
			//
			cmps++;
			sz[i]=1;
			parent[i]=i;
			head[i]=i;
			tail[i]=i;
		}
		
		//don't forget to intialize the array you are using for storing information (if needed) , for ex: max,min,summation ,etc...
		
		
	}
	
	// ///////////////////take care::::::::::::::::::::::::::::::::::::::::::::::
	// ///////////if graph is empty at the beginning so you use make_set to fill all details of that node
	// /////
	// void make_set(int u){
	// cmps++;
	// ///////////rest of details of the node:
	//
	//
	//
	// }
	
	
	
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
	
	
	vector<int> get_comp(int u){
		u=get_leader(u);////to get the leader because we don't update heads
								//because updatng all heads takes steps with number equal to the size of component
		vector<int>nodes;
		nodes.reserve(sz[u]);//to make the push back in O(1)
		for(int i=head[u];i!=-1;i=nxt[i]){////fix::::::::::::nxt not next.xxxxxxxxxxxxx
			nodes.push_back(i);
		}
		return nodes;////0-indexed
	}
	
	
	
	bool merge(int u, int v){
		//common mistake is to forget these two lines in any of these helper function : merge,is_connected
		u = get_leader(u);
		v = get_leader(v);
		
		if(u == v) return 0;
		
		
		cmps--;//number of connected components decreases by one if two nodes that are not in same component has been connected
		
		
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
		
		
		//////////////////////////////////
		nxt[tail[u]]=head[v];
		tail[u]=tail[v];
		/////note that head of v doesn't matter anymore
		
		
		//don't forget here to update the information you want to get (if needed) , for ex: max,min,sum,multiplication,etc.....
		//////////////////////////////////////////////////
		//////////////////////////////////////////////////
		
		
		
		
		return 1;
	}
	
	
	
	
	
};




void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	
	/////solution to problem: https://judge.yosupo.jp/problem/unionfind
	int n,q;cin>>n>>q;
	
	DSU dsu(n);
	
	
	while(q--){
		
		int op,u,v;cin>>op>>u>>v;
		if(op==0){
			dsu.merge(u,v);
		} else {
			cout << dsu.is_connected(u,v)<<'\n';
		}
		
	}
	
	
	
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	
	//setIO("problemname");
	
	//the following output way overwrites the file:
	
	// freopen("problemname.in", "r", stdin);
	// // the following line creates/overwrites the output file
	// freopen("problemname.out", "w", stdout);
	
	
	
	pre_compute();
	
	//
	cout<<setprecision(10)<<fixed;
	
	int tc=1;
	if(multicases_)cin>>tc;
	for(int _=1;_<=tc;_++){
		solve(_);
	}
	return 0;
}
