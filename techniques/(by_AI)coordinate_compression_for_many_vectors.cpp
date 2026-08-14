#include<bits/stdc++.h>
using namespace std;


// Coordinate compression for MANY vectors
// All vectors use the SAME compression mapping.
//
// If you want 1-indexed:
// - each vector should be of size n+1
// - index 0 is ignored
//
// If you want 0-indexed:
// - change the loops accordingly
void coord_comp_not_best(vector<vector<int>>&v){//must be by reference

    vector<int>sorted;

    // Put all values from all vectors into one vector
    for(auto&vec : v){
        for(int i = 1 ; i < vec.size() ; i++){
            sorted.push_back(vec[i]);
        }
    }

    sort(sorted.begin(),sorted.end());

    unordered_map<int,int>pos;

    // Give every distinct value a compressed coordinate
    int cnt = 0;

    for(int i = 0 ; i < sorted.size() ; i++){
        if(i == 0 || sorted[i] != sorted[i-1]){
            pos[sorted[i]] = ++cnt;
        }
    }

    // Replace every value in every vector
    for(auto&vec : v){
        for(int i = 1 ; i < vec.size() ; i++){
            vec[i] = pos[vec[i]];
        }
    }
}


// Example
int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n,m;
    cin >> n >> m;

    vector<vector<int>>v(m,vector<int>(n+1));

    for(int j = 0 ; j < m ; j++){
        for(int i = 1 ; i <= n ; i++){
            cin >> v[j][i];
        }
    }

    coord_comp_not_best(v);

    for(int j = 0 ; j < m ; j++){
        for(int i = 1 ; i <= n ; i++){
            cout << v[j][i] << ' ';
        }
        cout << '\n';
    }
}
