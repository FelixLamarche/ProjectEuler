/// Problem 28: Number spiral diagonals
// What is the sum of the numbers on the diagonals in a N x N spiral formed such?
/// as the one below for N = 5
// 21 22 23 24 25
// 20  7  8  9 10
// 19  6  1  2 11
// 18  5  4  3 12
// 17 16 15 14 13

#include <iostream>


static int SolveInefficient(long long N)
{
	const long long mod = 1'000'000'007; // is a prime number

	// Per loop, we add the 4 corners of the current square
	// Which is nb_prev + 2i + nb_prev + 4i + nb_prev + 6i + nb_prev + 8i
	// = 4nb_prev + 20i
	// Where i is the current square size and nb_prev is the last number of the previous square (nb_prev + 8i)
	long long sum = 1; // Start with one
	long long curNb = 1;
	for (long long i = 1; i <= N / 2; i++)
	{
		const long long square = 4 * curNb + 20 * (i % mod);
		curNb = (curNb + 8 * i) % mod;
		sum += square % mod;
	}

	return static_cast<int>(sum % mod);
}

static constexpr long long Degree(long long a, long long k, long long p) {
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

static int Solve(long long N)
{
	const long long mod = 1'000'000'007; // is a prime number

	// The spiral is made of squares.
	// The numbers on a single layer of the spiral are the corners of the square.
	// Where the top-right corner is the square of the size of the square. (n^2)
	// And the other corners are the top-right corner minus 1, 2, or 3 the size of the square
	// The sum of powers up to n is n(n+1)(2n+1)/6
	// Removing the even powers

	// Per loop, we add the 4 corners of the current square
	// Which is nb_prev + 2i + nb_prev + 4i + nb_prev + 6i + nb_prev + 8i
	// = 4nb_prev + 20i
	// Where i is the current square size and nb_prev is the last number of the previous square (nb_prev + 8i)
	// nb_prev is the sequence of the odd powers 1^2, 3^2, 5^2, 7^2, 9^2, ...
	// Because they are the top-right corners of the squares

	// The diagonals of a spiral have a sum of 4(2n - 1)^2 + 20n, where n > 0, n is the layer of the spira
	// A sum of 1 to N of 4(2n - 1)^2 + 20n 
	// = 4Sum((2n-1)^2 + 20Sum(n)
	// = 4Sum(4n^2 - 4n + 1) + 20*N*(N+1)/2
	// = 4Sum(4n^2) - 4Sum(4n) + 4Sum(1) + 10N*(N+1)
	// = 4*4Sum(n^2) - 4*4Sum(n) + 4N + 10N*(N+1)
	// = 4*4N*(N+1)*(2N+1)/6 + 2N(N+1) + 4N
	// = 8N*(N+1)*(2N+1)/3 + 2N(N+1) + 4N
	// = (16N^3)/3 + 10N^2 + 26N/3
	// And we add 1 at the end for the center of the spiral

	// 1/3 mod 1'000'000'007 = 3^(p - 2) = 333333336 
	// since 3^(p-1) = 1 mod p, where p is a prime number
	constexpr int divBy3 = static_cast<int>(Degree(3, mod - 2, mod)); 

	const long long Nmod = (N / 2) % mod;
	const long long a = 8 * Nmod % mod * (Nmod + 1) % mod * (2 * Nmod + 1) % mod * divBy3 % mod;
	const long long b = 2 * Nmod % mod * (Nmod + 1) % mod;
	const long long c = 4 * Nmod % mod;
	const long long sum = (a + b + c + 1) % mod;

	return static_cast<int>(sum);
}

int main()
{
	int T;
	std::cin >> T;
	for (int i = 0; i < T; i++)
	{
		long long N;
		std::cin >> N;
		std::cout << Solve(N) << std::endl;
	}
	return 0; 
}