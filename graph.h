#pragma once
#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string>
#include <list> 
#include <map>
#include <climits>
#include <vector>
#include <assert.h>

using namespace std;

class Graph
{
private:
	size_t numVertices;
	vector<string> vertexNames;
	vector<vector<int>>  adjMatrix;

	struct Edge {
		unsigned int vDest;
		int  cost;
		Edge(unsigned int v = 0, int c = -1) { vDest = v; cost = c; }
	};

public:
	Graph() :numVertices(0) {};
	~Graph() {};
	unsigned int getNumVertices() const { return numVertices; }
	int getEdgeCost(unsigned int v1, unsigned int v2) { return adjMatrix[v1][v2]; }
	string getVertexName(unsigned int v) const { return vertexNames[v]; }
	void read(ifstream& infile)
	{
		vector<list<Edge>> adjList;
		map<string, int> vertexNameIndex;


		string line;
		numVertices = 0;
		while (getline(infile, line))
		{
			numVertices++;
			istringstream iss(line);
			int n;
			int c;
			int vLabel;
			string vertex_name;
			vector<int> newRow;
			iss >> vLabel;
			iss >> vertex_name;
			vertexNameIndex[vertex_name] = numVertices - 1;
			vertexNames.push_back(vertex_name);

			list<Edge> tempList;
			tempList.clear();
			while (iss >> n)
			{
				iss >> c;
				n--;
				tempList.push_back(Edge(n, c));
			}
			adjList.push_back(tempList);
		}



		assert(numVertices == adjList.size());
		adjMatrix.resize(numVertices);
		for (size_t i = 0; i < numVertices; i++)
			adjMatrix.at(i).resize(numVertices);

		for (size_t i = 0; i < numVertices; i++) {
			for (size_t j = 0; j < numVertices; j++) {
				adjMatrix[i][j] = INT_MAX;
			}
		}

		for (size_t i = 0; i < numVertices; i++)
			adjMatrix[i][i] = 0;

		for (size_t i = 0; i < adjList.size(); i++) {
			for (list<Edge>::iterator itr = adjList.at(i).begin(); itr != adjList[i].end(); itr++) {
				unsigned int j = itr->vDest;
				adjMatrix[i][j] = itr->cost;
			}
		}
	}
	void print(ostream& outfile = cout) {
		for (size_t i = 0; i < numVertices; i++) {
			for (size_t j = 0; j < numVertices; j++) {
				if (adjMatrix[i][j] < INT_MAX) {
					outfile << adjMatrix[i][j] << " ";
				}
				else
				{
					outfile << "INF ";
				}
			}
			outfile << endl;
		}
	}
};

#endif