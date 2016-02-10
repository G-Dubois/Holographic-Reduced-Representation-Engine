//
// Created by Grayson on 2/1/2016.
//

#include <fstream>
#include <iostream>
#include <vector>
#include "hrrengine.h"

using namespace std;

int main (int argc, char** argv) {

	// Declare variables
	int size;
	//HRR myVec;
	//HRR myVec2;
	ifstream fin;
	vector<string> concepts = {};

	cout << "What size vectors do you want to create? ";
	cin >> size;

	// Set up the HRR engine
	HRREngine engine;
	engine.setVectorSize(size);
	//myVec = engine.generateHRR();

	// Read the concepts from the input file, if one is provided as a command line argument
	if (argc > 1){
		// Open input filestream
		fin.open( argv[1] );
		string temp;
		
		// While there is more to read, read a concept and push it into concepts vector
		while (fin >> temp){
			concepts.push_back(temp);
		}

		// Print out each string in concepts 
		for (string concept: concepts){
			cout << concept << "\n";
		}

		// Encode each string in concepts vector and store in a map
		engine.encodeConcepts( concepts );

	}

	engine.listAllConcepts();

	/*
	HRR hrr1(size);
	HRR hrr2(size);

	engine.getUserDefinedHRR(hrr1);
	engine.getUserDefinedHRR(hrr2);

	myVec = engine.convolveHRRs(hrr1, hrr2);
	*/

	//engine.printHRRVertical(myVec);

	return 0;
}
