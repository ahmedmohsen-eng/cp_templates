#include <bits/stdc++.h>

using namespace std;

bool multicases_ = true;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<typename T>
using ordered_multiset = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;

// #define int long long/////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef unsigned long long u64;
#define ull unsigned long long

void setIO(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}



///////////////////////////////////////////////////////////////////////////////////

struct MultiSet {
	
    
    int n;
    vector<long long> b;
	
    
    long long get(int idx) {
        long long ans = 0;
        while(idx > 0) {
            ans +=b[idx];
            idx -= idx & -idx;
        }
        return ans;
    }
	
	
    long long get(int l, int r) {
        return get(r) - get(l - 1);
    }
	
	
	int lower_bound(long long sum) { 
	//smallest index whose prefix sum is at least sum
		//here it is used on a fenwick tree based on a frquency array 
				// so we get number of numbers by setting each one value with 1 at its position
	
        int skip = 0;
		
        for(int step = n; step > 0; step >>= 1) {
            if(skip + step <= n && b[skip + step] < sum) {
                sum -= b[skip + step];
                skip += step;
            }
        }
        
		if(skip==n)return -1;//not found //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		
        return skip + 1;
    }
	
	
	/////////
	
	
	void insert(int val,long long cnt=1) {//insert here means put 1 here at the value
        while(val <= n) {
            b[val] += cnt;
            val += val & -val;
        }
    }
    
    void erase(int val,long long cnt=1){
    	long long old_cnt=get(val,val);//to make sure not deleing more than we have
    	cnt=min(cnt,old_cnt);
    	while(val <= n) {
            b[val] -= cnt;
            val += val & -val;
        }
    }
	
	int size(){
		return b[n];
	}
	
	
	int operator[](int idx){		//to use it for the object fen : fen[i]
		return lower_bound(idx);
	}
	
	
    MultiSet(int _n) {
		
        n = 1;
        while(n < _n) {
            n <<= 1;
        }
		
        b.assign(n + 1, 0);
    }
	
    
} ms(1e6) ; //defining it as global multiset before ending the struct

///////////////////////////////////////////////////////////////////////////////////

void pre_compute() {

}

///////note:
		// default of erase is 1 as same as insert , so erase default is 1 not erasing all as the natural multiset

void solve(int tc) {

    ms.insert(1,2);// 1 1     			,, it means add two 1s
    ms.insert(3,4); // 1 1 3 3 3 3 		,, it means add three 4s
    cout<<ms[2]<<endl;//should be second element which is 1
    cout<<ms[5]<<endl;//should be fifth element which is 3
    
    
    
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    pre_compute();

    int tc = 1;

    if(multicases_)
        cin >> tc;

    int total_tcs = tc;

    while(tc--) {
        solve(total_tcs - tc);
    }

    return 0;
}
