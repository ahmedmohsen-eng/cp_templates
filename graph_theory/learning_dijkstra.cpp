#include<bits/stdc++.h>
using namespace std;

strcut node {
    int idx,cost;////take care of naming , for example idx or index ????? mmmmm..
};

struct cmp{
    bool operator()(node&a,node&b){
        return a.cost > b.cost;///////what if cost is equal???? it doesn't matter any one comes first
    }
};// fix ::::: don't forget the ;

int n,m;
vector<vector<node>>adj;
vector<bool>vis;

//time complexity : O((V+E)logV)​
//for a connected graph : O(ElogV)​    because if it is connected then E≥V−1.

int dijkstra(int src,int target){
    priority_queue<node,vector<node>,cmp>pq;
    
    //fix ::::: naming issue (src not st (focus!!))
    pq.push({src,0});//the priroity is always for the node with the lowest cost
    
    while(!pq.empty()){ //same as : while((int)pq.size())
        
        //fix ::::: its type is node not int!!!!
        node u = pq.top();
        pq.pop();
        
        if(u.idx==target){//if found target return the cost
                //and take care there couldn't be lower than it because of the priority queue
            return u.cost;
        }
        
        if(vis[u.idx]){//if vis continue (but after checking if it is the target)
            continue;
        }
        
        vis[u.idx]=true;//fix ::::: naming issue (idx not index (focus!!))
        for(auto&v:adj[u.idx]){
            if(!vis[v.idx]){ 
                //When a vertex is popped from the priority queue for the first time, 
                        // it has its minimum possible distance.
                pq.push({v.idx,u.cost+v.cost});///fix ::::: naming issue (idx not index (focus!))
            }
        }
        
    }
    
    return -1;
}

signed main(){
    
    
    return 0;
}
