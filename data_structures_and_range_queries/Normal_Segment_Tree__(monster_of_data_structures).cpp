//////for the segment tree to work:
	//the operation must be associative
		//which means suppose the operation is '*'   then (a*b)*c=a*(b*c)
	//if it is not associative then it is not supported 
		// because the segment tree may combine segments in different groupings
				//(and they remain in same order but what matters is different groupings)

/*
	
	reason of needing associativity  (explained by ai)
	A segment tree stores answers for predefined grouped segments.
	During a query, those precomputed answers are merged according to the tree's grouping.
	Therefore, 
		the merge operation needs to be associative 
			so that different valid groupings produce the same result.
*/


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


//////if you want to return more than thing , then:
   //you can return the point and get whatever you want from it 
	    //for example: after returning the point in the get function (second get) and you want x,y
	     //so you can do cout<<sg.get_range(l,r).x<<' '<<sg.get_range(l,r).y;






///////i prefer returning a point then use whatever you needed from it <<<<<<<<<<<<<<<<<<<<






const long long oo = 1e18;

////////////////note***********: that max is required so keep it in both merge and node
	/////////to use the lower bound function (and kth one if needed)



//note 
///if you are not using the definition as long long so the arr (input) must be long long
///due to the implementation of struct as this was built like that to avoid overflow 
//--------------    follow up   ------->							and to have larger range
//
//
//

//
// #define int long long//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<??

///////////////////////////////////////////////////////////////////////////can be edited:
struct Node{
	
	///note:neutral for and(&) is -1 because in binary representation it has all as ones 1111..
	static constexpr long long neutral=0;//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//fix::made neutral as static to make one variable for all of them
		//////to avoid making neutral variable for each node(huge wasted memory)
	///enhancement ::
	// we made neutral as constexpr to be replaced with its literal value directly during compilation
	
			
	
	long long mx,   sum;
	Node(){
		mx=-oo;
		
		sum=neutral;
	}
	Node(long long x){/////fixed::::long long to avoid overflow
		mx=x;
		
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
		while(tree_size<n)tree_size<<=1;	//tree_size here means nearest greater or equal power of 2
		SegData.assign(2*tree_size,Node()); // ^ tree_size leaves, tree_size-1 internal nodes
									//^ neutral <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	}
	
	///////////////////////////////////////////////////////////////////////////can be edited:
	Node merge(const Node&lf,const Node&ri){
		Node ans=Node();
		ans.mx=max(lf.mx,ri.mx);
		//
		ans.sum=lf.sum+ri.sum;
		//
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
	Node get_range(int l, int r){ 	////////////////important: R not included !!!!!!!
		return get_range(l,r,0,0,tree_size);
						//   ^ we started from the top
	}
	
	
	////************************setting
		/////////note : setting here is assuming safe setting :: !!!!!!!!!!!!!!!!!!!!!!!!!!
	void set(int idx,long long val, int node, int lx, int rx){
		if(rx-lx==1){//this means you are at a leaf
			SegData[node]=Node(val);
			return;//////fix::::::don't forget return
		}
		
		int mid=(lx+rx)>>1;
		if(idx<mid)//mid here is considered part of the right not the left segment
						// [lx,mid) is the left segment, [mid,rx) is the right segment
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
	
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	/*
	///////////kth one(if all are ones and zeros):
	//////////make sure that input is safe(make sure that it can't be more than number of ones!)
	int kth(int cnt,int node,int lx,int rx){
		if(rx-lx==1){//when it is a lefa
			return lx;
		}
		
		int mid=(lx+rx)>>1;
		int lf_sum=SegData[2*node+1].sum;
		if(lf_sum>=cnt)
			return kth(cnt,2*node+1,lx,mid);
		return kth(cnt-lf_sum,2*node+2,mid,rx);
	}
	int kth(int cnt){
		return kth(cnt,0,0,tree_size);
	}
	////
	*/
	
	
	//////note:
	////if we want kth one using find_first
	////////and actually we can use binary search on prefix sum 
		//then the first index has prefix sum >=k is the answer
			//but here it is 1 because each time at most it increases by 1
				//////////////////i mean at the problem of 1s and 0s
		///////////////prefix sum here can be done using get summation from 1 to i
																	//or 0 to i (if 0-indexed)
	
	
	
	
	
	//***********************************************************************
	//***********************************************************************
	//***********************************************************************
	//////to search in unsorted array for the lowerbound of x:
		//we can use prefix mx and lowerbound for the value x
	
	
	
	//////so we use the same idea of the (max) to find first position has value>=x  !!
											////////(it doesn't have to be exactly the max!!)
	
	//////find first (lower bound in unsorted)
	
	
	
	int find_first(int l, int r, long long x,int node, int lx, int rx){
		
		if(lx>=r||rx<=l)	//if went to point out of range
			return -1;
		
		if(SegData[node].mx<x) ///if it is lower than required
			return -1;
		
		if(rx-lx==1)		//if it is a leaf
			return lx;
		
		//logic is to search left, if not found then search right 
		  //(for easier and simple implementation)
		    //>>>>>>>because searching at left firstly guarantees the smallest index is returned
		
		int mid=(lx+rx)>>1;
		int ans=find_first(l,r,x,2*node+1,lx,mid);
		if(ans==-1)
			ans=find_first(l,r,x,2*node+2,mid,rx);
		
		return ans;///fix::::don't forget the return statement
	}
	
	
	
	int find_first(int l, int r,long long x){
		return find_first(l,r,x,0,0,tree_size);
	}
	
	
	/*
		
		explanation of find_first by ai:
		//////to find the first position in [l,r) whose value >= x:
		//////we store the maximum of every segment
		//////if a segment's maximum < x, we can skip the whole segment
		//////then search left first, and if not found, search right
		
	*/
	
	
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
