////////dynamic segment tree 


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

const long long oo = 4e18;///////fixed:::make it greater than any sum or element or whatever



///what is edited??
/*
	update in the TreeNode
	in the end of update function 
	in the end of query function
	neutral value
*/




struct TreeNode{
	long long sum=0;
	///fixed::here TreeNode not Node
	TreeNode *left=nullptr,*right=nullptr;
	void update(int val){/////reason of it explained downward
		sum+=val;
	}
};

using Node=TreeNode*;////to avoid forgetting the * 

struct DynamicSegTree{
	
	int L,R;
	Node root;
	
	DynamicSegTree(int l, int r){////range of the numbers
		L=l;
		R=r+1;////////fixed::::important because half open interval logic
		root = new TreeNode;
		
	}
	
	///////////////////
	void update(int idx,int val,Node &node,int lx,int rx){
		
		if(rx-lx == 1){
				//////we used upate internally from it to avoid creating a new one that is not pointed to it
			node->update(val);
			return;
		}
		
		int mid=(lx+rx)>>1;
		if(idx<mid){
			if(node->left == nullptr) node->left=new TreeNode();
			update(idx,val,node->left,lx,mid);
		} else {
			if(node->right == nullptr) node->right = new TreeNode();
			update(idx,val,node->right,mid,rx);
		}
		
		
		//if we used the ((normal) merge) it will be wrong
			//because it creates a new node and cut the pointer to the old node
		node->sum= 
			(node->left==nullptr ? 0 : node->left->sum)
			+ 
			(node->right==nullptr ? 0 : node->right->sum);
		//if it is nullptr then the nodes down of it were not edited , so their answer is the neutral value
			//we use -> because we can't use . with the pointers
		//////////////we made sure firstly that the node is not nullptr
			//ok we can make a one if empty but this is waste of memory (2xmemory)
					//so the used approach is : //if not existed then use neutral value
		
		///fixed: we use parantheses(?:) because ?: has lower precendence than +
		
		
	}
	
	
	//////////////////
	
	
	
	long long query(int l,int r, Node &node ,int lx, int rx){
		
		
		//////fix:::::::::::::::>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			//// checking if nullptr after if checking if it is outofrange not vice versa xxxxxxxxxx
		
		/////this zero is not the same as the next one
		if(lx>=r||rx<=l)return 0;//the neutral value
		if(node==nullptr)return 0;//depend on the array intialization
									//for ex: the array was ones then it will be rx-lx (without +1 because it is [lx,rx) (half open interval) )
		
		
		if(lx>=l&&rx<=r) return node->sum;
			/////here we won't return nodes because we try to save memory
				/////////////because there is a problem in the struct that is made by a pointer:<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
					/////////////when creating with (new) , it is not deleted automatically so it is kept in memory which is soo bad<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		
		
		
		int mid=(lx+rx)>>1;
		
		long long left=query(l,r,node->left,lx,mid);
		long long right=query(l,r,node->right,mid,rx);
		
		return left+right;
	}
	
	
	
	///now building is merged with (query, and update)
	
	
	////notice that creating nodes is only happenning in the update fun. not in the get fun. !!!!!
	
	
	
	////////////////////////////////////////
	//wrappers (for easy calling) :
	
	void update (int idx,int val){
		update(idx,val,root,L,R);
	}
	
	long long query(int l, int r){
		return query(l,r,root,L,R);
	}
	
	
};
/*
	
	
	notice that now there is no need for coordinate compression 
		 coordinate compression need offline queries to know all values
		 			it needs offline queries because it need all values that are used to compress them before processing
		
		
		ok coordinate compression can be slower depending on the problem but this is not the goal
		and also in many practical cases dynamic segment tree takes more memory , so it is not about optimizing memory than coordinate compression
		,,,,but it is about making the whole range valid online
						(joke: it depends on the concept of use as go (like concept of cloud computing))
	
	
	_______________________________________________
	
	
	how is it accepting negative indices?
	
	because no restriction of indices
	we used pointers so it is like this pointing to that and so on..
	
	so there is no need to shift negtaives or thing like this!!
					//i mean there is no need for coordinate shifting
	
	
*/



/*
	what if he said intially the value at i1 is a1 and at i2 is a2 and ..
		//then use the update function to update them 
*/


///////note that :
//the path is created only if it has a leaf which is a node carrying one index (rx-lx==1) 
		// but there can't be any path without a node at the last down level 




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
