#include<bits/stdc++.h>
using namespace std;

#define int long long


//a-b is divisible for gcd(a,b).....why?
//because
//a/g is integer and b/g is integer ==>> so a/g - b/g is also integer ,,, 
                                    ///and since (a-b)/g is also an integer so a-b is divisible by g
                                                                                //*g here is the gcd
//and so a,b,a-b has the greatest common divisor(gcd)= g   i mean   (gcd(a,b)=gcd(a,a-b)=gcd(b,a-b))
// so gcd(a,b)=gcd(b,a-b)

//instead of repeating substraction , use modulus

int gcd(int a, int b){
    
    ////////fix:::::::::::don't forget abs of a to consider edge case if it was negative
                                            //for example if he inputed gcd(-1,0) so it is 1 not -1
                                                    //gcd mathematically is positive
    if(b==0)return abs(a);//this depends on that gcd between 0 and x is |x|
    return gcd(b,a%b);
    /////////////////////this function also is suitable even b is larger than a or vice versa
                                        //because : suppose : a = 3 and b = 9
                            //after one operation a=9(previous b)  and b=a%(previous b)=3%9=3
                                //so even if a is smaller they are swapped in one operation
        //max time is log n because you are keep dividing
        //you can wonder about swapping it is also hapeening one for every two numbers if they are large
            //so it is also <=logn which is complexity of log n also
        // so constants make it the same , so even if it is 3logn or 2logn ,, total copmlexity : logn
    ///
}

//so euclidean algorithm depenes on :
    //1- gcd(a,b)=gcd(b,a)
    //2- gcd(a,0)=|a|
    //3- gcd(a,b)=gcd(b,a%b)
//

///////////////total complexity : O( log(min(a,b)) ) ,,,,,,,,,,why min not max??mmmm...
    //if it was max of them not min so why finding gcd of 2,1000 is faster than finding gcd of 140
        //did you understand??
//________________________________________________________________________________________
//________________________________________________________________________________________
//________________________________________________________________________________________


//how to find the least multiple of a and b (lcm)
    //this depends on the factorization of a and b
    // after factorization ,, to make the number divisible by both :
                // so this number must have the max of power of every factor
                //for example:
                //  6   ,    8
                //factors:
                // 2 3  ,   2 2 2
                //2^1*3^1,, 2^3
                //so the multiple must have at least the greatest number(power) of each factor:
                //at least three of the 2s and one of the 3s
                // so it is 2^3,3^1
    /////////////wait??
    //did you notice something?????????????  mmmmm...
        // we can mulitply both numbers and divide by gcd.....but why??
            //this is because :
            //after muliplying both numbers you have the product = (all) elements of a x ele.s of b
            // and the gcd is the common factors so because multiplying both elements make the common factors appeared two times in the product
                    //to remove it only remove one copy of the common factors which is dividing by the gcd
                        //and so now you have only what you want and the common exists without copying it
////here it is the implementation:
int lcm(int x, int y){
    
    /////////fix:::::::::::::::::edge case when any one of them is zero
    /////////if you left it then it divides by the zero that comes from the gcd fun. if both are zero
    //and actually if any one is zero so ans is zero
    if(x==0 || y==0) return 0;
    
    
    ////fix:::::edge case of negatives, so use abs
    return abs(x/gcd(x,y)*y);////////instead of muliplying x*y then dividing by gcd
                                    // you should do the division first to avoid overflow by the muliplication
                                        //and since both are divisible by the gcd so it preserves the number
}

//_____________________________________________________________________________________________
//_____________________________________________________________________________________________

//important note:

///so now you must know the the gcd takes each factor with the least power from the two numbers
//but the lcm takes each factor with the greatest power from the two numbers


//and so gcd(a,b)*lcm(a,b)=|a*b|





//some important notes:
/*

lcm(a,b)%gcd(a,b)=0



*/







//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________


//one question can it be optimized by dp????????mmmmmmmmmmmmm.........
//answer is no because there are no overlapping problems 
//for example power of 13
// fastpow(13)
//     └── fastpow(6)
//             └── fastpow(3)
//                     └── fastpow(1)
//                             └── fastpow(0)

////////but dp is useful only in overlapping subproblems like fib:
//example fib of 5,, fib is the function : f(x)=f(x-1)+f(x-2) with base case for 1 and 2 or base case for 0 and 1 or whatever it is
// fib(5)
// ├── fib(4)
// │   ├── fib(3)
// │   └── fib(2)
// └── fib(3)   // repeated

//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________

///now the mod functions, use them to avoid the intermediate ovreflow:

//for example a famous mod value in problems:
// int mod=1'000'000'007; //take care if it defined or no!!

int mod_add(int a, int b,int mod=1'000'000'007){
    return (  (a%mod+mod) +(b%mod+mod)  )%mod;
}
int mod_sub(int a, int b,int mod=1'000'000'007){
    return (((a%mod+mod)-(b%mod+mod))+mod)%mod;
}
int mod_mul(int a, int b, int mod=1'000'000'007){
    __int128 ans= (__int128)   (a%mod+mod) *  (b%mod+mod ) % mod;//////fix : assigning it to __int128 before calculating to avoid smaller internal calculatino ranges before converting to __int128
    return ans;//even it is __128int ,,==>> it is returned with function type with value fits in range of int as the %
}


//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________

//now إن شاء الله , the fast pow function:
/////////naive (basic) solution to find pow(x,y) is to muliplying x by itself y times

//////with mod(mod was previously defined as 1e9+7 but don't use xey(forex:1e9) because it has precision erros and doesn't make the number you exactly want always)

//here using MOD instead of mod to make code clear and avoid duplicated names even if different scopes but for code readibility and easier debugging إن شاء الله

// assumes y >= 0**************************important
int fastpow(int x,int y,int MOD=1000'000'007 /*intializing it*/ ){  ////log n complexity because you keep dividing on 2
    if(y==0) return 1;//edge case      //fix::::::::::::::if y==0 not 1
    
    //fix: make x smaller from the beginning:
    x %= MOD;
    
    
    //idea is to divide each into its half value and then muliply it in its self and return
    //but if the power is odd so after dividing there is a missed one power because of floor division nature of integers
            // so mulitply with addition one power of y to fix it
                                ///fix:;;;don't forget mod
    int ret = fastpow(x,y/2,MOD);////////ret here means the returned value (answer for the current state)
    ret=mod_mul(ret,ret,MOD);
    //if odd: don't forget the missed one:
    if(y%2==1) ret=mod_mul(ret,x,MOD);///////////////////////////fix: *=x not y because you are mulitplying with x
    
    return ret;
}

//iterative version:

int fastpow_iterative(int a, int b,int MOD=1000'000'007){
    
    //fix: make a smaller from the beginning:
    a %= MOD;
    
    int ret=1;
    while(b>0){
        if(b&1){//b&1 is the same as b%2==1   ,, because in binary representation if it is odd so the first bit is 1 so you check this bit here
            ret=mod_mul(ret,a,MOD);
        }
        a = mod_mul(a,a,MOD);
        b>>=1;/////same as b/=2;
        
    }
    return ret;
}


///_____________________________________________________________________________________________
///_____________________________________________________________________________________________
///_____________________________________________________________________________________________
///_____________________________________________________________________________________________
///_____________________________________________________________________________________________
///_____________________________________________________________________________________________
//______________________________________________________________________________________________
//______________________________________________________________________________________________
//______________________________________________________________________________________________
//______________________________________________________________________________________________
//______________________________________________________________________________________________
//______________________________________________________________________________________________


////////////////modular inverse:
//////////////////for any number to have a modular inverse with specific mod
////////////////////////////////////the number must be coprime with this mod
///modular inverse mean :
/////////x is mod inverse for y  with the mod m  if (x*y)%m=1



//fermat's little thereom :::::::::::
///to calculate modular inverse using fermat's modular inverse
////////////conditions for this thermeom that MOD is a prime number + the main condition of that:
                                                                        //num and mod are coprimes
int fermat_little_mod_inverse(int NUM_ , int MOD_){
    return fastpow( NUM_ , MOD_ - 2 , MOD_ );//////don't forget to have mod value as a prime
                                                    //this is due to fermat's thereom
}

/////////////////
/////////////////



/////////////////
/////////////////



/////////////////
/////////////////



/////////////////
/////////////////



/////////////////
/////////////////
///chosen modular inverse:
//////to change to the function you want to use
int mod_inverse(int x , int y){
    return fermat_little_mod_inverse(x,y);
}


//_________________________________________________________________________________________
//_________________________________________________________________________________________

///////////building factorization and mod_inverse for factorization as a precomputation:
const int N = 1'000'000;
int fact[N+1],inv_fact[N+1];//normal factorial , and factorial_with_mod_inverse
///////take care of the parameter of mod here , and it is intialized
////
//////goal of function: 
////////build_normal_factorial_and_factorial_with_mod_inverse
void build_fact_and_fact_inv(int mod=1'000'000'007){
    fact[0]=fact[1]=1;
    inv_fact[0]=inv_fact[1]=1;///1 here is the value for mod_inverse(1,mod);
    
    ///////take care:::::********************
    // Safe because:
    // 1) mod is prime.
    // 2) N < mod.
    
    for(int i = 2 ; i<= N ; i++){
        fact[i]=mod_mul(fact[i-1],i,mod);
        inv_fact[i]=mod_inverse(fact[i],mod);
    }
}
/* another way for building the factorials with inverse factorials       with only complexity of n instead of log n
the previous one takes logn because using fastpow inside mod inverse in each one which is not necessary
you can calculate it in O(N):

note that mod mulitplicate inverse behaves exactly as the mulitplicative inverse but in the mod system
//so ::::
fact[i] = fact[i-1] * i
fact[i] / i = fact[i-1]
so   fact[i-1]=fact[i]/i
so 1/fact[i-1]=i/fact[i]
so mod inverse for fact[i-1] is i/fact[i]

code for it:
//
void build_fact_and_fact_inv(int mod=1'000'000'007){
    fact[0]=fact[1]=1;
    inv_fact[0]=inv_fact[1]=1;///1 here is the value for mod_inverse(1,mod);
    
    ///////take care:::::********************
    // Safe because:
    // 1) mod is prime.
    // 2) N < mod.
    
    for(int i = 2 ; i<= N ; i++){
        fact[i]=mod_mul(fact[i-1],i,mod);
        inv_fact[i]=mod_inverse(fact[i],mod);
    }
}




  */

//counting basics: 
////nPr : n! /  (n-r!)
////nCr : n! / ((n-r!) *r !)

///////**************************

/////////////don't forget before use to build the fact and its mod inverse using:
                            // build_fact_and_fact_inv

//importanttttttt//here we must make sure that  0≤r≤n. Otherwise inv_fact[n-r] accesses invalid memory.
int nPr(int n , int r, int mod =1'000'000'007){
    //fix:::::validity check for value of r
    if(r<0 || r>n) return 0;//many libraries add this:*****************************************
    return mod_mul(fact[n],inv_fact[n-r],mod);// we use inv_fact to divide while using mod
}

int nCr(int n , int r, int mod = 1'000'000'007){
    //fix:::::validity check for value of r
    if(r<0 || r>n) return 0;//many libraries add this::*****************************************
    int ans=fact[n];
    ans=mod_mul(ans,inv_fact[r],mod);//dividing over r but with conserving value under mod
    ans=mod_mul(ans,inv_fact[n-r],mod);//dividing over n-r but with conserving value under mod
    return ans;
}

//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________


bool multi_cases=false;
void solve(){
    
}



signed main(){
    
    int ttt=1;
    if(multi_cases)cin>>ttt;
    while(ttt--){
        solve();
    }
    
}
