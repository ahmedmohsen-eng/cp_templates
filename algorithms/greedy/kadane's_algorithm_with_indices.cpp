//goal is to find maximum subarray indices and sum in O(n):

// Global variables to store the answer
int mx;
int l, r;

void kadane(const vector<int>& v) {
    int n = v.size();

    int cur = 0;
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

//usage:
/*

kadane(v);

//variables are previously declared globally :
cout << mx << '\n';          // Maximum subarray sum
cout << l << ' ' << r << '\n'; // Indices of the maximum subarray

*/
