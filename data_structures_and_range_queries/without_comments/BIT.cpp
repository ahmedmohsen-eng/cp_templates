#include <bits/stdc++.h>

using namespace std;

bool multicases_ = true;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<typename T>
using ordered_multiset = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;

#define int long long

typedef unsigned long long u64;
#define ull unsigned long long

void setIO(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}



///////////////////////////////////////////////////////////////////////////////////

struct BIT {

    long long op(long long a, long long b) {
        return a + b;
    }

    long long inv_op(long long a, long long b) {
        return a - b;
    }

    long long def_op = 0;

    int n;
    vector<long long> b;

    void update(int idx, long long v) {
        while(idx <= n) {
            b[idx] = op(b[idx], v);
            idx += idx & -idx;
        }
    }

    long long get(int idx) {
        long long ans = def_op;
        while(idx > 0) {
            ans = op(ans, b[idx]);
            idx -= idx & -idx;
        }
        return ans;
    }

    long long get(int l, int r) {
        return get(r) - get(l - 1);
    }

    void set(int idx, long long v) {
        long long old = get(idx, idx);
        update(idx, inv_op(v, old));
    }

    BIT(vector<long long> arr) {

        int original_n = arr.size() - 1;

        n = 1;
        while(n < original_n)
            n <<= 1;

        b.assign(n + 1, def_op);

        for(int i = 1; i <= original_n; i++) {
            b[i] = op(b[i], arr[i]);
        }

        for(int i = 1; i <= n; i++) {
            int parent = i + (i & -i);
            if(parent <= n)
                b[parent] = op(b[parent], b[i]);
        }
    }

    BIT(int _n) {

        n = 1;
        while(n < _n) {
            n <<= 1;
        }

        b.assign(n + 1, def_op);
    }

    int lower_bound(long long sum) {

        int skip = 0;

        for(int step = n; step > 0; step >>= 1) {
            if(skip + step <= n && b[skip + step] < sum) {
                sum -= b[skip + step];
                skip += step;
            }
        }

        return skip + 1;
    }
};

///////////////////////////////////////////////////////////////////////////////////

void pre_compute() {

}

void solve(int tc) {

    int n;
    cin >> n;

    vector<int> arr(n + 1);

    for(int i = 1; i <= n; i++)
        cin >> arr[i];

    BIT b = BIT(arr);

    int l, r;
    cin >> l >> r;

    cout << b.get(l, r) << '\n';

    int i, v;
    cin >> i >> v;

    b.set(i, v);

    cout << b.get(l, r) << '\n';
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    pre_compute();

    int tc = 1;

    if(multicases_)
        cin >> tc;

    int total_tcs = tc;

    while(tc--) {
        solve(total_tcs - tc);
    }

    return 0;
}
