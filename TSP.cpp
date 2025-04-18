#include "Tsp.h"
#include <algorithm>

uint32_t Tsp::minTourCost(int index, const std::bitset<32> s)
{
	uint32_t aCost;
	size_t bestJ;
	bool hasFoundOne = false;
	size_t bitsetNum = s.to_ulong();

	if (s.none())
		return memoCost[index][0];

	if (memoCost[index][bitsetNum] >= 0)
		return memoCost[index][bitsetNum];

	uint32_t bestCost = INT_MAX;
	for (size_t j = 0; j < g.getNumVertices(); ++j) {
		if (s.test(j) == 1) {
			std::bitset<32> sCopy = s;
			sCopy.flip(j);
			aCost = g.getEdgeCost(index, j) + minTourCost(j, sCopy);
			if (aCost < bestCost) {
				hasFoundOne = true;
				bestCost = aCost;
				bestJ = j;
			}
		}
	}

	if (hasFoundOne) {
		memoCost[index][bitsetNum] = bestCost;
		memoPath[index][bitsetNum] = bestJ;
	}

	return bestCost;
}

void Tsp::outputPath(const int start, const std::bitset<32> s, const int minCost) const
{
	if (minCost == INT_MAX) {
		std::cout << "No Hamiltonian Cycle\n";
		return;
	}

	int currentIndex = start;

	std::bitset<32> currentSet = s;

	std::cout << "Optimal Tour Cost = [" << minCost << ", <";

	while (currentSet.any()) {
		int nextIndex = memoPath[currentIndex][currentSet.to_ulong()];
		std::cout << g.getVertexName(currentIndex) << ", ";
		currentSet.flip(nextIndex);
		currentIndex = nextIndex;
	}
	std::cout << g.getVertexName(currentIndex) << ">]\n";
}

void Tsp::solve()
{
	std::bitset<32> initialSet;
	for (size_t i = 1; i < g.getNumVertices(); ++i) initialSet.set(i);

	int bestCost = static_cast<int>(minTourCost(0, initialSet));


	std::cout << "\n";
	outputPath(0, initialSet, bestCost);
}
