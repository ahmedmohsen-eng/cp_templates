#include<bits/stdc++.h>
using namespace std;


#define int long long

// a%b = a-(floor(a/b))      because we still substract by b till value is smaller than a


////////////////////////////////////////////////////////////////
// we know that gcd (a,b) = gcd(b,a)

//gcd(b,a)=gcd(b%a,a)              here is why  >====
//and since gcd(a,b)=gcd(b,a)                        |
//then gcd(a,b)=gcd(b%a,a)                           |
                                                       //reason: 
                                                              // g is gcd(a,b)
                                                              // a/g is integer and b/g is integer then a/g-b/g is integer which means that a-b is divisible by g also
                                                              // so substracting by the another value doesn't change the answer and this is the proof
                                                              //
//////////////////////////////////so now gcd(a,b)=gcd(b%a,a)
////////////////////////////////////////////////////////////////////
//and we have gcd(a,0)=a


// 

//




signed main (){




}
