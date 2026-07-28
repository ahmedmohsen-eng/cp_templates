//both functions complexities : sqrt(n) for both time and memory

// Returns the k-th smallest divisor of n (1-indexed).
// Returns -1 if k > number of divisors.
long long kthSmallestDivisor(long long n, long long k) {
    vector<long long> large;

    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (--k == 0) return i;

            if (i != n / i)
                large.push_back(n / i);
        }
    }

    if (k > (long long)large.size())
        return -1;

    return large[large.size() - k];
}

// Returns the k-th largest divisor of n (1-indexed).
// Returns -1 if k > number of divisors.
long long kthLargestDivisor(long long n, long long k) {
    vector<long long> small;

    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i != n / i)
                small.push_back(i);

            if (--k == 0)
                return n / i;
        }
    }

    if (k > (long long)small.size())
        return -1;

    return small[small.size() - k];
}
