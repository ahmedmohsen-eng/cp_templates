/*

if you have a pair of integers(x,y) and you want the max of them to be n
then all possible pairs = (n+1)*2 -1 

because you can have (0,n) => (1,n) => ... => (n,n)
and also             (n,0) => (n,1) => ... => (n,n)
,,,,and the case of (n,n) was duplicated so remove from both
so it is (n+1)*2 -1  which is equal to n*2 + 1

_____________________________________________________________________________________________________________________________________
_____________________________________________________________________________________________________________________________________


if you have 5 seats 
__ __ __ __ __

and you have 
a b c d e 
how many ways to to let them sit but with condition that : a,b sit always beside each other ??????

that means (a,b) acts as 1 block so number of blocks is 4 because a,b is one block and each reamining is also a block

and (a,b) themselves can be rearranged internally a,b or b,a       so because they are two , it is 2! choices for internal choices of a,b

==> so it acts as a block so now you have 4 seats with 4 blocks but one block has 2 elements in it

so overall it is 4! x 2 !

//////////////////////////////////////////////

what if i told you number of ways such that a,b  (((don't))) seat beside each other :
so calculate all ways then substract (-) from them number of ways that they sit beside each other !

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
what if seats are circular ?????
_______A_______
|              |
|              |
B              D
|              |
|______c_______|

another way:
_______B_______
|              |
|              |
C              A
|              |
|______D_______|

now what to do? how to calculate such thing??

n!/n = (n-1)!

because        ( a b c d )
is the same as ( b c d a ) but it is rotated ,, and it is a circle so it is the same
notice that it is rotated by one seat

why dividing by n? because:
          Every circular arrangement appears exactly n times in n!
                  for example : abcd bcda cdab dabc  and if you rotate more then it is the same as the first 
                        so it appeared four times which is n
            in other words : :::::::::::::::::::::::: : you can rotate the table n-1 times before reaching at the nth time to the original place so they are n+1 rotations 
                                                                  + 1 which is the original one
                                                                                        so now you have each distinct arragnement appears n times in the total n! possible ways

          or simply you can fix one place and calculate the next elements to avoid duplicated arrangements

**it is proved mathematically downward in the area of (by ai) 

_____________________________________________________________________________________________________________________________________
_____________________________________________________________________________________________________________________________________






*/







//by ai :
/*

//proof of the (n-1)! formula of circular seats:

Mathematical proof:

Let S be the set of all arrangements when seats are labeled.

Since there are n people and n labeled seats:

|S| = n!

Now define an equivalence relation:

x ~ y

if x can be obtained from y by rotating the circle.

In other words, all rotations of the same circular arrangement are considered identical.

For any arrangement x, its equivalence class is:

[x] = {x, R(x), R²(x), ..., Rⁿ⁻¹(x)}

where R means rotating the arrangement by one seat.

There are exactly n possible rotations:

R⁰, R¹, R², ..., Rⁿ⁻¹

and because all people are distinct, all these rotations are different.

Therefore:

|[x]| = n

Each circular arrangement corresponds to exactly one equivalence class.

So the number of circular arrangements is:

|S| / |[x]|

= n! / n

= (n-1)!

Therefore:

Number of ways to arrange n distinct people around a circular table = (n-1)!
________________________________________________________________________________________________________________________________________________________
________________________________________________________________________________________________________________________________________________________
________________________________________________________________________________________________________________________________________________________














// ------------------------------------------------------------
// Addition Rule (Sum Rule)
//
// If a task can be completed by choosing exactly ONE of several
// mutually exclusive options, then the total number of ways is
// the sum of the number of ways for each option.
//
// Formula:
// If there are:
//   - a ways to do option A
//   - b ways to do option B
// and A and B cannot happen together,
// then the total number of ways is:
//
//      a + b
//
// Example:
// Choose either:
//   - one red ball (5 choices)
//   - one blue ball (3 choices)
//
// Since a ball cannot be both red and blue,
// the total number of choices is:
//
//      5 + 3 = 8
// ------------------------------------------------------------


// ------------------------------------------------------------
// Multiplication Rule (Product Rule)
//
// If a task consists of several independent consecutive steps,
// then the total number of possible outcomes equals the product
// of the number of choices for each step.
//
// Formula:
// If:
//   - Step 1 has a choices.
//   - Step 2 has b choices.
//   - ...
//   - Step n has k choices.
//
// Then the total number of ways is:
//
//      a × b × ... × k
//
// Example:
// Form a password consisting of:
//   - 3 uppercase letters (26 choices each)
//   - 2 digits (10 choices each)
//
// Number of passwords:
//
//      26 × 26 × 26 × 10 × 10
// ------------------------------------------------------------


// ------------------------------------------------------------
// Permutations (nPr)
//
// A permutation counts the number of ways to choose AND arrange
// r objects from n distinct objects.
//
// Order matters.
//
// Formula:
//
//            n!
// nPr = -------------
//        (n - r)!
//
// where:
//   - n! = n × (n-1) × ... × 2 × 1
//
// Why?
// Imagine filling r positions.
//
// Position 1: n choices
// Position 2: n-1 choices
// ...
// Position r: n-r+1 choices
//
// By the multiplication rule:
//
// n × (n-1) × ... × (n-r+1)
//
// which simplifies to:
//
//      n! / (n-r)!
//
// Example:
// Arrange 3 students from 5 in a row.
//
//      5P3
//    = 5 × 4 × 3
//    = 60
// ------------------------------------------------------------


// ------------------------------------------------------------
// Combinations (nCr)
//
// A combination counts the number of ways to choose r objects
// from n distinct objects.
//
// Order does NOT matter.
//
// Formula:
//
//             n!
// nCr = ----------------
//        r!(n-r)!
//
// Why?
// First, count all possible arrangements:
//
//      nPr = n! / (n-r)!
//
// However, each selected group of r objects is counted r! times,
// because the same objects can be arranged in r! different orders.
//
// Therefore, divide by r!:
//
//            n!
// nCr = -------------
//        r!(n-r)!
//
// Example:
// Choose a committee of 3 students from 5.
//
//      5C3
//    = 10
//
// Notice:
//
// {A, B, C}
// {B, A, C}
// {C, B, A}
//
// are considered the SAME selection, so they are counted only once.
// ------------------------------------------------------------













*/

