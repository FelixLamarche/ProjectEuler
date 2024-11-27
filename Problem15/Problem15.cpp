#include "Problem15.h"

#include <numeric>


// a^k mod p, fast with binary method
long long Problem15::Degree(long long a, long long k, long long p) {
    long long res = 1;
    long long cur = a;

    while (k) {
        if (k % 2) {
            res = (res * cur) % p;
        }
        k /= 2;
        cur = (cur * cur) % p;
    }
    return res;
}

// n >= k, p is a prime number
long long Problem15::NChooseKModP(int n, int k, int p)
{
    long long res = 1;
    // Calculate n!/(n - k)!
    // = n * (n - 1) * (n - 2) * ... 3 * 2 * 1 / (n - k) * (n - k - 1) * ... * 3 * 2 * 1
    // = n * (n - 1) * (n - 2) * ... * (n - k + 1)
    for (int i = n - k + 1; i <= n; i++)
    {
        res = (res * i) % p;
    }

    // Calculate 1/k!
    long long denom = 1;
    for (long long i = 2; i <= k; ++i) {
        denom = (denom * i) % p;
    }

    // Final result of n!/k!(n-k)!
    // Fermat little theorem: 
    // a^(p-1) = 1 mod p, if p and a are coprime
    // Then, a^(p-2) * a = 1 mod p
    // a^(p - 2) = a^(-1) mod p
    // So 1/k! = k^(p - 2) in mod p
    // n!/k!(n - k)! mod p = n_to_k_plus_1_factorial * k^(p-2) mod p
    res = (res * Degree(denom, p - 2, p)) % p;

    return res;
}

long long Problem15::Solve(int N, int M)
{
    // Prime modulo
    constexpr int modulo = 1'000'000'007;
    const int n = N + M;
    const int k = std::min(N, M);
    const long long res = NChooseKModP(n, k, modulo);
    return res;
}