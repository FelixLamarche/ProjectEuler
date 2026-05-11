#pragma once

#include <stdexcept>
#include <string>

using uint64 = unsigned long long;
using uint32 = unsigned long;

class Unsigned128
{
	static constexpr uint32 nbBitsPerUnit = 32;

	uint32 bits3;
	uint32 bits2;
	uint32 bits1;
	uint32 bits0;

public:
	constexpr Unsigned128()
		: bits3(0), bits2(0), bits1(0), bits0(0)
	{}

	constexpr Unsigned128(uint64 nb)
		: bits3(0), bits2(0), bits1(static_cast<uint32>(nb >> nbBitsPerUnit)), bits0(static_cast<uint32>(nb))
	{
	}

	explicit constexpr Unsigned128(const uint32 bits3, const uint32 bits2, const uint32 bits1, const uint32 bits0)
		: bits3(bits3), bits2(bits2), bits1(bits1), bits0(bits0) {
	}

	// BITWISE OPERATORS
	constexpr Unsigned128 operator~() const
	{
		return Unsigned128(~bits3, ~bits2, ~bits1, ~bits0);
	}

	constexpr Unsigned128 operator|(const Unsigned128& rhs) const
	{
		return Unsigned128(bits3 | rhs.bits3, bits2 | rhs.bits2, bits1 | rhs.bits1, bits0 | rhs.bits0);
	}

	constexpr Unsigned128 operator&(const Unsigned128& rhs) const
	{
		return Unsigned128(bits3 & rhs.bits3, bits2 & rhs.bits2, bits1 & rhs.bits1, bits0 & rhs.bits0);
	}

	constexpr Unsigned128 operator^(const Unsigned128& rhs) const
	{
		return Unsigned128(bits3 ^ rhs.bits3, bits2 ^ rhs.bits2, bits1 ^ rhs.bits1, bits0 ^ rhs.bits0);
	}

	constexpr Unsigned128 operator>>(uint32 nb) const
	{
		uint32 resBits0 = bits0 >> nb;
		uint32 resBits1 = bits1 >> nb;
		uint32 resBits2 = bits2 >> nb;
		const uint32 resBits3 = bits3 >> nb;

		if (nbBitsPerUnit >= nb)
		{
			resBits0 += bits1 << (nbBitsPerUnit - nb);
			resBits1 += bits2 << (nbBitsPerUnit - nb);
			resBits2 += bits3 << (nbBitsPerUnit - nb);
		}
		else if (2 * nbBitsPerUnit >= nb)
		{
			resBits0 += bits2 << (2 * nbBitsPerUnit - nb);
			resBits1 += bits3 << (2 * nbBitsPerUnit - nb);
		}
		else if (3 * nbBitsPerUnit >= nb)
		{
			resBits0 += bits3 << (3 * nbBitsPerUnit - nb);
		}

		return Unsigned128(resBits3, resBits2, resBits1, resBits0);
	}

	constexpr Unsigned128 operator<<(uint32 nb) const
	{
		const uint32 resBits0 = bits0 << nb;
		uint32 resBits1 = bits1 << nb;
		uint32 resBits2 = bits2 << nb;
		uint32 resBits3 = bits3 << nb;

		if (nbBitsPerUnit >= nb)
		{
			resBits3 += bits2 >> (nbBitsPerUnit - nb);
			resBits2 += bits1 >> (nbBitsPerUnit - nb);
			resBits1 += bits0 >> (nbBitsPerUnit - nb);
		}
		else if (2 * nbBitsPerUnit >= nb)
		{
			resBits3 += bits1 >> (2 * nbBitsPerUnit - nb);
			resBits2 += bits0 >> (2 * nbBitsPerUnit - nb);
		}
		else if (3 * nbBitsPerUnit >= nb)
		{
			resBits3 += bits0 >> (3 * nbBitsPerUnit - nb);
		}

		return Unsigned128(resBits3, resBits2, resBits1, resBits0);
	}

	constexpr Unsigned128& operator|=(const Unsigned128& rhs)
	{
		*this = *this | rhs;
		return *this;
	}

	constexpr Unsigned128& operator&=(const Unsigned128& rhs)
	{
		*this = *this & rhs;
		return *this;
	}

	constexpr Unsigned128& operator^=(const Unsigned128& rhs)
	{
		*this = *this ^ rhs;
		return *this;
	}

	// Comparison Operators
	constexpr bool operator==(const Unsigned128& rhs) const
	{
		return bits0 == rhs.bits0 && bits1 == rhs.bits1 && bits2 == rhs.bits2 && bits3 == rhs.bits3;
	}

	constexpr bool operator!=(const Unsigned128& rhs) const
	{
		return !(*this == rhs);
	}

	constexpr bool operator>(const Unsigned128& rhs) const
	{
		if (bits3 != rhs.bits3)
			return bits3 > rhs.bits3;
		if (bits2 != rhs.bits2)
			return bits2 > rhs.bits2;
		if (bits1 != rhs.bits1)
			return bits1 > rhs.bits1;
		return bits0 > rhs.bits0;
	}

	constexpr bool operator>=(const Unsigned128& rhs) const
	{
		if (bits3 != rhs.bits3)
			return bits3 > rhs.bits3;
		if (bits2 != rhs.bits2)
			return bits2 > rhs.bits2;
		if (bits1 != rhs.bits1)
			return bits1 > rhs.bits1;
		return bits0 >= rhs.bits0;
	}

	constexpr bool operator<(const Unsigned128& rhs) const
	{
		if (bits3 != rhs.bits3)
			return bits3 < rhs.bits3;
		if (bits2 != rhs.bits2)
			return bits2 < rhs.bits2;
		if (bits1 != rhs.bits1)
			return bits1 < rhs.bits1;
		return bits0 < rhs.bits0;
	}

	constexpr bool operator<=(const Unsigned128& rhs) const
	{
		if (bits3 != rhs.bits3)
			return bits3 < rhs.bits3;
		if (bits2 != rhs.bits2)
			return bits2 < rhs.bits2;
		if (bits1 != rhs.bits1)
			return bits1 < rhs.bits1;
		return bits0 <= rhs.bits0;
	}

	// Arithmetic Operators
	constexpr Unsigned128& operator+=(const Unsigned128& rhs)
	{
		const uint64 sumBits0 = static_cast<uint64>(bits0) + static_cast<uint64>(rhs.bits0);
		const uint64 carrySumBits0 = sumBits0 >> nbBitsPerUnit;

		const uint64 sumBits1 = static_cast<uint64>(bits1) + static_cast<uint64>(rhs.bits1) + carrySumBits0;
		const uint64 carrySumBits1 = sumBits1 >> nbBitsPerUnit;

		const uint64 sumBits2 = static_cast<uint64>(bits2) + static_cast<uint64>(rhs.bits2) + carrySumBits1;
		const uint64 carrySumBits2 = sumBits2 >> nbBitsPerUnit;

		const uint64 sumBits3 = static_cast<uint64>(bits3) + static_cast<uint64>(rhs.bits3) + carrySumBits2;

		bits0 = static_cast<uint32>(sumBits0);
		bits1 = static_cast<uint32>(sumBits1);
		bits2 = static_cast<uint32>(sumBits2);
		bits3 = static_cast<uint32>(sumBits3);

		return *this;
	}

	constexpr Unsigned128 operator+(const Unsigned128& rhs) const
	{
		Unsigned128 res = *this;
		res += rhs;
		return res;
	}

	constexpr Unsigned128& operator-=(const Unsigned128& rhs)
	{
		const Unsigned128 twosComplementRhs = (~rhs) + 1;
		*this += twosComplementRhs;
		return *this;
	}

	constexpr Unsigned128 operator-(const Unsigned128& rhs) const
	{
		Unsigned128 res = *this;
		res -= rhs;
		return res;
	}

	constexpr Unsigned128& operator++()
	{
		*this = *this + 1;
		return *this;
	}

	constexpr Unsigned128 operator++(int)
	{
		Unsigned128 temp = *this;
		++*this;
		return temp;
	}

	constexpr Unsigned128& operator--()
	{
		*this = *this - 1;
		return *this;
	}

	constexpr Unsigned128 operator--(int)
	{
		Unsigned128 temp = *this;
		--*this;
		return temp;
	}

	constexpr Unsigned128& operator*=(const Unsigned128& rhs)
	{
		const uint64 prodBits00 = static_cast<uint64>(bits0) * static_cast<uint64>(rhs.bits0);
		const uint32 carryProdBits00 = prodBits00 >> nbBitsPerUnit;
		const uint64 prodBits01 = static_cast<uint64>(bits0) * static_cast<uint64>(rhs.bits1);
		const uint32 carryProdBits01 = prodBits01 >> nbBitsPerUnit;
		const uint64 prodBits02 = static_cast<uint64>(bits0) * static_cast<uint64>(rhs.bits2);
		const uint32 carryProdBits02 = prodBits02 >> nbBitsPerUnit;
		const uint64 prodBits03 = static_cast<uint64>(bits0) * static_cast<uint64>(rhs.bits3);
		//const uint32 carryProdBits03 = prodBits03 >> nbBitsPerUnit;

		const uint64 prodBits10 = static_cast<uint64>(bits1) * static_cast<uint64>(rhs.bits0);
		const uint32 carryProdBits10 = prodBits10 >> nbBitsPerUnit;
		const uint64 prodBits11 = static_cast<uint64>(bits1) * static_cast<uint64>(rhs.bits1);
		const uint32 carryProdBits11 = prodBits11 >> nbBitsPerUnit;
		const uint64 prodBits12 = static_cast<uint64>(bits1) * static_cast<uint64>(rhs.bits2);
		//const uint32 carryProdBits12 = prodBits12 >> nbBitsPerUnit;
		//const uint64 prodBits13 = static_cast<uint64>(bits1) * static_cast<uint64>(rhs.bits3);
		//const uint64 carryProdBits13 = prodBits13 >> nbBitsPerUnit;

		const uint64 prodBits20 = static_cast<uint64>(bits2) * static_cast<uint64>(rhs.bits0);
		const uint32 carryProdBits20 = prodBits20 >> nbBitsPerUnit;
		const uint64 prodBits21 = static_cast<uint64>(bits2) * static_cast<uint64>(rhs.bits1);
		//const uint32 carryProdBits21 = prodBits21 >> nbBitsPerUnit;
		//const uint64 prodBits22 = static_cast<uint64>(bits2) * static_cast<uint64>(rhs.bits2);
		//const uint32 carryProdBits12 = prodBits22 >> nbBitsPerUnit;
		//const uint64 prodbits23 = static_cast<uint64>(bits2) * static_cast<uint64>(rhs.bits3);
		//const uint64 carryprodbits23 = prodbits23 >> nbbitsperunit;

		const uint64 prodBits30 = static_cast<uint64>(bits3) * static_cast<uint64>(rhs.bits0);
		//const uint32 carryProdBits30 = prodBits30 >> nbBitsPerUnit;
		//const uint64 prodBits31 = static_cast<uint64>(bits3) * static_cast<uint64>(rhs.bits1);
		//const uint32 carryProdBits31 = prodBits31 >> nbBitsPerUnit;
		//const uint64 prodBits32 = static_cast<uint64>(bits3) * static_cast<uint64>(rhs.bits2);
		//const uint32 carryProdBits32 = prodBits32 >> nbBitsPerUnit;
		//const uint64 prodbits33 = static_cast<uint64>(bits3) * static_cast<uint64>(rhs.bits3);
		//const uint64 carryprodbits33 = prodbits33 >> nbbitsperunit;

		const uint64 newBits1 = prodBits01 + prodBits10 + carryProdBits00;
		const uint64 newBits2 = prodBits02 + carryProdBits01 + prodBits11 + carryProdBits10 + prodBits20 + (newBits1 >> nbBitsPerUnit);
		const uint64 newBits3 = prodBits03 + carryProdBits02 + prodBits12 + carryProdBits11 + prodBits21 + carryProdBits20 + prodBits30 + (newBits2 >> nbBitsPerUnit);

		bits0 = static_cast<uint32>(prodBits00);
		bits1 = static_cast<uint32>(newBits1);
		bits2 = static_cast<uint32>(newBits2);
		bits3 = static_cast<uint32>(newBits3);

		return *this;
	}

	constexpr Unsigned128 operator*(const Unsigned128& rhs) const
	{
		Unsigned128 res = *this;
		res *= rhs;
		return res;
	}

	constexpr Unsigned128& operator/=(const Unsigned128& rhs)
	{
		if (rhs == 0)
		{
			throw std::runtime_error("Division by zero!");
		}

		if (*this < rhs)
		{
			*this = 0;
			return *this;
		}

		if (rhs.bits3 > 0)
		{
			*this = bits3 / rhs.bits3;
		}
		else if (rhs.bits2 > 0)
		{
			const uint64 upperBits = (static_cast<uint64>(bits3) << nbBitsPerUnit) + bits2;
			*this = upperBits / rhs.bits2;
		}
		else
		{
			Unsigned128 result = 0;

			while (*this >= rhs)
			{
				Unsigned128 resultIteration = 1;

				Unsigned128 divider = rhs;
				while (*this >= divider << 1 && (divider < (divider << 1)))
				{
					resultIteration = resultIteration << 1;
					divider = divider << 1;
				}

				*this -= divider;
				result += resultIteration;
			}
			*this = result;
		}
		return *this;
	}

	constexpr Unsigned128 operator/(const Unsigned128& rhs) const
	{
		Unsigned128 res = *this;
		res /= rhs;
		return res;
	}

	constexpr Unsigned128& operator%=(const Unsigned128& rhs)
	{
		const Unsigned128 division = *this / rhs;
		*this -= division * rhs;
		return *this;
	}

	constexpr Unsigned128 operator%(const Unsigned128& rhs) const
	{
		Unsigned128 res(*this);
		res %= rhs;
		return res;
	}

	explicit constexpr operator uint64() const
	{
		return (static_cast<uint64>(bits1) << nbBitsPerUnit) + static_cast<uint64>(bits0);
	}
	explicit constexpr operator uint32() const
	{
		return bits0;
	}

	constexpr std::string ToString() const
	{
		if (*this == 0)
			return std::string("0");

		uint32 nbDigits = 0;
		Unsigned128 nb = *this;
		while (nb > 0)
		{
			nbDigits++;
			nb /= 10;
		}

		std::string s;
		s.resize(nbDigits, '0');

		nb = *this;
		for (int digitIdx = nbDigits - 1; digitIdx >= 0; --digitIdx)
		{
			const uint32 digit = static_cast<uint32>(nb % 10);
			s.at(digitIdx) = static_cast<unsigned char>(digit) + '0';
			nb /= 10;
		}

		return s;
	}

	friend constexpr Unsigned128 operator|(const uint64 lhs, const Unsigned128& rhs);
	friend constexpr Unsigned128 operator&(const uint64 lhs, const Unsigned128& rhs);
	friend constexpr Unsigned128 operator^(const uint64 lhs, const Unsigned128& rhs);

	friend constexpr bool operator==(const uint64 lhs, const Unsigned128& rhs);
	friend constexpr bool operator!=(const uint64 lhs, const Unsigned128& rhs);
	friend constexpr bool operator>(const uint64 lhs, const Unsigned128& rhs);
	friend constexpr bool operator>=(const uint64 lhs, const Unsigned128& rhs);
	friend constexpr bool operator<(const uint64 lhs, const Unsigned128& rhs);
	friend constexpr bool operator<=(const uint64 lhs, const Unsigned128& rhs);

	friend constexpr Unsigned128 operator+(const uint64 lhs, const Unsigned128& rhs);
	friend constexpr Unsigned128 operator-(const uint64 lhs, const Unsigned128& rhs);
	friend constexpr Unsigned128 operator*(const uint64 lhs, const Unsigned128& rhs);
	friend constexpr Unsigned128 operator/(const uint64 lhs, const Unsigned128& rhs);
	friend constexpr Unsigned128 operator%(const uint64 lhs, const Unsigned128& rhs);
};

constexpr Unsigned128 operator|(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator|(lhs);
}
constexpr Unsigned128 operator&(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator&(lhs);
}
constexpr Unsigned128 operator^(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator^(lhs);
}

constexpr bool operator==(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator==(lhs);
}
constexpr bool operator!=(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator!=(lhs);
}

constexpr bool operator>(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator>(lhs);
}
constexpr bool operator>=(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator>=(lhs);
}
constexpr bool operator<(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator<(lhs);
}
constexpr bool operator<=(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator<=(lhs);
}

constexpr Unsigned128 operator+(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator+(lhs);
}

constexpr Unsigned128 operator-(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator-(lhs);
}

constexpr Unsigned128 operator*(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator*(lhs);
}

constexpr Unsigned128 operator/(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator/(lhs);
}

constexpr Unsigned128 operator%(const uint64 lhs, const Unsigned128& rhs)
{
	return rhs.operator%(lhs);
}

using uint128 = Unsigned128;
