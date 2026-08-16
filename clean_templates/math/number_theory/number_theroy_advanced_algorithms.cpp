#include <bits/stdc++.h>
using namespace std;

// Advanced number theory algorithms (duplicated comprehensive content so this file is self-contained)
// Includes notes and placeholders for NTT and polynomial operations as well as full factorization and primality tools.

using ll = long long;
using u128 = __uint128_t;

inline ll mul_mod(ll a, ll b, ll mod) {
    return (ll)((u128)a * (u128)b % (u128)mod);
}

ll pow_mod(ll a, ll e, ll mod) {
    ll r = 1 % mod;
    a %= mod;
    while (e > 0) {
        if (e & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return r;
}

ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = (a >= 0) ? 1 : -1; y = 0; return llabs(a); }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll modinv(ll a, ll m) {
    ll x, y;
    ll g = extgcd(a, m, x, y);
    if (g != 1) return -1;
    x %= m; if (x < 0) x += m; return x;
}

static vector<ll> fact, ifact;
void init_factorials(int N, ll MOD) {
    fact.assign(N + 1, 1);
    for (int i = 1; i <= N; ++i) fact[i] = fact[i-1] * i % MOD;
    ifact.assign(N + 1, 1);
    ifact[N] = pow_mod(fact[N], MOD - 2, MOD);
    for (int i = N; i >= 1; --i) ifact[i-1] = ifact[i] * i % MOD;
}
ll nCr_mod_prime(int n, int r, ll MOD) { if (r<0||r>n) return 0; return fact[n]*ifact[r]%MOD*ifact[n-r]%MOD; }

vector<int> sieve_primes(int N) { vector<char> is(N+1,true); vector<int> primes; is[0]=is[1]=false; for(int i=2;i<=N;i++) if(is[i]){ primes.push_back(i); if ((ll)i*i<=N) for(int j=i*i;j<=N;j+=i) is[j]=false;} return primes; }

bool isPrime64(ll n) { if (n<2) return false; for (ll p : {2,3,5,7,11,13,17,19,23,29,31,37}) if (n%p==0) return n==p; ll d=n-1; int s=0; while((d&1)==0){d>>=1;++s;} auto check=[&](ll a){ ll x=pow_mod(a,d,n); if(x==1||x==n-1) return true; for(int r=1;r<s;r++){ x=mul_mod(x,x,n); if(x==n-1) return true;} return false;}; for (ll a : {2,325,9375,28178,450775,9780504,1795265022}){ if(a%n==0) continue; if(!check(a)) return false;} return true; }

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
ll Pollards_rho_single(ll n){ if(n%2==0) return 2; if(n%3==0) return 3; ll c=uniform_int_distribution<ll>(1,n-1)(rng); ll x=uniform_int_distribution<ll>(0,n-1)(rng), y=x; ll d=1; auto f=[&](ll x){ return (mul_mod(x,x,n)+c)%n; }; while(d==1){ x=f(x); y=f(f(y)); d=std::gcd<ll>(llabs(x-y), n); if(d==n) return Pollards_rho_single(n);} return d; }
void factor_pollard(ll n, vector<ll>& res){ if(n==1) return; if(isPrime64(n)){ res.push_back(n); return; } ll d=Pollards_rho_single(n); factor_pollard(d,res); factor_pollard(n/d,res); }
vector<pair<ll,int>> factorize_pollard(ll n){ vector<ll> facs; factor_pollard(n,facs); sort(facs.begin(),facs.end()); vector<pair<ll,int>> res; for(ll p:facs){ if(res.empty()||res.back().first!=p) res.push_back({p,1}); else res.back().second++; } return res; }

/* Error / Debug notes:
- Use mul_mod to avoid overflow; Pollard-Rho randomized behavior; Miller-Rabin deterministic bases for 64-bit.
*/

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr); return 0; }
