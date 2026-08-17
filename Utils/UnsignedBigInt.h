#pragma once

#include <assert.h>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

using uint64 = unsigned long long;
using uint32 = unsigned long;

class UnsignedBigInt
{
	static constexpr uint32 nbBitsPerChunk = 32;

	// For bits layout: [0] = 0002  [1] = 0003
	// 2 would be the smallest value which would equal a 2, and 3 would be the smallest value being 3 x sizeof( chunk0 )
	// Should always contain at least a single input
	std::vector<uint32> bits; // index-0 is the smallest order of magnitude number

public:
	constexpr UnsignedBigInt()
	{
		bits.push_back(0);
	}

	constexpr UnsignedBigInt(uint64 nb)
	{
		if (nb <= std::numeric_limits<uint32>::max())
		{
			bits.push_back(static_cast<uint32>(nb));
		}
		else
		{
			bits.resize(2);
			bits[0] = static_cast<uint32>(nb);
			bits[1] = static_cast<uint32>(nb >> nbBitsPerChunk);
		}
	}

	constexpr UnsignedBigInt(const std::vector<uint32>& bits)
		: bits(bits)
	{
		assert(!bits.empty());
	}

	constexpr UnsignedBigInt(std::vector<uint32>&& bits)
		: bits(std::move(bits))
	{
		assert(!bits.empty());
	}

	constexpr UnsignedBigInt(const UnsignedBigInt& other)
		: bits(other.bits)
	{}

	constexpr UnsignedBigInt(UnsignedBigInt&& other) noexcept
		: bits(std::move(other.bits))
	{}

	constexpr UnsignedBigInt& operator=(const UnsignedBigInt& other)
	{
		bits = other.bits;
		return *this;
	}

	constexpr UnsignedBigInt& operator=(UnsignedBigInt&& other) noexcept
	{
		bits = std::move(other.bits);
		return *this;
	}

	// Removes unnecessary 0 values above a threshold
	constexpr void Optimize()
	{
		if (bits.size() == 1)
			return;

		auto it = std::find_if(bits.rbegin(), bits.rend(), [](uint32 x) {
			return x != 0;
			});

		// Keep at least a single bit chunk
		if (it == bits.rend())
			it--;

		bits.erase(it.base(), bits.end());
	}

	constexpr void ShiftLeft(uint32 shift)
	{
		if (shift == 0 || *this == 0)
			return;

		const uint32 fullChunksMoved = shift / nbBitsPerChunk;
		const uint32 movementInChunk = shift % nbBitsPerChunk;
		const uint32 complementMovementInChunk = nbBitsPerChunk - movementInChunk;

		uint32 chunksNeeded = fullChunksMoved + bits.size();

		const uint64 lastBitsChunkValue64 = static_cast<uint64>(bits[bits.size() - 1]) << movementInChunk;
		const uint32 biggestChunkComplementBits = static_cast<uint32>(lastBitsChunkValue64 >> nbBitsPerChunk);
		const bool isLastChunkComplement = biggestChunkComplementBits > 0;
		if (isLastChunkComplement)
			++chunksNeeded;

		uint32 previousBitsLastIndex = bits.size() - 1;
		bits.resize(chunksNeeded, 0);

		if (complementMovementInChunk == nbBitsPerChunk)
		{
			int iRes = bits.size() - 1;
			for (int iBits = previousBitsLastIndex; iRes >= 0; --iBits, --iRes)
			{
				if (iBits >= 0)
					bits[iRes] = bits[iBits];
				else
					bits[iRes] = 0;
			}
			return;
		}

		int iRes = bits.size() - 1;
		if (isLastChunkComplement)
		{
			bits[bits.size() - 1] += biggestChunkComplementBits;

			--iRes;
		}

		for (int iBits = previousBitsLastIndex; iBits >= 0; --iBits, --iRes)
		{
			bits[iRes] = bits[iBits] << movementInChunk;
			if (iBits - 1 >= 0)
				bits[iRes] += bits[iBits - 1] >> complementMovementInChunk;
		}

		for (uint32 iBits = 0; iBits < fullChunksMoved; ++iBits)
			bits[iBits] = 0;
	}

	constexpr void ShiftRight(uint32 shift)
	{
		if (shift == 0 || *this == 0)
			return;

		const uint32 fullChunksMoved = shift / nbBitsPerChunk;
		const uint32 movementInChunk = shift % nbBitsPerChunk;
		const uint32 complementMovementInChunk = nbBitsPerChunk - movementInChunk;

		const uint32 chunkCountResult = bits.size() - fullChunksMoved;
		if (chunkCountResult <= 0)
		{
			bits.resize(1);
			bits[0] = 0;
			return;
		}

		// Shifting by 32 is undefined, so special case
		if (complementMovementInChunk == nbBitsPerChunk)
		{
			for (uint32 i = 0; i < bits.size(); ++i)
			{
				if (i + fullChunksMoved >= bits.size())
					break;
				bits[i] = bits[i + fullChunksMoved];
			}
			Optimize();
			return;
		}

		for (uint32 i = 0; i < bits.size(); ++i)
		{
			bits[i] = bits[i + fullChunksMoved] >> movementInChunk;

			if (1 + i + fullChunksMoved >= bits.size())
				break;
			bits[i] += static_cast<uint32>(bits[1 + i + fullChunksMoved] << complementMovementInChunk);
		}
		Optimize();
	}

	// BITWISE OPERATORS
	constexpr UnsignedBigInt operator~() const
	{
		UnsignedBigInt temp = *this;
		for (uint32& bitChunk : temp.bits)
			bitChunk = ~bitChunk;
		return temp;
	}

	constexpr UnsignedBigInt operator|(const UnsignedBigInt& rhs) const
	{
		const bool isThisBigger = bits.size() >= rhs.bits.size();
		const UnsignedBigInt& biggerNb = isThisBigger ? bits : rhs;
		const UnsignedBigInt& lesserNb = isThisBigger ? rhs : bits;

		UnsignedBigInt result = biggerNb;
		for (uint32 i = 0; i < lesserNb.bits.size(); ++i)
			result.bits[i] |= lesserNb.bits[i];
		return result;
	}

	constexpr UnsignedBigInt operator&(const UnsignedBigInt& rhs) const
	{
		const bool isThisBigger = bits.size() >= rhs.bits.size();
		const UnsignedBigInt& biggerNb = isThisBigger ? bits : rhs;
		const UnsignedBigInt& lesserNb = isThisBigger ? rhs : bits;

		UnsignedBigInt result = lesserNb;
		for (uint32 i = 0; i < lesserNb.bits.size(); ++i)
			result.bits[i] &= biggerNb.bits[i];

		result.Optimize();
		return result;
	}

	constexpr UnsignedBigInt operator^(const UnsignedBigInt& rhs) const
	{
		const bool isThisBigger = bits.size() >= rhs.bits.size();
		const UnsignedBigInt& biggerNb = isThisBigger ? bits : rhs;
		const UnsignedBigInt& lesserNb = isThisBigger ? rhs : bits;

		UnsignedBigInt result = biggerNb;
		for (uint32 i = 0; i < lesserNb.bits.size(); ++i)
			result.bits[i] ^= lesserNb.bits[i];

		result.Optimize();
		return result;
	}

	constexpr UnsignedBigInt operator>>(uint32 nb) const
	{
		UnsignedBigInt res = *this;
		res.ShiftRight(nb);
		return res;
	}

	constexpr UnsignedBigInt operator<<(uint32 nb) const
	{
		UnsignedBigInt res = *this;
		res.ShiftLeft(nb);
		return res;
	}

	constexpr UnsignedBigInt& operator|=(const UnsignedBigInt& rhs)
	{
		*this = *this | rhs;
		return *this;
	}

	constexpr UnsignedBigInt& operator&=(const UnsignedBigInt& rhs)
	{
		*this = *this & rhs;
		return *this;
	}

	constexpr UnsignedBigInt& operator^=(const UnsignedBigInt& rhs)
	{
		*this = *this ^ rhs;
		return *this;
	}

	// Comparison Operators
	constexpr bool operator==(uint32 rhs) const
	{
		return bits.size() == 1 && bits[0] == rhs;
	}

	constexpr bool operator==(const UnsignedBigInt& rhs) const
	{
		uint32 i = 0;
		while (i < bits.size() && i < rhs.bits.size())
		{
			if (bits[i] != rhs.bits[i])
				return false;
			++i;
		}

		while (i < bits.size())
		{
			if (bits[i] != 0)
				return false;
			++i;
		}
		while (i < rhs.bits.size())
		{
			if (rhs.bits[i] != 0)
				return false;
			++i;
		}
		return true;
	}

	constexpr bool operator!=(uint32 rhs) const
	{
		return !(*this == rhs);
	}

	constexpr bool operator!=(const UnsignedBigInt& rhs) const
	{
		return !(*this == rhs);
	}

	constexpr std::strong_ordering operator<=>(uint32 rhs) const
	{
		if (bits.size() > 1)
			return std::strong_ordering::greater;
		if (bits[0] > rhs)
			return std::strong_ordering::greater;
		if (bits[0] < rhs)
			return std::strong_ordering::less;
		return std::strong_ordering::equal;
	}

	constexpr std::strong_ordering operator<=>(const UnsignedBigInt& rhs) const
	{
		for (int i = std::max(bits.size(), rhs.bits.size()) - 1; i >= 0; --i)
		{
			const uint32 bitsValue = i < bits.size() ? bits[i] : 0;
			const uint32 rhsValue = i < rhs.bits.size() ? rhs.bits[i] : 0;
			if (bitsValue > rhsValue)
				return std::strong_ordering::greater;
			if (bitsValue < rhsValue)
				return std::strong_ordering::less;
		}
		return std::strong_ordering::equal;
	}

	constexpr bool operator>(const UnsignedBigInt& rhs) const
	{
		for (int i = std::max(bits.size(), rhs.bits.size()) - 1; i >= 0; --i)
		{
			const uint32 bitsValue = i < bits.size() ? bits[i] : 0;
			const uint32 rhsValue = i < rhs.bits.size() ? rhs.bits[i] : 0;
			if (bitsValue > rhsValue)
				return true;
			if (bitsValue < rhsValue)
				return false;
		}
		return false;
	}

	constexpr bool operator>=(const UnsignedBigInt& rhs) const
	{
		for (int i = std::max(bits.size(), rhs.bits.size()) - 1; i >= 0; --i)
		{
			const uint32 bitsValue = i < bits.size() ? bits[i] : 0;
			const uint32 rhsValue = i < rhs.bits.size() ? rhs.bits[i] : 0;
			if (bitsValue > rhsValue)
				return true;
			if (bitsValue < rhsValue)
				return false;
		}
		return true;
	}

	constexpr bool operator<(const UnsignedBigInt& rhs) const
	{
		for (int i = std::max(bits.size(), rhs.bits.size()) - 1; i >= 0; --i)
		{
			const uint32 bitsValue = i < bits.size() ? bits[i] : 0;
			const uint32 rhsValue = i < rhs.bits.size() ? rhs.bits[i] : 0;
			if (bitsValue < rhsValue)
				return true;
			if (bitsValue > rhsValue)
				return false;
		}
		return false;
	}

	constexpr bool operator<=(const UnsignedBigInt& rhs) const
	{
		for (int i = std::max(bits.size(), rhs.bits.size()) - 1; i >= 0; --i)
		{
			const uint32 bitsValue = i < bits.size() ? bits[i] : 0;
			const uint32 rhsValue = i < rhs.bits.size() ? rhs.bits[i] : 0;
			if (bitsValue < rhsValue)
				return true;
			if (bitsValue > rhsValue)
				return false;
		}
		return true;
	}

	// Arithmetic Operators

	// Will rollover and won't 
	constexpr void AdditionOverflow(UnsignedBigInt& lhs, const UnsignedBigInt& rhs)
	{
		if (rhs.bits.size() > bits.size())
			bits.resize(rhs.bits.size(), 0);

		uint32 carry = 0;
		uint32 chunk;
		for (chunk = 0; chunk < rhs.bits.size() || carry > 0; ++chunk)
		{
			if (chunk >= bits.size())
				break;

			uint64 sum = carry;
			sum += static_cast<uint64>(bits[chunk]);
			if (chunk < rhs.bits.size())
				sum += static_cast<uint64>(rhs.bits[chunk]);

			bits[chunk] = static_cast<uint32>(sum);
			carry = sum >> nbBitsPerChunk;
		}

		Optimize();
	}

	constexpr UnsignedBigInt& operator+=(const UnsignedBigInt& rhs)
	{
		if (rhs.bits.size() > bits.size())
			bits.resize(rhs.bits.size(), 0);

		uint32 carry = 0;
		uint32 chunk;
		for (chunk = 0; chunk < rhs.bits.size() || carry > 0; ++chunk)
		{
			if (chunk >= bits.size())
				bits.emplace_back(0);

			uint64 sum = carry;
			sum += static_cast<uint64>(bits[chunk]);
			if (chunk < rhs.bits.size())
				sum += static_cast<uint64>(rhs.bits[chunk]);

			bits[chunk] = static_cast<uint32>(sum);
			carry = sum >> nbBitsPerChunk;
		}

		return *this;
	}

	constexpr UnsignedBigInt operator+(const UnsignedBigInt& rhs) const
	{
		UnsignedBigInt res = *this;
		res += rhs;
		return res;
	}

	constexpr UnsignedBigInt& operator-=(const UnsignedBigInt& rhs)
	{
		// 2's complement substraction
		UnsignedBigInt twosComplementRhs = ~rhs;
		const int bitsSizeDiff = bits.size() - rhs.bits.size();
		if (bitsSizeDiff > 0)
			twosComplementRhs.bits.insert(twosComplementRhs.bits.end(), bitsSizeDiff, ~0);

		AdditionOverflow(*this, twosComplementRhs);
		AdditionOverflow(*this, 1);
		return *this;
	}

	constexpr UnsignedBigInt operator-(const UnsignedBigInt& rhs) const
	{
		UnsignedBigInt res = *this;
		res -= rhs;
		return res;
	}

	constexpr UnsignedBigInt& operator++()
	{
		*this = *this + 1;
		return *this;
	}

	constexpr UnsignedBigInt operator++(int)
	{
		UnsignedBigInt temp = *this;
		++*this;
		return temp;
	}

	constexpr UnsignedBigInt& operator--()
	{
		*this = *this - 1;
		return *this;
	}

	constexpr UnsignedBigInt operator--(int)
	{
		UnsignedBigInt temp = *this;
		--*this;
		return temp;
	}

	constexpr UnsignedBigInt& operator*=(const UnsignedBigInt& rhs)
	{
		UnsignedBigInt res(0);
		const size_t likelyChunkSize = bits.size() + rhs.bits.size();
		res.bits.reserve(likelyChunkSize);

		for (uint32 thisChunkIdx = 0; thisChunkIdx < bits.size(); ++thisChunkIdx)
		{
			for (uint32 rhsChunkIdx = 0; rhsChunkIdx < rhs.bits.size(); ++rhsChunkIdx)
			{
				const uint64 productBits = static_cast<uint64>(bits[thisChunkIdx]) * static_cast<uint64>(rhs.bits[rhsChunkIdx]);

				UnsignedBigInt bigProduct(productBits);
				const uint32 chunkProductIdx = thisChunkIdx + rhsChunkIdx;
				bigProduct = bigProduct << chunkProductIdx * nbBitsPerChunk;

				res += bigProduct;
			}
		}

		*this = std::move(res);
		return *this;
	}

	constexpr UnsignedBigInt operator*(const UnsignedBigInt& rhs) const
	{
		UnsignedBigInt res = *this;
		res *= rhs;
		return res;
	}

	constexpr UnsignedBigInt& operator/=(const UnsignedBigInt& rhs)
	{
		if (rhs == 0)
		{
			throw std::runtime_error("Division by zero!");
		}

		if (rhs > *this)
		{
			*this = 0;
			this->Optimize();
			return *this;
		}

		// TODO: This seems horribly inefficient
		UnsignedBigInt result = 0;

		//const uint32 chunkDiff = static_cast<uint32>(bits.size() - rhs.bits.size());
		//if (chunkDiff > 1)
		//{
		//	const uint32 bitsShiftedMinimal = (chunkDiff - 1) * nbBitsPerChunk;
		//	result = 1;
		//	result = result << bitsShiftedMinimal;
		//	*this = *this >> bitsShiftedMinimal;
		//}

		while (*this >= rhs)
		{
			UnsignedBigInt resultIteration = 1;

			const uint32 baseShift = bits.size() > rhs.bits.size() ? bits.size() - rhs.bits.size() - 1 : 0;
			UnsignedBigInt divider = rhs << nbBitsPerChunk * baseShift;
			resultIteration.ShiftLeft(nbBitsPerChunk * baseShift);

			divider.ShiftLeft(1);
			while (*this >= divider)
			{
				resultIteration.ShiftLeft(1);
				divider.ShiftLeft(1);
			}
			divider.ShiftRight(1);

			*this -= divider;
			result += resultIteration;
		}

		result.Optimize();

		*this = std::move(result);
		return *this;
	}

	constexpr UnsignedBigInt operator/(const UnsignedBigInt& rhs) const
	{
		UnsignedBigInt res = *this;
		res /= rhs;
		return res;
	}

	constexpr UnsignedBigInt& operator%=(const UnsignedBigInt& rhs)
	{
		const UnsignedBigInt division = *this / rhs;
		*this -= division * rhs;
		this->Optimize();
		return *this;
	}

	constexpr UnsignedBigInt operator%(const UnsignedBigInt& rhs) const
	{
		UnsignedBigInt res(*this);
		res %= rhs;
		return res;
	}

	explicit constexpr operator uint64() const
	{
		if (bits.size() == 1)
			return static_cast<uint64>(bits[0]);
		else
			return (static_cast<uint64>(bits[1]) << nbBitsPerChunk) + static_cast<uint64>(bits[0]);
	}
	explicit constexpr operator uint32() const
	{
		return bits[0];
	}

	constexpr std::string ToString() const
	{
		if (*this == 0)
			return std::string("0");

		uint32 nbDigits = 0;
		UnsignedBigInt nb = *this;
		while (nb > 0)
		{
			nbDigits++;
			nb /= 10;
		}

		std::string s;
		s.resize(nbDigits);

		nb = *this;
		for (int digitIdx = nbDigits - 1; digitIdx >= 0; --digitIdx)
		{
			const uint32 digit = static_cast<uint32>(nb % 10);
			s.at(digitIdx) = static_cast<unsigned char>(digit) + '0';
			nb /= 10;
		}

		return s;
	}

	friend constexpr UnsignedBigInt operator|(const uint64 lhs, const UnsignedBigInt& rhs);
	friend constexpr UnsignedBigInt operator&(const uint64 lhs, const UnsignedBigInt& rhs);
	friend constexpr UnsignedBigInt operator^(const uint64 lhs, const UnsignedBigInt& rhs);

	friend constexpr bool operator==(const uint64 lhs, const UnsignedBigInt& rhs);
	friend constexpr bool operator!=(const uint64 lhs, const UnsignedBigInt& rhs);
	friend constexpr bool operator>(const uint64 lhs, const UnsignedBigInt& rhs);
	friend constexpr bool operator>=(const uint64 lhs, const UnsignedBigInt& rhs);
	friend constexpr bool operator<(const uint64 lhs, const UnsignedBigInt& rhs);
	friend constexpr bool operator<=(const uint64 lhs, const UnsignedBigInt& rhs);

	friend constexpr UnsignedBigInt operator+(const uint64 lhs, const UnsignedBigInt& rhs);
	friend constexpr UnsignedBigInt operator-(const uint64 lhs, const UnsignedBigInt& rhs);
	friend constexpr UnsignedBigInt operator*(const uint64 lhs, const UnsignedBigInt& rhs);
	friend constexpr UnsignedBigInt operator/(const uint64 lhs, const UnsignedBigInt& rhs);
	friend constexpr UnsignedBigInt operator%(const uint64 lhs, const UnsignedBigInt& rhs);
};

constexpr UnsignedBigInt operator|(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator|(lhs);
}
constexpr UnsignedBigInt operator&(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator&(lhs);
}
constexpr UnsignedBigInt operator^(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator^(lhs);
}

constexpr bool operator==(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator==(lhs);
}
constexpr bool operator!=(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator!=(lhs);
}

constexpr bool operator>(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator>(lhs);
}
constexpr bool operator>=(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator>=(lhs);
}
constexpr bool operator<(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator<(lhs);
}
constexpr bool operator<=(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator<=(lhs);
}

constexpr UnsignedBigInt operator+(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator+(lhs);
}

constexpr UnsignedBigInt operator-(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator-(lhs);
}

constexpr UnsignedBigInt operator*(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator*(lhs);
}

constexpr UnsignedBigInt operator/(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator/(lhs);
}

constexpr UnsignedBigInt operator%(const uint64 lhs, const UnsignedBigInt& rhs)
{
	return rhs.operator%(lhs);
}

using uBigInt = UnsignedBigInt;
