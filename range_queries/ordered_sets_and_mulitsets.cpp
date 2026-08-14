#include<bits/stdc++.h>
using namespace std;



#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class  T>using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T>using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
/*
    Two important PBDS functions:

    1) s.order_of_key(x)

       Returns the number of elements strictly less than x.

       For example:
       S = {10, 20, 30, 40, 50}

       s.order_of_key(30) = 2
       because {10, 20} are strictly less than 30.

       If the keys are integers and you want the number of elements <= x:

       s.order_of_key(x + 1);


    2) s.find_by_order(k)

       Returns an iterator to the element at 0-based position k.

       For example:
       S = {10, 20, 30, 40, 50}

       *s.find_by_order(0) = 10
       *s.find_by_order(1) = 20
       *s.find_by_order(2) = 30
       *s.find_by_order(3) = 40
       *s.find_by_order(4) = 50

       Therefore, if you want the k-th smallest element using
       1-based indexing:

       *s.find_by_order(k - 1)

       IMPORTANT:
       +1 is relevant to order_of_key when converting < x to <= x
       (for integer keys).

       +1 is NOT how you convert find_by_order to 1-based indexing.
*/
