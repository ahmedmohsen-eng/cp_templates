//lazy segment tree

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
typedef unsigned long long u64;//this or the one  below
#define ull unsigned long long

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

void pre_compute(){
	
}







/////////>>::
#define int long long//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<??




//////////////note that the segment tree is built on what we get not what we set (update)<<<<<<<<<important ******






//lazy segment tree depends on making updates same as get fun. (to make it easy to update ranges)
	//by update only the value that we need
	////and make a variable (lazy) to store the update at this value , so when need to traverse downward then propagate the update to its two children and remove the value of lazy (if it has already been propagated)



//notice that the lazy values can accumulate


//in other words
//
//so remember that tge update traverse logic is the same as traverse of getting 
//and lazy is the update stored to make it propagated to the children when needed
//propagation happens to the children only when needed (and remove the lazy of the parent if it has been already propagated)




//but when does the lazy seg.tree work? 
	// the get and set have to have harmony between them
	// which mean >>>>>>>>: 
		//we know that the segement tree is built on the get function not the update
		//when you update the range you must be able to update it without need to see the children
//things that are not supported : 
//for example getting summation of range and update (division(floor)) or %
//because you need elements downward to know the update (which means lazy fails here)
///////////////but the % and / are solved through thing called "segtree beats"





////////////****important:
//////////whenever you make any function make the propagate fun. in the first line
/////////////even before the base cases 
				//(because kareem said that some problems quries that he faced while solving caused him some problems when he put the propagate function after the base case )
				







//what is editable:
/*
	
	variables in nodes
	node update fun.
	merge
	
	
*/




//when	 you reach a node propagate from it to its two children !!





///this implementation uses half-open intervals [l,r)
			//which means also r-l is the number of elements (without +1)
			//and when you want getting range from l to r then use get_range(l,r+1) .,.,,.,, notice it is r+1 here not r


const long long oo = 1e18;

struct Node{
	long long mn;
	long long lazy;
	bool is_lazy;//easier template 
	
	Node(): mn(oo),lazy(0),is_lazy(0){}//false is the same as 0
	Node(int x): mn(x),lazy(0),is_lazy(0){}
	
	///////////////////////////////////
	void update(int val,int lx, int rx){///may be we need lx,rx (for example when we need number of elements in range!!)
		mn += val;
		lazy += val;
		is_lazy=1;
	}
	
};

struct LazySegTree{
	
	int tree_size;
	vector<Node> SegData;
	
	LazySegTree(int n){
		tree_size=1;
		while(tree_size<n) tree_size <<= 1;
		SegData.assign(2*tree_size,Node());
	}
	
	Node merge(const Node&lf, const Node &ri){
		Node ans=Node();
		ans.mn=min(lf.mn,ri.mn);
		return ans;
	}
	
	void build(const vector<int>&arr, int node, int lx, int rx){
		if(rx-lx==1){
			if(lx<(int)arr.size()){//fix::::(int) before arr.size()
				SegData[node]=Node(arr[lx]);
			}
			return;////////fix::::::don't forget to return
		}
		
		int mid=(lx+rx)>>1;
		build(arr,2*node+1,lx,mid);
		build(arr,2*node+2,mid,rx);
		SegData[node]=merge(SegData[2*node+1],SegData[2*node+2]);
	}
	
	void build(const vector<int>&arr){
		build(arr,0,0,tree_size);
	}
	
	
	//////////////////////////////////////////////
	void propagate(int node, int lx, int rx){ ///propagate to the two children only
		
		
		//if it is a leaf or doesn't carry any lazy value
		if(rx-lx==1||SegData[node].is_lazy==false) //////fix::::::rx-lx not lx-rx
			return;
		
		int mid=(lx+rx)>>1;
		SegData[2*node+1].update(SegData[node].lazy,lx,mid);
		SegData[2*node+2].update(SegData[node].lazy,mid,rx);
		
		SegData[node].lazy=0;
		SegData[node].is_lazy=false;
		
	}
	
	
	void update(int l, int r,int val, int node, int lx, int rx){
		
		//////////////////////////////////////////////////
		propagate(node,lx,rx);
		
		if(lx>=r||rx<=l)
			return;
		
		if(lx>=l&&rx<=r){
			SegData[node].update(val,lx,rx);//////////update and return !!!!
			return;
		}
		
		int mid=(lx+rx)>>1;
		update(l,r,val,2*node+1,lx,mid); ///fix:::::::::typo mistake in the word node
		update(l,r,val,2*node+2,mid,rx); ///fix:::::::::typo mistake in the word node
		
		SegData[node]=merge(SegData[2*node+1],SegData[2*node+2]);
		
	}
	
	void update(int l, int r, int val){
		update(l,r,val,0,0,tree_size);
	}
	
	
	
	
	
	Node get_range(int l, int r, int node, int lx, int rx){
		
		//////////////////////////////////////////////////
		propagate(node,lx,rx);
		
		if(lx>=r||rx<=l)
			return Node();
		if(lx>=l&&rx<=r)
			return SegData[node];
		
		int mid = (lx+rx)>>1;
		Node lf=get_range(l,r,2*node+1,lx,mid);
		Node ri=get_range(l,r,2*node+2,mid,rx);
		
		return merge(lf,ri);
	}
	
	Node get_range(int l, int r){///////fix: returning correct data type
		return get_range(l,r,0,0,tree_size);
	}
	
	
	
};


//comment by ai (to know why top down works but not down top)
	//in other words why the child can't pull from its parent
			//to summarize the reason: because then the parent needs to pull from its parent !!!!
/*
 * =========================================================================
 * ARCHITECTURAL NOTE: WHY TOP-DOWN PROPAGATION (PUSH) IS MANDATORY
 * =========================================================================
 * 
 * 1. THE "GRANDPARENT PROBLEM" (Why pulling from parent `(node - 1) / 2` fails):
 *    - If you try to propagate or pull updates when visiting a child by looking 
 *      at its parent `(node - 1) / 2`, that parent itself might still be "dirty" 
 *      (i.e., it holds unpropagated lazy tags from its *own* ancestors like 
 *      grandparents or great-grandparents).
 *    - Pulling from a stale parent means the child completely misses updates 
 *      originating from higher up in the tree, leading to wrong answers.
 * 
 * 2. THE TOP-DOWN CASCADE SOLUTION (Why we propagate at the start of functions):
 *    - In a recursive segment tree, traversal is strictly top-down. By the time 
 *      you reach any node, all ancestors above it have already pushed their 
 *      pending updates down to it during their own visits.
 *    - Therefore, calling `propagate(node, lx, rx)` as the very first line when 
 *      entering `update` or `get_range` ensures that the current node is 
 *      fully synchronized.
 *    - It then immediately pushes those updates down to its children, guaranteeing 
 *      that any recursive descents land on clean, up-to-date child nodes.
 * =========================================================================
 */







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
