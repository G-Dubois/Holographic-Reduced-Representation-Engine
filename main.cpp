//
// Created by Grayson on 2/1/2016.
//

#include <iostream>
#include <vector>
#include "hrrengine.h"

using namespace std;

int main (int argc, char** argv) {

	int size;
	HRR myVec;
	HRR myVec2;

	cout << "What size vectors do you want to create? ";
	cin >> size;

	HRREngine engine;
	myVec = engine.generateHRR(size);

	HRR hrr1(size);
	HRR hrr2(size);

	engine.getUserDefinedHRR(hrr1);
	engine.getUserDefinedHRR(hrr2);

	myVec = engine.convolveHRRs(hrr1, hrr2);

	engine.printHRR(myVec);

	return 0;
}
