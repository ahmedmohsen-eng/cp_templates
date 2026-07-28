#include<bits/stdc++.h>
using namespace std;

#define int long long


signed main(){

  //////////////note : & in the parameter (int&x) is for editing the vairable itself not acopy but it is different than the & inside the[]
  //////////////////////if it is [] then it doesn't capture any variables from any scope, otherwise if it is[&] so it reads previous defined variables in the same domain
  auto inc = [] (int& x) { //      ( ) takes the parameters
    x++;//any code
    return x//the return statment
  };/////////////////////////////////////don't forget the ; after the }
  
}
