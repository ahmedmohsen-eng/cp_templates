#include<bits/stdc++.h>
using namespace std;

//take care: 
#define int long long ///////////////important ,, but take care of comparisons, for ex: min(x,0LL)

bool is_prime_or_no(int n){
    if(n==1||n==0)return false;//fix : don't forget this
    bool ok = true;
    for(int i = 2 ; i*i <= n; i++){
        if(n%i==0){
            ok=false;
            break;
        }
    }
    return ok;
}

// basic functions : prime_factors_basic,no_divisors_basic
// the first one to get ((prime)) factors
// the second one is to calculate number of divisors
vector<int>factors_basic;
void prime_factors_basic(int n){
    for(int i = 2; i*i<=n ;i++){
        while(n%i==0){
            factors_basic.push_back(i);
            n/=i;
        }
    }
    if(n>1)factors_basic.push_back(n);//last one if prime
}

int no_divisors_basic(int n){
    int cnt=1;//fix : count 1 so initalize with 1 because downward you started from 2
    for(int i = 2 ; i*i <= n; i++){ //fix : <= not <
        if(n%i==0){
            if (n==i*i) cnt++;
            else cnt+=2;
        }
    }
    return cnt;
}


///____________________________________________________________________________
///____________________________________________________________________________
///____________________________________________________________________________
///____________________________________________________________________________

// vector<bool> vs vector<char>
// vector<bool> is a special container: it stores one bit per element.
// vector<char> stores one byte per element.
// vector<bool> accesses are a little slower because reading or writing one element requires extra bit operations.
// However, vector<bool> uses 8x less memory. For very large arrays (such as the sieve), 
                // this can improve cache utilization and reduce memory traffic.
// Therefore, although vector<bool> has more expensive individual accesses,
            // it can be faster overall for large sieves 
                // because the reduction in memory bandwidth can outweigh the cost of the extra bit operations.
// Which one is faster depends on the algorithm, compiler, and hardware.

//_________
vector<bool> sieve(int n){
    //idea is to mark zero and one as not prime
    //then
    //mark all multiples of numbers starting from 2 as not prime till n
    // and if true so it leave it , as it is prime because it was not marked before 
                //===> as if was not prime so it would be marked from primes before it
    
    
    //start from current_prime*2 (first muliple of it (of course no*1 because it is itself which is prime))
    //optimized to walk from current_prime*current_prime
    //then walk till you reach n
    
    vector<bool> isprime(n+1,true);//+1 to take the number itself 
    //after n+1 also this part is safe which is initializing 0 and 1
    isprime[0]=isprime[1]=0;
    for(int i=2 ; i*i <=n; i++){ //fix : forgetting the i*i instead of i <<<<<<<<<<<<<<<<<<<<<===============fix
        if(isprime[i]){
            //instead of writing 
            for(int j = i*i; j <= n ; j+=i){ //optimized instead of walking from i*2
            //why it is true , this is because:
            //The reason is that every multiple smaller than i^2 has already been marked by a smaller prime.
            //for example if you have i=5 if you looked at 3*5 , then actually it was marked by 3 muliples and so on...
                isprime[j]=false;
            }
        }
    }
    
    //complexity of sieve :
    //it was O(nloglogn) 
    // and also it is still O(nloglogn) 
    // this is because starting fromi*i instead of i*2 only imoprves (decreases) the constant factor
    
    //  n + n/3 + n/4 + n/5     it is called harmonic series which is equal to n Ln n (complexity of nlogn) 
    
    return isprime;
}
///____________________________________________________________________________
///____________________________________________________________________________
///____________________________________________________________________________
///____________________________________________________________________________
///____________________________________________________________________________

//fix : make it with type int not bool
vector<int>smallest_prime_factor;//making it global to be seen by the both functions

//prime factorization with sieve:
void sieve_with_factorization(int n){
    
    //we want to store only one prime divisor for every number and if prime store itself
    //then to factorize it , divide it by current prime divisor 
            // and then you get a number then divide it by its prime divisor ... till you reach one
                    //complexity is O( nloglogn ) also
    smallest_prime_factor.assign(n+1,0);//0 and 1 are zeros here
    
    vector<int>isprime(n+1,true);//fix 1, 3 : initalize with true not false, vector of ints not of bools
    isprime[0]=isprime[1]=0;
    for(int i=2;i<=n;i++){
        if(isprime[i]){
            
            smallest_prime_factor[i]=i;
            
            for(int j = i*i ;j<=n ;j+=i){//fix 2 : j+=i not j++
                isprime[j]=false;
                
                if(smallest_prime_factor[j]==0) // to store least prime factor
                    smallest_prime_factor[j]=i;
                
            }
        }
    }
    ;//currently writing as void
}

vector<int>prime_factors_for(int x){
    vector<int>prime_factors_local;
    //comlexity only for each number is log n , i mean here after the previous function was executed
    
    int cur_prime_factor;
    while(x!=1){
        cur_prime_factor=smallest_prime_factor[x];
        prime_factors_local.push_back(cur_prime_factor);
        x/=cur_prime_factor;
    }
     
    return prime_factors_local;//fix : return the local vector not the global one
}


//precomputation : divisors for all numbers from 1 to n
//how it works? : 
    // for each number from 1 to n : 
        //  reach each number mutliples and increase the number of divisors
vector<int>divisors;
void cnt_divisors_1toN(int n){
    divisors.assign(n+1,0);
    for(int i = 1 ; i<=n ; i++){
        for(int j = i; j<=n ; j+=i){
            divisors[j]++;
        }
    }
} //complexity : O(nlogn) ,, also the inside loop was not counted because it is a small constant :

//you have n*(1+1/2+1/3+1/4........) which means complexity is n times the inner complexity which is ln or (logn)
// 1+1/2+1/3+1/4+...... which is the harmonic series
// approximately the summation is ln(n)    (approximately)   
                    //  even it diverges to infinity but because you are not counting inifinity numbers, you have a limit


//to calculate number of divisors you can find primefactorization for the number
    // then find each prime factor occurence
            // for example 24 = 2*2*2 * 3  = 2 pow 3  * 3 pow 1
                //to find them which are "1, 2, 3, 4, 6, 8, 12, 24" (8 divisors)
            // you can muliplty each power+1 into each other , see:
            // for the (24) : 2 pow 3  *  3 pow 1  , so the powers are 3,1
            // so do : (3+1) * (1+1)   ,, the +1 is because if the number was not taken (power zero)
                //which gives the correct answer of 24
    //another example for 2pow1 * 3pow1 which is 2*3=6
    //you have 4 divisors which are "1, 2, 3, 6"
    //powers:1,1 so ans=(1+1) * (1+1) =4


//note that:
//the least number of divisors for any number is 2 when the number is prime

//any number has even number of divisors if not complete square, but odd if it is a complete square

//to have 3 divisors only, two of them is 1,and the number itself


#define add_mod(a,b,m) ( ( (a%m)+(b%m) +m )% m ) 
#define sub_mod(a,b,m) ( ( (a%m)-(b%m) +m )% m )

// #define mul_mod(a,b,m) ( (   (((a%m)+m)%m)*(((b%m)+m)%m)   %m   )% m )  //no need for another+m before the last modulus because now both are positive
//the previous one may overflow , so use this:store as __int128 then return as long long

inline long long mul_mod(long long a, long long b, long long m) {
    a = (a % m + m) % m;    //because (a + m) % m works only when a is at least -m
    b = (b % m + m) % m;
    return (__int128)a * b % m;
}

constexpr double EPS = 1e-9;
constexpr int INF = 1 << 30, Mod = 1e9 + 7;
constexpr long long LINF = 1LL << 62;
const char* yes = "YES\n";
const char* no  =  "NO\n";


#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << ": " << (x) << "\n";
#else
#define debug(x)
#endif

// int mod=1e9+7; 
// //using prime why in making answer smaller?? 
//          may be because it has no factors other than ones? 
//                  but why does this matter if right?? 
// or what??

// int mod=1e9+7; //don't forget this : you can change it to be used in the function
int fastpow(int n,int m,int mod=1e9+7){ //when you want to use it: for ex: cout<<(n%mod,m,mod);  (don't forget mod) 
//==>> result must be lower than mod 
// /or/ 
//  he tells you that you must print ans % mod 
    if(m==0) return 1;
    
    
    int ans=fastpow(n,m/2,mod)%mod;
    ans=(ans*ans)%mod;
    
    if(m&1) ans=(ans*n)%mod;
    
    return ans;
    
}



/* 
____________________________________________________________________________________________________________________
_______________________________________________________________________________________________________
___________________________________________________________________________________
__________________________________________________________________
________________________________________________
functions you have tell now here :

1-to precompute number of divisors for range of numbers*******
void (cnt_divisors_1toN)  ===>> use with the global vector (divisors)


2-to have a vector of prime factors for any number*******
void (sieve_with_factorization) ===>>
         with the global vector(smallest_prime_factor) to store one prime divisor 
                            (here: the smallest) for each number ,, complexity : nloglogn
,,,then,,,
vector<int> (prime_factors_for) ==>   ,, complexity : logn


3-to precompute isprime or not*******
vector<int> sieve  ====>>    ,, complexity : nloglogn 


and also some basic functions at the beginning

and may be other functions like :    fastpow
*/







//don't forget pre processing is not processed each time

bool multi_cases = false ;

void solve(const int& t){
    //dbg:
    // cerr<< "\ntest case no." << t << " debugging : \n";
    //end_dbg
    
    //if the output is very large don't forget to make this as comment : freop("out.txt","w",stdout); 
    // to avoid program crashing

    //fixed : 
    //when i say prime divisors that is a small mistake , i mean prime factors!!!!!!!!!!!!!!!
    //don't forget +1 in functions to handle the limit number itself
    //recopy it to github and current files
    
    
    
    
    
    
    
    
    
    
    
    
    
}

signed main(){
    
    cin.exceptions(cin.failbit);// important to know wrong input (sometimes)
    
    ios::sync_with_stdio(0);cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    
    int test_cases=1;
    if(multi_cases)cin>>test_cases;
    for(int i = 1 ; i <= test_cases; i++){
        solve(i);
    }
    
    //test_cases are 1-indexed
    
    return 0;
}
