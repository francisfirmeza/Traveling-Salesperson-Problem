#pragma once
#ifndef _TSP_PROBLEM_H
#define _TSP_PROBLEM_H

#include <bitset>
#include <iostream>
#include <vector>
#include "graph.h"
#include <math.h>

class Tsp {
private:
	Graph g;
	std::vector<std::vector<int>> memoCost;
	std::vector<std::vector<int>> memoPath;

	uint32_t minTourCost(int index, const std::bitset<32> s);
	void outputPath(const int start, const std::bitset<32> s, const int minCost) const;
public:
	Tsp(Graph g) : g{ g } {
		size_t numVertices = g.getNumVertices();
		memoCost.resize(numVertices);
		memoPath.resize(numVertices);
		for (int i = 0; i < numVertices; ++i) {
			memoCost[i].resize(pow(2, numVertices));
			memoPath[i].resize(pow(2, numVertices));
		}
		for (std::vector<int>& v : memoCost) std::fill(v.begin(), v.end(), -1);
		for (std::vector<int>& v : memoPath) std::fill(v.begin(), v.end(), 0);

		for (size_t i = 1; i < numVertices; ++i)
			memoCost[i][0] = g.getEdgeCost(i, 0);
	}
	void solve();
};

#endif