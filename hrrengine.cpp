//  Program:		Holographic Reduced Representation Engine Implementation
//  Filename:		hrrengine.cpp
//  Author:		Grayson M. Dubois
//  Mentor:		Dr. Joshua L. Phillips

#include <random>
#include <vector>
#include <cmath>
#include <iostream>
#include "hrrengine.h"

using namespace std;

// Generates an hrr representation for the given vector
HRR HRREngine::generateHRR(int size) {
	HRR myVec(size);

	random_device rd;
	mt19937 e2(rd());

	float mean = 0.0;
	float stdDev = 1.0 / sqrt(float(size));

	normal_distribution<float> dist(mean, stdDev);

	for (int i = 0; i < myVec.size(); i++) {
		myVec[i] = dist(e2);
	}

	return myVec;
}

// Outputs the contents of an hrr
void HRREngine::printHRR(HRR hrr) {
	for (int i = 0; i < hrr.size(); i++) {
		cout << "|" << hrr[i] << "|\n";
	}
}

// Forms a complex concept by performing circular convolution on two hrrs
HRR HRREngine::convolveHRRs(HRR hrr1, HRR hrr2) {
	HRR newConcept(hrr1.size());

	if (hrr1.size() != hrr2.size()) {
		// Notify user if attempted to convolve vectors of differing length
		cout << "ERROR: Cannot convolve two hrrs of differing size!\n";
	} else {

		// Form the outer product of hrr1 and hrr2
		vector<vector<float>> outerProduct(hrr1.size());
		cout << "outerProduct.size() == " << outerProduct.size() << '\n';
		for (int i = 0; i < outerProduct.size(); i++){
			vector<float> newVector(hrr2.size());
			cout << "newVector.size() == " << newVector.size() << '\n';
			outerProduct[i] = newVector;
		}
		
		
		cout << "hrr1:\n";
		printHRR(hrr1);
		cout << "hrr2:\n";
		printHRR(hrr2);
		cout << "\nOuter product of hrr1 and hrr 2 ";
		for (int i = 0; i < hrr1.size(); i ++){
			cout << "\n| ";
			for (int j = 0; j < hrr2.size(); j++){
				outerProduct[i][j] = hrr1[i] * hrr2[j];
				cout << "\t" << outerProduct[i][j];
			}
			cout << " |\n";
		}

		// Perform circular convolution
		for (int j = 0; j < hrr1.size(); j++){
			float sum = 0;
			for (int i = j, k = 0; k <= j; i--, k++){
				sum += hrr1[i] * hrr2[k];

			}
			for (int i = hrr2.size()-1, k = j+1; k <= hrr2.size()-1; i--, k++){
				sum += hrr1[i] * hrr2[k];
			}
			newConcept[j] = sum;
		}

	}

	return newConcept;
}

// Get user-defined values for an hrr
void HRREngine::getUserDefinedHRR(HRR& hrr){

	// Get continuous values for an HRR for each value
	cout << "Please input each value for hrr. Values needed: " << hrr.size() <<"\nInput here: ";
	for (int i = 0; i < hrr.size() ; i++){
		cin >> hrr[i];
	}
	
}