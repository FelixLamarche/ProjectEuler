#include "Problem16.h"

#include <vector>

int Problem16::Solve(int N)
{
    std::vector<unsigned char> digits{ 1 };
    for (int i = 1; i <= N; i++)
    {
        int ret = 0;
        for (size_t j = 0; j < digits.size(); j++)
        {
            unsigned char n = digits[j] * 2 + ret;
            ret = n / 10;
            n %= 10;
            digits[j] = n;
        }
        if (ret)
        {
            digits.push_back(ret);
        }
    }
    int sum = 0;

    for (size_t i = 0; i < digits.size(); i++)
    {
        sum += digits[i];
    }
    return sum;
}

