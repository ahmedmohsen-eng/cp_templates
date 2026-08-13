#include<bits/stdc++.h>
using namespace std;

struct node{
    int index,cost;
};

int n,m;
vector<vector<int>>adj;

//important:
//when using a directed one:
// vector<vector<node>>adj;

vector<bool>vis;

void bfs(int src){
    vis.assign(n+1,false);
    
    queue<int>q;
    
    vis[src]=true;
    q.push(src);
    
    while(!q.empty()){
        int u=q.front();
        q.pop();
        
        for(auto&v:adj[u]){
            if(!vis[v]){
                q.push(v);
                vis[v] = true;//fix
            }
        }
        
    }
    
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

vector<int>lvls;/////use the bfs_shortest_path(start) then lvls[end] to find the shortest path
                            //it can be start->end or end->start

void bfs_shortest_path(int src){
    lvls.assign(n+1,-1);
    
    queue<int>q;
    
    lvls[src] = 0;
    q.push(src);
    
    while(!q.empty()){
        int u=q.front();
        q.pop();
        
        for(auto&v:adj[u]){
            if(lvls[v]==-1){//////////
                lvls[v]=lvls[u]+1;////
                q.push(v);//////////
            }
        }
        
    }
    
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


//**********done :

//when target is unreachable (unconnected with the component for the current starting node)
///if you don't know whether the target is available you must use
//and (إن شاء الله) then before building you have to check if it is not -1 
/*
        if (dist[target] == -1)
            return {};
*/


vector<int>parent;
///bfs_shortest_path + building the path through parents
void bfs_build_shortest_path(int src){
    lvls.assign(n+1,-1);
    parent.assign(n+1, -1);////////////
    
    queue<int>q;
    
    vis[src]=true;
    q.push(src);
    
    while(!q.empty()){
        int u=q.front();
        q.pop();
        
        for(auto&v:adj[u]){
            if(lvls[v]==-1){
                lvls[v]=lvls[u]+1;
                parent[v] = u;//////////////////////
                q.push(v);
            }
        }
        
    }
    
}
//now get not build
//so use the build fun. then the get fun.
vector<int>path;
void bfs_get_shortest_path(int target){
    
    path.clear();
    
    //adding unreachable targets
    if(lvls[target] == -1)
        return;
    
    int cur=target;
    while(cur!=-1){
        path.push_back(cur);
        cur=parent[cur];//fix naming mistake
    }
    reverse(path.begin(), path.end());
}


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/////don't forget to path the sources vector
void multi_source_bfs(vector<int>&sources,int src){
    lvls.assign(n+1,-1);
    
    queue<int>q;
    
    for (int src : sources) { ///////////////////////
        lvls[src] = 0;
        q.push(src);
    }
    
    while(!q.empty()){
        int u=q.front();
        q.pop();
        
        for(auto&v:adj[u]){
            if(lvls[v]==-1){
                lvls[v]=lvls[u]+1;
                q.push(v);
            }
        }
        
    }
    
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

//********* important note :
///take care of naming when using : undirected not indirected

bool has_cycle_undirected_bfs(){    //same idea as dfs undirected check
    vis.assign(n+1,{});
    
    
    for(int i = 1; i <= n; i++){
        if(vis[i]) continue;
        
        queue<pair<int,int>>q;//child , parent
        
        q.push({i,-1});
        vis[i]=true;
        
        while(!q.empty()){
            auto[u,parent]=q.front();
            q.pop();
            
            for(auto&v:adj[u]){
                if(!vis[v]){
                    vis[v]=true;
                    q.push({v,u});
                } else if(v!=parent){
                    return true;
                }
            }
            
        }
        
        
    }
    
    return false;
}



//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


//now for the bfs idea for checking cycles in directed graphs it uses indegrees
                            //in dfs vis vector with 3 colours was used

//indegree method here is also called " Kahn's algorithm "

///////////////This is also the basis of BFS TOPOLOGICAL SORT.

bool has_cycle_directed_bfs(){
    
    vector<int>indegree(n+1,0);
    
    //firstly calculating indegrees
    for(int i = 1 ;i <= n; i++){
        for(auto&v:adj[i]){ //fixing name issue
            indegree[v]++;
        }
    }
    
    queue<int>q;
    
    for(int i = 1 ; i<= n; i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    
    int processed=0;
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        
        processed++;
        
        for(auto&v:adj[u]){
            indegree[v]--;
            
            if(indegree[v]==0){
                q.push(v);
            }
            
        }
        
    }
    
    return  processed!=n;
    
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

/////take care here it is not void 
////////it returns the topo vector 

//also take care:
    //if it has cycle it returns {}   (empty vector)

//also take care:
    /// do you need to reverse??
    

vector<int> topo_sort_bfs(){
    vector<int>indegree(n+1,0);
    
    vector<int>topo;///////////
    
    for(int i = 1; i <= n; i++){
        for(auto&v:adj[i]){
            indegree[v]++;
        }
    }
    
    queue<int>q;
    
    for(int i = 1 ;i <= n; i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    
    
    while(!q.empty()){
        int u=q.front();
        q.pop();
        
        topo.push_back(u);///////////
        
        for(auto&v:adj[u]){
            indegree[v]--;
            
            if(indegree[v]==0){
                q.push(v);
            }
        }
    }
    
    
    /////////take care :;///////////
        /// do you need to reverse??
    
    
    if((int)topo.size()!=n){///////////
        return {};
    }
    
    return topo;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


bool is_bipartite(){
    
    vector<int>color(n+1,-1);
    
    for(int i = 1 ;  i <= n; i++){
        if(color[i]!=-1) continue;
        
        queue<int>q;
        
        color[i]=0;
        q.push(i);
        
        while(!q.empty()){
            int u = q.front();
            q.pop();
            
            for(auto&v:adj[u]){
                if(color[v]==-1){
                    color[v]=2-color[u];// or : color[v]=color[u]^1;
                    q.push(v);
                } else if(color[v]==color[u]){
                    return false;
                }
            }
        }
        
    }
    return true;
}












///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////



/*
===========================================================
take care :


    A graph is a tree iff:

            1. It has n - 1 edges
            2. It is connected

    For an undirected graph, this is enough.

    Alternatively: (*****when directed)
        connected + no cycle
===========================================================
*/










signed main(){
    
    
    return 0;
}
