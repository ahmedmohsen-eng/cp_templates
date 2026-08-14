#include<bits/stdc++.h>
using namespace std;



#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class  T>using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T>using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

/*
5. The two important functions

These are the main reason to use PBDS:

s.order_of_key(x);

and

s.find_by_order(k);
order_of_key

Returns:

#{a∈S:a<x}
//////////////////////notice less only not less or equal !!      so if you want elements less or equal use +1 

/////////****important
/////////////////////find_by_order(k)​ starts from index 0 !!!!!
*/
