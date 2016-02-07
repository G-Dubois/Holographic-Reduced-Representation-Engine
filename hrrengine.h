//  Program:		Holographic Reduced Representation Engine Specification
//  Filename:		hrrengine.h
//  Author:		Grayson M. Dubois
//  Mentor:		Dr. Joshua Phillips

#include <vector>

using namespace std;

typedef vector<float> HRR;

class HRREngine {
public:
	// Generates an hrr representation for the given vector
	HRR generateHRR(int size);

	// Forms a complex concept by performing circular convolution on two hrrs
	HRR convolveHRRs(HRR hrr1, HRR hrr2);

	// Output contents of hrr
	void printHRR(HRR hrr);

	// Get user-defined values for an hrr
	void getUserDefinedHRR(HRR& hrr);
	
};
