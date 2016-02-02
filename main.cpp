//
// Created by Grayson on 2/1/2016.
//

#include <iostream>
#include <vector>
#include <hrr.h>

using namespace std;

int main (int argc, char** argv) {

	int size;
	vector<float> myVec;

	cout << "What size vector do you want to create? ";
	cin >> size;

	myVec.resize(size);

	HRREngine engine;
	engine.generateHRR(myVec&);

	for (int i = 0; i < myVec.size(); i++) {
		cout << "|" << myVec[i] << "|\n";
	}

	return 0;
}
