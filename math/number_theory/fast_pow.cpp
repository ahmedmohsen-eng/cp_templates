#include<bits/stdc++.h>
using namespace std;

int fastpow(int n,int m){ //when you want to use it: for ex: cout<<(n%mod,m);  (don't forget mod) 
//==>> result must be lower than mod 
// /or/ 
//  he tells you that you must print ans % mod 
    if(m==0) return 1;
    
    
    int ans=fastpow(n,m/2)%mod;
    ans=(ans*ans)%mod;
    
    if(m&1) ans=(ans*n)%mod;
    
    return ans;
    
}
