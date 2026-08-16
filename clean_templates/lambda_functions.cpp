#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    // Lambda capture reminders:
    // []    : capture nothing
    // [&]   : capture by reference
    // [=]   : capture by value
    auto inc = [](int &x) {
        x++;
        return x;
    };
    return 0;
}
