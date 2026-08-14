#include<bits/stdc++.h>
using namespace std;


//if you want 1-indexed you can 
//else you can do it normal 
void coord_comp_not_best(vector<int>&v){//it must be by reference
    vector<int>sorted(v.begin(),v.end());//this is the same as : vector<int>sorted=v;
    sort(sorted.begin(),sorted.end());
    unordered_map<int,int>pos;
    
    
    //important*******************
    //note that here:
    //we started from i=1 supposing that the vector recieved was of size n+1
    for(int i = 1 ; i < sorted.size() ; i++) pos[sorted[i]]=i;    
    
    for(auto&x:v)x=pos[x];
}

//example for usage:
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //don't forget here in this example it is the standard stdin,stdout
    int n; cin>>n;
    vector<int>v(n+1);//to make coord_comp start from 1 not zero
    for(int i = 1; i <= n ; i++)cin>>v[i];//then take from i =1
    coord_comp_not_best(v);
    
    //also don't foget to output starting from index 1 , becuase vector accepted by the fucntion logic is 1-indexed(you can edit it to accept 0-indexed)
    for(int i = 1; i <= n ; i++)cout<<v[i]<<' ';
}
