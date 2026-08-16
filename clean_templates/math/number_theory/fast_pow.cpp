#include <bits/stdc++.h>
using namespace std;

// Fast exponentiation (binary exponentiation)
long long fast_pow(long long a, long long e, long long mod){
    long long r=1; a%=mod;
    while(e){ if(e&1) r=(__int128)r*a%mod; a=(__int128)a*a%mod; e>>=1; }
    return r;
}

/* Error/debug notes: none */
