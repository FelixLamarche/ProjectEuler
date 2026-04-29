// Problem 54 Poker Hands
// How many hands does player 1 win

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(0)

enum class HandType
{
	HighCard,
	OnePair,
	TwoPairs,
	ThreeOfAKind,
	Straight,
	Flush,
	FullHouse,
	FourOfAKind,
	StraightFlush,
	RoyalFlush
};

struct Hand
{
	static constexpr int handSize = 5;

	HandType handType;
	int cardValuesSorted[handSize];
	int pairingValues[2];
};

static int GetValueOfCard(const char cardChr)
{
	switch (cardChr)
	{
	case 'A':
		return 14;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'T':
		return 10;
	case 'J':
		return 11;
	case 'Q':
		return 12;
	case 'K':
		return 13;
	}

	assert(false);
	return 0;
}

static Hand GetHand(const char* handString)
{
	Hand hand{};

	for (int cardIdx = 0; cardIdx < 10; cardIdx += 2)
	{
		hand.cardValuesSorted[cardIdx / 2] = GetValueOfCard(handString[cardIdx]);
	}

	std::sort(hand.cardValuesSorted, (hand.cardValuesSorted + Hand::handSize), [](int a, int b) {return a > b; });

	constexpr int firstSuitIdx = 1;
	bool hasFlush = true;
	for (int suitIdx = 3; suitIdx < 10; suitIdx += 2)
	{
		if (handString[firstSuitIdx] != handString[suitIdx])
		{
			hasFlush = false;
			break;
		}
	}

	bool hasStraight = true;
	for (int cardIdx = 0; cardIdx < Hand::handSize - 1; ++cardIdx)
	{
		// Exception for ace wrap-around
		if (cardIdx == 0 && hand.cardValuesSorted[0] == 14 && hand.cardValuesSorted[1] == 5)
			continue;

		if (hand.cardValuesSorted[cardIdx] - hand.cardValuesSorted[cardIdx + 1] != 1)
		{
			hasStraight = false;
			break;
		}
	}

	if (hasStraight && hasFlush)
	{
		if (hand.cardValuesSorted[0] == 14)
			hand.handType = HandType::RoyalFlush;
		else
			hand.handType = HandType::StraightFlush;
		return hand;
	}
	else if (hasFlush)
	{
		hand.handType = HandType::Flush;
		return hand;
	}
	else if (hasStraight)
	{
		hand.handType = HandType::Straight;
		return hand;
	}

	int pairingAmounts[2] = { 0, 0 };

	for (int cardIdx = 0; cardIdx < Hand::handSize - 1; ++cardIdx)
	{
		const bool hasPairing = hand.cardValuesSorted[cardIdx] == hand.cardValuesSorted[cardIdx + 1];
		if (hasPairing)
		{
			const int pairingValue = hand.cardValuesSorted[cardIdx];

			if (hand.pairingValues[0] == pairingValue || hand.pairingValues[0] == 0)
			{
				hand.pairingValues[0] = pairingValue;
				pairingAmounts[0]++;
			}
			else
			{
				hand.pairingValues[1] = pairingValue;
				pairingAmounts[1]++;
			}
		}
	}

	// Order so most important value is the value corresponding to the most pairings
	if (pairingAmounts[1] > pairingAmounts[0])
	{
		std::swap(hand.pairingValues[0], hand.pairingValues[1]);
	}

	if (pairingAmounts[0] == 3)
	{
		hand.handType = HandType::FourOfAKind;
	}
	else if (pairingAmounts[0] == 2)
	{
		if (pairingAmounts[1] == 1)
			hand.handType = HandType::FullHouse;
		else
			hand.handType = HandType::ThreeOfAKind;
	}
	else if (pairingAmounts[0] == 1)
	{
		if (pairingAmounts[1] == 2)
			hand.handType = HandType::FullHouse;
		else if (pairingAmounts[1] == 1)
			hand.handType = HandType::TwoPairs;
		else
			hand.handType = HandType::OnePair;
	}
	else
	{
		hand.handType = HandType::HighCard;
	}

	return hand;
}

static bool DoesHand1BeatHand2(const Hand& hand1, const Hand& hand2)
{
	if (hand1.handType > hand2.handType)
		return true;

	if (hand1.handType < hand2.handType)
		return false;

	if (hand1.pairingValues[0] > hand2.pairingValues[0])
		return true;
	if (hand1.pairingValues[0] < hand2.pairingValues[0])
		return false;

	if (hand1.pairingValues[1] > hand2.pairingValues[1])
		return true;
	if (hand1.pairingValues[1] < hand2.pairingValues[1])
		return false;

	for (int i = 0; i < Hand::handSize; ++i)
	{
		if (hand1.cardValuesSorted[i] > hand2.cardValuesSorted[i])
			return true;
		if (hand1.cardValuesSorted[i] < hand2.cardValuesSorted[i])
			return false;
	}

	return false;
}

static int Solve()
{
	constexpr const char* fileName = "0054_poker.txt";
	if (!std::filesystem::exists(fileName))
	{
		std::cerr << "Could not find file: " << fileName << std::endl;
		return 0;
	}

	std::ifstream fileStream(fileName);

	int handsPlayer1Won = 0;

	std::string buffer;

	constexpr int cardChars = 3;
	constexpr int handSize = 5;
	constexpr int handCharLength = cardChars * handSize;
	while (std::getline(fileStream, buffer))
	{
		int charIdx = 0;
		char player1Hand[10]{};

		for (int cardIdx = 0; cardIdx < handSize; ++cardIdx)
		{
			player1Hand[(2 * cardIdx)] = buffer[(3 * cardIdx)];
			player1Hand[(2 * cardIdx) + 1] = buffer[(3 * cardIdx) + 1];
		}

		char player2Hand[10]{};

		charIdx += handCharLength;
		for (int cardIdx = 0; cardIdx < handSize; ++cardIdx)
		{
			player2Hand[(2 * cardIdx)] = buffer[(3 * cardIdx) + charIdx];
			player2Hand[(2 * cardIdx) + 1] = buffer[(3 * cardIdx) + 1 + charIdx];
		}

		const Hand hand1 = GetHand(player1Hand);
		const Hand hand2 = GetHand(player2Hand);

		if (DoesHand1BeatHand2(hand1, hand2))
		{
			++handsPlayer1Won;

			// LOGF("buffer of player 1 win: %s, handP1: %i, handP2: %i\n", buffer.c_str(), hand1.handType, hand2.handType);
		}
	}
	fileStream.close();

	return handsPlayer1Won;
}

void main()
{
	const int solution = Solve();
	std::cout << "Problem 54 Solution: " << solution << std::endl;
}
