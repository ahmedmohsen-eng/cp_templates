//instead of using the program stack to recurse states :
//  you simulate it (not exactly , but the same logic) using your own stack to store numbers needed to check

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>adj(n);
vector<bool>vis(n,false);

void DFS(int start){
    
    stack<int>st;//don't forget that you wrote it here as st not s   , focus on names <<<<<<<<<<<<<<<<<<<<<<<<
    st.push(start);
    
    while(!st.empty()){
        int u = st.top();
        st.pop();
        
        if(vis[u]) continue;
        
        vis[u]=true;//mark before push
        
        //
        for(int v : adj[u]){
            if(!vis[v]) st.push(v);
        }
        //////////if you want the same order of recursive you this:
        //
        //for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) // the "++" goes from rbegin goes to rend  
                                                                            // r.end()  <<< to <<<  r.begin()
        //  st.push(*it);
        //
        // you reversed here because in stack: last in first out (LIFO)
            //but in vector it is ordered normally by index
    }
    
}
