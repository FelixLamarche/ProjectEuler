#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <string>

static std::string Solve(long long N)
{
	static std::map<long long, std::string> words
	{
		{0, "Zero"},
		{1, "One"},
		{2, "Two"},
		{3, "Three"},
		{4, "Four"},
		{5, "Five"},
		{6, "Six"},
		{7, "Seven"},
		{8, "Eight"},
		{9, "Nine"},
		{10, "Ten"},
		{11, "Eleven"},
		{12, "Twelve"},
		{13, "Thirteen"},
		{14, "Fourteen"},
		{15, "Fifteen"},
		{16, "Sixteen"},
		{17, "Seventeen"},
		{18, "Eighteen"},
		{19, "Nineteen"},
		{20, "Twenty"},
		{30, "Thirty"},
		{40, "Fourty"},
		{50, "Fifty"},
		{60, "Sixty"},
		{70, "Seventy"},
		{80, "Eighty"},
		{90, "Ninety"},
		{100, "Hundred"},
		{1000, "Thousand"},
		{1'000'000, "Million"},
		{1'000'000'000, "Billion" },
		{1'000'000'000'000, "Trillion"}
	};

	std::string name = "";
	long long remaining = N;
	while (remaining)
	{
		const int length = static_cast<int>(std::to_string(remaining).size());
		const int chunkLength = length % 3;
		const long long orderNb = static_cast<long long>(std::pow(10, std::max((length - 1) / 3 * 3, 0)));

		// Between 0-999
		const int chunkNb = static_cast<int>(remaining / orderNb);
		if (chunkLength == 0)
		{
			const int n = chunkNb / 100;
			if (n > 0)
			{
				name.append(words[n]);
				name.push_back(' ');
				name.append(words[100]);
				name.push_back(' ');
			}
		}
		const int tens = chunkNb % 100;

		if (tens >= 20)
		{
			name.append(words[tens / 10 * 10]);
			name.push_back(' ');

			if (tens % 10)
			{
				name.append(words[tens % 10]);
				name.push_back(' ');
			}
		}
		else if (tens != 0)
		{
			name.append(words[tens]);
			name.push_back(' ');
		}

		if (orderNb > 999)
		{
			name.append(words[orderNb]);
			name.push_back(' ');
		}

		if (orderNb < 1000)
		{
			break;
		}
		remaining %= orderNb;
	}

	// Remove final space ' '
	name.erase(--name.end(), name.end());
	return name;
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
