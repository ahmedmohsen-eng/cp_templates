#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>adj(n);
vector<bool>vis(n,false);


//best way

void DFS(int u){
    vis[u]=true;
    for(auto v:adj[u]){
        if(!vis[v]){ //here it acts like the base case
            DFS(v);
        }
    }
}

//another way 

/*
void DFS(int u){
    if(vis[u]) return; // the base case is here, but as said below(it is not the best way)
    vis[u]=true;
    for(auto v:adj[u]){
        DFS(v);
    }
    
    
}

//the problem here that you recurse even if already visited then you check if visited or not 
//      , which is not useful
*/
