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
// #define int long long//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<??
typedef unsigned long long u64;//this or the one  below
#define ull unsigned long long




//the sparse table was built to use non-empty intervals only
	//////so handle this through edge cases !!!!!!!!!!!!!!!!!!!!!




///////condition to use sparse table for some property : 
	// suppose the propoerty is a function :
		// fun(x,x)=x
			//for example : min(x,x)=x
							//but : sum(x,x)!=x , but it is equal to 2x 
	
	//why this :
		// because :
			// we recalculate the same value many times to build the table



//////////////note  :  the query must be the same indexing system as array input (0/1 indexing)

//////////but for the sparse table it doesn't matter because always you can put empty additional space and it doesn't matter
					///////it doesn't matter  because when you query you query on the available data

/////building : nlogn . x     ,        query : O(x)           and x is the time of operation (merge function)

struct SparseTable {	//known as RMQ : Range Minimum Queries
	
	vector<vector<int>>data;
	vector<int>logs;
	
	
	
	///////////////////////////////////////////////the only thing to edit :
	
	int merge(int &lf,int &rt){	//////change this to the function you want <<<<<<<<<
		return min(lf,rt);//left,right
	}
	
	////////////
	
	
	SparseTable(vector<int>&arr){ /// constructor
		
		int n = arr.size();
		
		logs.assign(n+1,0);//we made 0 and 1 value with 0, all next depend on previous
		for(int i = 2 ;i <= n; ++i){//loop from 2 not 0 nor 1 ,,,,, fix!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			logs[i]=logs[i/2]+1;
		}
		
		data.assign(logs[n]+1,vector<int>(n));
		data[0]=arr;
		
		for(int i = 1 ;i <=logs[n];++i){
			int len=1<<i;//1,2,4,8,16 (length of window)
			for(int j = 0 ; j+len-1<n;++j){
				data[i][j] = merge( data[i-1][j] , data[i-1][j+(len>>1)] );//merge
						//the last one means :          ^
							// last row,    same column + half length 
			}
		}
		
		
	}	//end of constructor
	
	int get (int l, int r){
		int len = r-l+1;
		int level = logs[len];	///length of window
		/////(l ...).. r
		/////l ..(... r)
		////////here first window start is l
		///////second window start is r-(window size)+1   ,, window size is log(level)
		////window size is greatest number which is power of 2 and smaller or equal to length
		
		
		return merge(data[level][l],data[level][r-(1<<level)+1]);
	}
	
};






void pre_compute(){
		
	
	
}









void solve(int tc){
	// //dbg:
	 // cerr<<"at the test case no."<<tc<<" : \n";
	
	int n,q; cin>>n>>q;
	vector<int>arr(n+1);//don't forget n+1 (if you want it like this to be always fitting the size(converting to 1-indexing))
								////as said some empty spaces wouldn't make problems because they woudn't be used
	for(int i = 1 ;i <= n; ++i){
		cin>>arr[i];
	}
	
	
	
	//creating the data structure
	SparseTable st = SparseTable(arr);
	
	
	
	//query on it !!
	while(q--){
	
	
		int l,r;
		cin>>l>>r;
		cout<<st.get(l,r)<<'\n';//getting the ans
				//don't forget endline
		
		
		
		//, if it is 0-indexed don't forget : --l,--r 
	}
	
	
	
	

}


///////////some notes , tips and tricks:
////////////if you want to get summation how to do that because overlapping happen ?????mmmmmm...:
		/////////// :
		///////////////// you can divide it into its binary representation of the length:
			//for example :
			/// summation from element 2 to element 8
			//////length=7
				///////binary representation 111
					///////so take 4 elements then 2 elements then 1 elements    , and add them
											//////(power of 2 jumps)<<<<<<<<<<<<<<<<<
						////////which happens in log(n)
								//////so if prefix can calculate it , use it because of the O(1)calculation
									/////but if prefix can't do it and have overlapping then use this method
												/////////////but it is rarely (rarely) appear  in problems(if appeared !!!!!)





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
