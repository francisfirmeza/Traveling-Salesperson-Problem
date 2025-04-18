//CS 320 - 02
//Christian Ferrer
//Francis Firmeza
//Zuhair Khan
//Emanuel Garza
#include "graph.h"
#include <iostream>
#include <fstream>
#include "Tsp.h"


int main() {
	std::cout << "Enter a filename for graph input: ";
	string filename;
	std::cin >> filename;
	ifstream infile{ filename };
	if (!infile) {
		std::cerr << "Error opening file " << filename << "\n";
		return 1;
	}
	Graph g;
	g.read(infile);
	infile.close();

	Tsp tsp{ g };
	tsp.solve();

	return 0;
}