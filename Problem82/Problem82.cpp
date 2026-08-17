// Problem 82: Path Sum: Three Ways

#include <format>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <sstream>
#include <vector>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;

static u64 Solve(const char* fileName)
{
	std::ifstream fileStream(fileName);

	if (!fileStream.is_open())
	{
		std::cout << "Error could not read file: " << fileName << std::endl;
		return 0;
	}

	std::vector<u32> matrix;

	std::string str;
	std::string token;

	int lineCount = 0;
	while (std::getline(fileStream, str))
	{
		++lineCount;

		std::stringstream strStream(str);
		while (std::getline(strStream, token, ','))
			matrix.push_back(std::stoul(token));
	}

	const int colCount = lineCount;
	const int rowCount = matrix.size() / colCount;

	std::vector<u64> partialSumsMatrix(matrix.size(), std::numeric_limits<u64>::max());

	struct QueueElement
	{
		u32 matrixCoord = 0;
		u64 partialSum = 0;
	};

	std::queue<QueueElement> coordsQueue;
	for (int y = 0; y < rowCount; ++y)
	{
		const u32 coord = y * colCount;
		coordsQueue.push({ coord, 0 });
	}

	while (!coordsQueue.empty())
	{
		const QueueElement elem = coordsQueue.front();
		coordsQueue.pop();

		const u64 elemPartialSum = elem.partialSum + matrix[elem.matrixCoord];
		const u64 curBestPartialSum = partialSumsMatrix[elem.matrixCoord];
		if (elemPartialSum >= curBestPartialSum)
			continue;

		partialSumsMatrix[elem.matrixCoord] = elemPartialSum;

		const u32 coordX = elem.matrixCoord % colCount;
		const u32 coordY = elem.matrixCoord / colCount;
		if (coordX + 1 < colCount)
		{
			QueueElement& newRightElem = coordsQueue.emplace();
			newRightElem.matrixCoord = coordY * colCount + coordX + 1;
			newRightElem.partialSum = elemPartialSum;
		}
		if (coordY + 1 < rowCount)
		{
			QueueElement& newBelowElem = coordsQueue.emplace();
			newBelowElem.matrixCoord = (coordY + 1) * colCount + coordX;
			newBelowElem.partialSum = elemPartialSum;
		}
		if (coordY > 0)
		{
			QueueElement& newUpElem = coordsQueue.emplace();
			newUpElem.matrixCoord = (coordY - 1) * colCount + coordX;
			newUpElem.partialSum = elemPartialSum;
		}
	}

	u64 minRightColumnSum = std::numeric_limits<u64>::max();
	for (u32 y = 0; y < rowCount; ++y)
	{
		const u32 lastElemRowIdx = y * colCount + colCount - 1;
		minRightColumnSum = std::min(minRightColumnSum, partialSumsMatrix[lastElemRowIdx]);
	}

	return minRightColumnSum;
}

int main()
{
	constexpr const char* fileName = "resources/0082_matrix.txt";
	const int sol = Solve(fileName);
	std::cout << "Solution 82: " << sol << std::endl;

	return 0;
}