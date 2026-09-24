///////problem : https://cses.fi/alon/task/1651









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

//bit or called fenwick tree :       (simple small code)
	// dynamic
	// support operations that have inverse such as summation  (it is like an extension of cumulative arrays)
	//memory linear (exactly n not big constant)
	// log n for both update and query , but it is only log (no big constants)
//
// :
// it supports to add point (idx,v) a[idx]+=v   not setting it xxxx
//it supports getting range from l to r

////////



/////storage : index i stores range [i-lsb(i)+1,i]
											//which means index i stores length of lsb(i)


///lsb(n) = n & -n          
		///negative makes the binary rersepenation as the 2's complement of the number
	//because for example :
					//// 0010(1)0
					//// 1101(1)0 //we get the 2's complement by leaving all zeros from the left
										//then leave the first one from the left
										//then reverse all after the first one from the left
					//// then when you get and only the first one remains 
						//so its value is lsb 

//unrelated but good information :
//additinoal information : lsb is also the biggest power of 2 that divides the n
//////////unrelated information ended

//now continue:



//here if you want summation(l,r) then it is summation(1,r)-summation(1,l-1)
/// as the get function here gives you summatation (or the used function) from 1 to idx




////////get function :
			// get (x) ->    firstly  add the value stored in x then remove the lsb from x then add the value and so on..
						/////////which takes log n








//firstly the array is initally 0 and then we update function for building
	//it means making array of zeros and then add use update while passing on each value of the original array


//but what is the update function : 
///////when update element at index i then update all indices that include it in its range <<<<<<<<<<<<<<<<<
			// keep adding the lsb
			// so update(i,x) means add x to idx i then add lsb of i then add x then ..... while i<=n








///////////////////////////////////////////////////////////
//

///////////////////////conclustion :
//to update you keep adding lsb to move to the window of the element before the current window 
//to get you keep removing lsb to see which indices windows are affected
	//////// https://www.hackerearth.com/practice/notes/binary-indexed-tree-or-fenwick-tree/

//important note : you can set by updating i,-cur+new     so you remove the current element at idx and then add the value you want



//////////this implementation is 1-indexed and the array must be 1-indexed also


struct BIT {
	//op
	long long op(long long a, long long b){
		return a+b;
	}
	long long inv_op(long long a, long long b){
		return a-b;
	}
	long long def_op=0;///default : for + it is 0 , for * it is 1
	
	
	//variables
	int n; vector<long long>b;
	
	
	//update
	void update(int idx,long long v){
				//note : use LL (ex:2LL) as v to avoid different types errors !!<<<<<<<<
		while(idx<=n){
			b[idx]=op(b[idx],v);
			idx += idx&-idx;//negative is done before &
		}
	}
	
	//get from 1 to idx
	long long get (int idx){
		long long ans=def_op;
		while(idx>0){////because it is 1-indexed
			ans=op(ans,b[idx]);
			idx-=idx&-idx;
		}
		return ans;
	}
	
	//get from l to r
	long long get(int l , int r){
		return get(r)-get(l-1);//safe because it is 1-indexed
	}
	
	//set
	void set(int idx,long long v){
			//note : use LL (ex:2LL) as v to avoid different types errors !!<<<<<<<<
		long long old=get(idx,idx);
		update(idx, inv_op(v,old) );
	}
	
	
	BIT(vector<long long>arr){ //beginning of constructor
		
		n=arr.size()-1;//must be 1-indexed <<<<<<<<<<<<<<<<<<<<<<<<<<<
		b.assign(n+1,def_op);
		
		
		// for(int i = 1 ;i <= n; i++){
			// update(i,arr[i]);
		// }
		
		//optimized to (O(n)) instead of nlogn:
		//it is directed acyclic graph so while passing add to its parent
			//which means when finishing it is linear time and all values have their exact ranges
				//note: don't set but make operation , to store values of children gained before entering it!
					//and of course even accessed a parent then children, this doesn't matter ->because also we add the parent(so order of accessing doesn't matter)'
		for(int i = 1 ;i<=n ;i++){
			b[i]=op(b[i],arr[i]);
			int parent=i+(i&-i);
			if(parent<=n)b[parent]=op(b[parent],b[i]);
		}
		
		
	} //end of constructor
	
	
	BIT(int _n){////if we want empty array 
					//(maybe for range update, point query)
						///because range update point query requires intially all empty 
									//(two arrays one of the BIT, and the original)
										//this is because when adding as difference array we want to avoid add original values if kept without making -x directly at the index after 
																									//(to avoid including at the prefix for other elements)
															///////because condition of differencea array is begin with default value(0 for the plus-minus)
		n=_n;
		b.assign(n+1,def_op);
	}
	
	
};



/*
	there are two questions i don't know their answers :
		1-why when adding lsb this goes to the nearest bigger element it affects
								//bigger because as known the BIT indices store themselves and some elements before (as continous range)
		2-why when removing lsb this goes to element exactly before current block
						i mean why do they work
	
	////////////keep them here , maybe they are answered :
		// 
	
	
	
	
*/










void pre_compute(){
	
}

void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	int n,q; cin>>n>>q;
	vector<int>arr(n+1);
	for(int i = 1 ;i <= n; i++)cin>>arr[i];
	
	
	BIT b = BIT(n);
	
	int qq,l,r,v,i;
	while(q--){
		
		cin>>qq;
			
		if(qq==1){
			cin>>l>>r>>v;
			b.update(l,v);
			b.update(r+1,b.inv_op(b.def_op,v));//order matters because if - then 0-x not x-0
														////same thing for some operations like *
		} else {
			cin>>i;
			cout<<arr[i]+b.get(i)<<'\n';
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
	
	int tc=1;
	if(multicases_)cin>>tc;
	int total_tcs=tc;
	while(tc--){
		solve(total_tcs-tc);
	}
	return 0;
}
