#include <bits/stdc++.h>
using namespace std;

// Finds maximum subarray sum and indices in O(n).
// Usage: call kadane(v); then read globals mx, l, r.
long long mx;
int l, r;

void kadane(const vector<long long>& v) {
    int n = (int)v.size();

    long long cur = 0;
    mx = LLONG_MIN;

    int curL = 0, curR = 0;
    l = r = 0;

    for (int i = 0; i < n; i++) {
        if (v[i] > cur + v[i]) {
            cur = v[i];
            curL = curR = i;
        } else {
            cur += v[i];
            curR = i;
        }

        if (cur > mx) {
            mx = cur;
            l = curL;
            r = curR;
        }
    }
}

/* Error / debug notes (appended for safety):
None in original.
*/
