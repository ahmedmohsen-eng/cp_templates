//////for the segment tree to work:
	//the operation must be associative
		//which means suppose the operation is '*'   then (a*b)*c=a*(b*c)
	//if it is not associative then it is not supported 
		//because it may be edited in different orders


#include <bits/stdc++.h>
using namespace std;

bool multicases_=false;////////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
// template<class  T>using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T>using ordered_multiset = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

using ll = long long;
// #define int long long//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<??
typedef unsigned long long u64;//this or the one  below
#define ull unsigned long long

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

/*
what can be edited:(for changing usage)
1-node struct (,,and neutral value)
2-merge function
3-return of the get function
*/


///////////////////////////////////////////////////////////////////////////can be edited:
struct Node{
	
	///note:neutral for and(&) is -1 because in binary representation it has all as ones 1111..
	static constexpr long long neutral=0;//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//fix::made neutral as static to make one variable for all of them
		//////to avoid making neutral variable for each node(huge wasted memory)
	///enhancement ::
	// we made neutral as constexpr to be replaced with its literal value directly during compilation
	
			
	
	long long sum;
	Node(){
		sum=neutral;
	}
	Node(long long x){/////fixed::::long long to avoid overflow
		sum=x;
	}
};

////notice that in the functions we used const ..type..& 
	//const to avoid editing it by mistake
	//& to avoid making a copy of it (for memory)

/////fixed::using long long for value and vector of long long to avoid overflow

struct SegTree{
	////notice that ::::
	// segment tree works for both 1 and 0 indexed array , it depend on the array indexing itself
	
	/////firstly the merge function and the constructor and the variables:
	
	
	int tree_size;
	vector<Node>SegData;
	
	SegTree(int n){
		tree_size=1;
		while(tree_size<n)tree_size<<=1;
		SegData.assign(2*tree_size,Node()); //n leaves, n-1 internal nodes
									//^ neutral <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	}
	
	///////////////////////////////////////////////////////////////////////////can be edited:
	Node merge(const Node&lf,const Node&ri){
		Node ans=Node();
		ans.sum=lf.sum+ri.sum;
		return ans;
	}
	
	
	////****************************getting range
	
	Node get_range(int l, int r, int node ,int lx, int rx){
		
		if(lx>=r||rx<=l) return Node();
		if(lx>=l&&rx<=r) return SegData[node];
		
		int mid=(lx+rx)>>1;
		Node lf = get_range(l,r,2*node+1,lx,mid);
		Node ri = get_range(l,r,2*node+2,mid,rx);
		return merge(lf,ri);
	}	
	
	///////////////////////////////////////////////////////////////////////////can be edited:
	long long get_range(int l, int r){ 	////////////////important: R not included !!!!!!!
		return get_range(l,r,0,0,tree_size).sum;
						//   ^ we started from the top
	}
	
	
	////************************setting
	
	void set(int idx,long long val, int node, int lx, int rx){
		if(rx-lx==1){//this means you are at a leaf
			SegData[node]=Node(val);
			return;//////fix::::::don't forget return
		}
		
		int mid=(lx+rx)>>1;
		if(idx<mid)//mid here is considered part of the right not the left
			set(idx,val,2*node+1,lx,mid);
		else
			set(idx,val,2*node+2,mid,rx);
		SegData[node]=merge(SegData[2*node+1],SegData[2*node+2]);
	}
	
	void set(int idx,long long val){
		set(idx,val,0,0,tree_size);//also started dfs from the 0 node
	}
	
	/////**********************building
	
	void build(const vector<long long>&arr,int node, int lx, int rx){
		if(rx-lx==1){//if it is a leaf
			if(lx<(int)arr.size())////////////to avoid getting out of the array
				SegData[node]=Node(arr[lx]);
			else	//////////////////////////////////////////////////////////added from gemini
				SegData[node]=Node();//empty with the neutral value
			return;//////fix::::::don't forget return
		}
		
		int mid=(lx+rx)>>1;
		build(arr,2*node+1,lx,mid);
		build(arr,2*node+2,mid,rx);
		
		SegData[node]=merge(SegData[2*node+1],SegData[2*node+2]);
	}
	
	void build(const vector<long long>&arr){
		build(arr,0,0,tree_size);
	}
	
};

void pre_compute(){
	
}

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
