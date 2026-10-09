//merge sort tree

#include <bits/stdc++.h>
using namespace std;

bool multicases_=true;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
////////fix:: making the copmarator explicit to avoid ambiguity (std::less instead of less)
// template<class  T>using ordered_multiset = tree<T,null_type,std::less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T>using ordered_multiset = tree<pair<T, int>, null_type, std::less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>using ordered_set = tree<T,null_type,std::less<T>,rb_tree_tag,tree_order_statistics_node_update>;

using ll = long long;
#define int long long//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<??
typedef unsigned long long u64;//this or the one  below
#define ull unsigned long long

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

void pre_compute(){
	
}


////////////////take care that for the function less:        std has a member std::less
					//and it is named for the function of the merge sort segment tree







//////memory and building:
//memory each level has n elements and there are levels of log then the copmlexity is number of elements which are (nlogn)
//
//we sort from two sorted nodes with two pointers (to make it linear or you can sort using sort() but it will take nlogn)
//so now the sort is happened lineary which means number of elements which means also (nlogn) 
	//(as said because we have n elements at levels whose number is log)
//
//so now memory is nlogn and the same thing for build



//what about the query?
//same logic of normal segment tree + binary search inside each covered sorted vector (node) to  find the required query(how many numbers greater/smaller/greater or equal/smaller or equal  to  x)
//which means ((logn)^2)  the log here is squared as you see (but it is fast log squared not like other squared logs )
	//>>>>>>>>>>>>>>>>>>>>>which means if you updated with ordered set (using binary search+with repeated find_by_order()) then it is log cubic (it is avoidable often but it is sometimes fast)
		/////so many people avoid using it for updates
			//they use other things for updates, so they use it as static range query data structure





////editable:
///less function, less wraper (if you want for example <, <=, > ,or >=)

struct MergeSortTree{
	int tree_size;
	vector<vector<int>>SegData;
	
	MergeSortTree(int n){
		tree_size=1;
		while(tree_size<n) tree_size<<=1;
		SegData.assign(2*tree_size,{});
	}
	
	vector<int>merge(const vector<int>&lf , const vector<int>&ri){
		int n=lf.size(),m=ri.size();
		vector<int>ans(n+m);
		
		
		int i=0,j=0,k=0;
		while(i<n&&j<m){
			if(lf[i]<ri[j])
				ans[k++]=lf[i++];
			else
				ans[k++]=ri[j++];
		}
		
		//if some elements from one array remain
		while(i<n)
			ans[k++]=lf[i++];
		while(j<m)
			ans[k++]=ri[j++];
		
		///fixed::::::don't forget to return ans
		return ans;
		
	}
	
	void build(const vector<int>&arr, int node, int lx, int rx){//we make the arr const to avoid editing it by mistake, and & to avoid wasted memory 
		
		if(rx-lx==1){
			if(lx<(int)arr.size())//////fix:: (int) before arr size
				SegData[node]={arr[lx]};
			return;////fixed:::::::::::::::::::important : return here is out of if<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			
		}
		
		
		int mid=(lx+rx)>>1;///fixed a type mistake ::::in rx
		build(arr,2*node+1,lx,mid);
		build(arr,2*node+2,mid,rx);
		
		SegData[node]=merge(SegData[2*node+1],SegData[2*node+2]);
		
	}
	
	//wrapper of build:
	void build(const vector<int>&arr){
		build(arr,0,0,tree_size);
	}
	
	
	
	
	int less (int l,int r, int k, int node, int lx, int rx){
		
		/*
			0-indexed:
			
			1-less (<)
					lower bound - begin
			
			/// 2-less or equal (<=)
					upper bound - begin <<<<<<<<<
			
			3-greater (>)
					end - upper bound
			
			/// 4-greater or equal (>=)
					end - lower bound   <<<<<<<<<
			
		*/
		
		
		if(lx>=r||rx<=l)
			return 0;
		if(lx>=l&&rx<=r){
			//now search
			
			
			auto &vec=SegData[node];//by reference,,,, for fast typing for the line downward
			//// ^ don't forget the & to avoid memory waste 
			
			return lower_bound(vec.begin(),vec.end(),k)-vec.begin(); 
			//>>>>>because the array is 0-indexed 
			///because elements less than x is  :   lower bound - begin 
			
			
		}
		
		int mid=(lx+rx)>>1;
		int lf=less(l,r,k,2*node+1,lx,mid);
		int ri=less(l,r,k,2*node+2,mid,rx);
		return lf+ri;////////fixing naming mistakes lf,ri not left,right
	}
	
	
	int less (int l, int r, int k){
		return less(l,r,k,0,0,tree_size);/////////important : not arr.size 
									///////////we put our tree_size which is power of 2
	}
	
};


////////////ai comments if you want to add update:

// Query complexity:
//
// 1) Merge Sort Tree (sorted vector at each node):
//    Segment-tree traversal: O(log n) nodes
//    Binary search in each vector: O(log n)
//    Total: O(log^2 n)
//
// 2) Segment Tree of PBDS ordered sets:
//
//    A) Using binary search with find_by_order(mid):
//       Each find_by_order() costs O(log n).
//       Binary search performs O(log n) steps -> O(log^2 n) per node.
//       Segment-tree traversal visits O(log n) nodes.
//       Total: O(log^3 n).
//
//    B) Using order_of_key(k) directly:
//       Counts elements strictly smaller than k in O(log n).
//       No manual binary search is needed.
//       Segment-tree traversal visits O(log n) nodes.
//       Total: O(log^2 n).
//
// Note: PBDS ordered_set does not support duplicate values as separate
// elements. Store {value, unique_id} pairs to preserve duplicates.







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
