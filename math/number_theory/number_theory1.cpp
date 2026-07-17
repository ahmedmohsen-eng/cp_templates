#include<bits/stdc++.h>
using namespace std;

//take care: 
#define int long long ///////////////important ,, but take care of comparisons, for ex: min(x,0LL)

const char* yes = "YES\n";
const char* no = "NO\n";

bool is_prime(int n){
    bool ok = true;
    for(int i = 2 ; i*i <= n; i++){
        if(n%i==0){
            ok=false;
            break;
        }
    }
    return ok;
}


vector<int>factors;
void prime_factor(int n){
    for(int i = 2; i*i<=n ;i++){
        while(n%i==0){
            factors.push_back(i);
            n/=i;
        }
    }
    if(n>1)factors.push_back(n);//last one if prime
}

int no_divisors(int n){
    int cnt=0;
    for(int i = 2 ; i*i < n; i++){
        if(n%i==0){
            if (n/i==i) cnt++;
            else cnt+=2;
        }
    }
    return cnt;
}


///____________________________________________________________________________
///____________________________________________________________________________
///____________________________________________________________________________
///____________________________________________________________________________
vector<bool> sieve(int n){
    //bool vs char:
    //char is (sometimes) faster because it is bit by bit ,, but bool is bits beside each other
    //but when i tried both actually (bool) was faster in the sieve
    //this is because:
    //the sieve runs alot of times may be millions
    //which mean that char takes more memory so it much less fits in cpu caches 
    //so once the array becomes much larger than the array than the CPU's cache,
                                // memory bandwidth becomes a bottleneck
    //          So although each access to vector<bool> requires extra bit operations, 
    //              those bit operations are very cheap. The reduction in memory traffic can outweigh their cost.
    
    
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
    for(int i=2 ; i <=n; i++){
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
    //it was O(nlogn) 
    // but enhanced to nloglogn 
    // this happenedafter making it starting fromi*i instead of i*2
    
    //  n + n/3 + n/4 + n/5     it is called harmonic series which is equal to n Ln n (complexity of nlogn) 
    
    return isprime;
}
///____________________________________________________________________________
///____________________________________________________________________________
///____________________________________________________________________________
///____________________________________________________________________________
///____________________________________________________________________________

//fix : make it with type int not bool
vector<int>prime_divisors;//making it global to be seen by the both functions

//prime factorization with sieve:
void sieve(int n){
    
    //we want to store only one prime divisor for every number and if prime store itself
    //then to factorize it , divide it by current prime divisor 
            // and then you get a number then divide it by its prime divisor ... till you reach one
                    //complexity is O(  )
    prime_divisors.assign(n+1,0);//0 and 1 are zeros here
    
    vector<int>isprime(n+1,true);//fix 1, 3 : initalize with true not false, vector of ints not of bools
    isprime[0]=isprime[1]=0;
    for(int i=2;i<=n;i++){
        if(isprime[i]){
            
            prime_divisors[i]=i;
            
            for(int j = i*i ;j<=n ;j+=i){//fix 2 : j+=i not j++
                isprime[j]=false;
                
                if(prime_divisors[j]==0) // to store least prime factor
                    prime_divisors[j]=i;
                
            }
        }
    }
    ;//currently writing as void
}

vector<int>prime_divisors_for(int x){
    vector<int>prime_factors;
    //comlexity only for each number is log n , i mean here after the previous function was executed
    
    int cur_prime_divisor;
    while(x!=1){
        cur_prime_divisor=prime_divisors[x];
        prime_factors.push_back(cur_prime_divisor);
        x/=cur_prime_divisor;
    }
    
    return prime_factors;
}




// int mod=1e9+7; 
// //using prime why in making answer smaller?? 
//          may be because it has no factors other than ones? 
//                  but why does this matter if right?? 
// or what??






//don't forget pre processing is not processed each time

bool multi_cases = false ;

void solve(const int& t){
    //dbg:
    // cerr<< "\ntest case no." << t << " debugging : \n";
    //end_dbg
    
    
    
    
}

signed main(){
    
    cin.exceptions(cin.failbit);// important to know wrong input (sometimes)
    
    ios::sync_with_stdio(0);cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    #endif
    
    int test_cases=1;
    if(multi_cases)cin>>test_cases;
    for(int i = 1 ; i <= test_cases; i++){
        solve(i);
    }
    
    //test_cases are 1-indexed
    
    return 0;
}
