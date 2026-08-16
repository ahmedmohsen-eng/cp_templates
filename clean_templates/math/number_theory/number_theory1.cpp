#include <bits/stdc++.h>
using namespace std;

// Comprehensive Number Theory Template (duplicated here so each file is self-contained)
// Contains: modular arithmetic, fast pow, extgcd, modinv, factorials (fact/ifact), nCr mod prime,
// sieve (linear), prime factorization, Euler phi, mobius, divisors, Miller-Rabin, Pollard-Rho,
// CRT, Baby-Step Giant-Step (discrete log), and helpers.

using ll = long long;
using u128 = __uint128_t;

// -------------------- modular arithmetic --------------------
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

// -------------------- extended gcd / modular inverse --------------------
ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = (a >= 0) ? 1 : -1; y = 0; return llabs(a); }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// inverse of a mod m (when gcd(a,m)=1)
ll modinv(ll a, ll m) {
    ll x, y;
    ll g = extgcd(a, m, x, y);
    if (g != 1) return -1; // inverse doesn't exist
    x %= m;
    if (x < 0) x += m;
    return x;
}

// -------------------- factorials and nCr mod prime --------------------
static vector<ll> fact, ifact;

void init_factorials(int N, ll MOD) {
    fact.assign(N + 1, 1);
    for (int i = 1; i <= N; ++i) fact[i] = fact[i-1] * i % MOD;
    ifact.assign(N + 1, 1);
    ifact[N] = pow_mod(fact[N], MOD - 2, MOD); // Fermat inverse, MOD must be prime
    for (int i = N; i >= 1; --i) ifact[i-1] = ifact[i] * i % MOD;
}

ll nCr_mod_prime(int n, int r, ll MOD) {
    if (r < 0 || r > n) return 0;
    return fact[n] * ifact[r] % MOD * ifact[n-r] % MOD;
}

// -------------------- sieve (linear) and primes --------------------
void linear_sieve(int N, vector<int>& primes, vector<int>& lp) {
    lp.assign(N + 1, 0);
    primes.clear();
    for (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) { lp[i] = i; primes.push_back(i); }
        for (int p : primes) {
            if (p > lp[i] || (ll)i * p > N) break;
            lp[i * p] = p;
        }
    }
}

vector<int> sieve_primes(int N) {
    vector<char> is(N+1, true);
    vector<int> primes;
    is[0]=is[1]=false;
    for (int i=2;i<=N;i++) if (is[i]){
        primes.push_back(i);
        if ((ll)i*i<=N) for (int j=i*i;j<=N;j+=i) is[j]=false;
    }
    return primes;
}

// -------------------- factorization --------------------
// trial division using primes list
vector<pair<ll,int>> factorize_trial(ll n, const vector<int>& primes) {
    vector<pair<ll,int>> res;
    for (int p : primes) {
        if ((ll)p * p > n) break;
        if (n % p == 0) {
            int c = 0;
            while (n % p == 0) { n /= p; ++c; }
            res.push_back({p, c});
        }
    }
    if (n > 1) res.push_back({n, 1});
    return res;
}

// -------------------- Euler Phi and mobius --------------------
ll phi_single(ll n) {
    ll res = n;
    for (ll p = 2; p*p <= n; ++p) if (n%p==0) {
        while (n%p==0) n/=p;
        res -= res / p;
    }
    if (n>1) res -= res/n;
    return res;
}

vector<int> mobius_sieve(int N) {
    vector<int> mu(N+1, 1), primes; vector<int> lp(N+1,0);
    for (int i=2;i<=N;i++){
        if (!lp[i]){ lp[i]=i; primes.push_back(i); mu[i]=-1; }
        for (int p:primes){ if (p>lp[i] || i*(ll)p>N) break; lp[i*p]=p; if (i%p==0) mu[i*p]=0; else mu[i*p]=-mu[i]; }
    }
    return mu;
}

// -------------------- divisor count and sum --------------------
ll number_of_divisors_from_factors(const vector<pair<ll,int>>& fac){
    ll res=1; for (auto &pr:fac) res *= (pr.second+1); return res; }
ll sum_of_divisors_from_factors(const vector<pair<ll,int>>& fac){
    ll res=1; for (auto &pr:fac){ ll p=pr.first; int e=pr.second; ll term=1, cur=1; for (int i=1;i<=e;i++){ cur*=p; term+=cur; } res*=term; } return res; }

// -------------------- Miller-Rabin primality test --------------------
bool isPrime64(ll n) {
    if (n < 2) return false;
    for (ll p : {2,3,5,7,11,13,17,19,23,29,31,37}){
        if (n%p==0) return n==p;
    }
    ll d = n-1; int s = 0; while ((d&1)==0){ d>>=1; ++s; }
    auto check = [&](ll a)->bool{
        ll x = pow_mod(a, d, n);
        if (x==1 || x==n-1) return true;
        for (int r=1;r<s;r++){
            x = mul_mod(x,x,n);
            if (x==n-1) return true;
        }
        return false;
    };
    // Deterministic bases for 64-bit integers
    for (ll a : {2,325,9375,28178,450775,9780504,1795265022}){
        if (a%n==0) continue;
        if (!check(a)) return false;
    }
    return true;
}

// -------------------- Pollard Rho factorization --------------------
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll Pollards_rho_single(ll n) {
    if (n%2==0) return 2;
    if (n%3==0) return 3;
    ll c = uniform_int_distribution<ll>(1, n-1)(rng);
    ll x = uniform_int_distribution<ll>(0, n-1)(rng);
    ll y = x;
    ll d = 1;
    auto f = [&](ll x){ return (mul_mod(x,x,n) + c) % n; };
    while (d==1) {
        x = f(x);
        y = f(f(y));
        d = std::gcd<ll>(llabs(x-y), n);
        if (d==n) return Pollards_rho_single(n);
    }
    return d;
}

void factor_pollard(ll n, vector<ll>& res) {
    if (n==1) return;
    if (isPrime64(n)) { res.push_back(n); return; }
    ll d = Pollards_rho_single(n);
    factor_pollard(d, res);
    factor_pollard(n/d, res);
}

vector<pair<ll,int>> factorize_pollard(ll n){
    vector<ll> facs; factor_pollard(n, facs); sort(facs.begin(), facs.end());
    vector<pair<ll,int>> res; for (ll p: facs){ if (res.empty() || res.back().first!=p) res.push_back({p,1}); else res.back().second++; }
    return res;
}

// -------------------- Chinese Remainder Theorem --------------------
// Returns (x, m) where x is solution modulo m, or (0, -1) if no solution
pair<ll,ll> crt_pair(ll a1, ll m1, ll a2, ll m2){
    ll x, y; ll g = extgcd(m1, m2, x, y);
    if ((a2 - a1) % g != 0) return {0, -1};
    ll l = m1 / g * m2;
    ll mul = ((a2 - a1) / g % (m2/g) + (m2/g)) % (m2/g);
    ll inv = (x % (m2/g) + (m2/g)) % (m2/g);
    ll t = mul_mod(mul, inv, m2/g);
    ll r = (a1 + (u128)m1 * t) % l;
    if (r<0) r+=l;
    return {r, l};
}

// -------------------- Baby-Step Giant-Step (discrete log) --------------------
// solve a^x = b (mod m), returns x or -1 if no solution
ll discrete_log(ll a, ll b, ll m){
    a%=m; b%=m;
    if (m==1) return 0;
    ll cnt = 0; ll t = 1;
    for (ll g; (g=std::gcd(a,m))>1;){
        if (b==t) return cnt;
        if (b%g) return -1;
        b/=g; m/=g; t = mul_mod(t, a/g, m); cnt++;
    }
    ll n = (ll) sqrt(m) + 1;
    unordered_map<ll,ll> vals;
    ll an = 1;
    for (ll i=0;i<n;i++) an = mul_mod(an, a, m);
    ll cur = b;
    for (ll q=0;q<n;q++){
        vals[cur]=q;
        cur = mul_mod(cur, a, m);
    }
    cur = 1;
    for (ll p=1;p<=n+1;p++){
        cur = mul_mod(cur, an, m);
        if (vals.count(cur)){
            ll ans = p*n - vals[cur];
            if (ans < m) return ans;
        }
    }
    return -1;
}

// -------------------- Lucas Theorem (nCr mod prime) --------------------
ll nCr_lucas(ll n, ll r, ll p) {
    if (r==0) return 1;
    ll ni = n % p, ri = r % p;
    if (ri > ni) return 0;
    return nCr_lucas(n/p, r/p, p) * nCr_mod_prime(ni, ri, p) % p;
}

// -------------------- Usage examples (commented)
/*
// Example: initialize factorials for mod=1e9+7
const ll MOD = 1000000007;
init_factorials(1000000, MOD);
// nCr: nCr_mod_prime(n,r,MOD)

// Prime list
auto primes = sieve_primes(1000000);

// Factorization (trial)
auto fac = factorize_trial(1234567890LL, primes);

// Fast primality
if (isPrime64(1000000007)) {
    // prime
}

// Pollard factorization
auto fac2 = factorize_pollard(600851475143LL);

// CRT
auto sol = crt_pair(r1,m1,r2,m2);
if (sol.second==-1) // no solution

// Discrete log
ll x = discrete_log(a,b,mod);
*/

// -------------------- Error / Debug / Fix notes (one block, per-file)
/*
- Overflow: use mul_mod with 128-bit intermediate (u128) for safe multiplication mod 64-bit modulus.
- MOD must be prime for factorial inverse via Fermat; otherwise use extgcd-based inverses.
- Miller-Rabin bases used are deterministic for 64-bit integers. For larger ranges, adjust bases.
- Pollard-Rho is randomized; factorization may fail rarely; retrying is fine.
- discrete_log: handle gcd reductions first; be careful with modulus reductions.
- When using nCr_lucas, ensure n and r are non-negative and p is prime.
- Precompute factorial arrays to required N before queries to avoid O(N) in hot loops.
*/

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
