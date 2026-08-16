// Problem: UVA 12148 - Summing the differences when two dates differ by one day.
#include <bits/stdc++.h>
using namespace std;

// Month lengths for non-leap year
static const int M[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool oneday(int ad, int am, int ay, int bd, int bm, int by) {
    // Check if (ad,am,ay) is exactly one day after (bd,bm,by)
    if (--bd == 0) {
        if (--bm == 0) {
            --by;
            bm = 12;
        }
        bd = M[bm - 1];
        bool isleap = (by % 4 == 0 && (by % 100 != 0 || by % 400 == 0));
        if (bm == 2 && isleap)
            bd = 29;
    }
    return ad == bd && am == bm && ay == by;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, ad = 0, am = 0, ay = 0, ac = 0;
    while (cin >> n, n) {
        int sum = 0, count = 0;
        while (n--) {
            int bd, bm, by, bc;
            cin >> bd >> bm >> by >> bc;
            if (oneday(ad, am, ay, bd, bm, by)) {
                sum += bc - ac;
                count++;
            }
            ad = bd;
            am = bm;
            ay = by;
            ac = bc;
        }
        cout << count << " " << sum << '\n';
    }
    return 0;
}

/* Error/debug notes:
None preserved beyond code comments.
*/
