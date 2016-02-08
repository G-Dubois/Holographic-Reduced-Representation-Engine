//  Program:		Holographic Reduced Representation Engine Specification
//  Filename:		hrrengine.h
//  Author:		Grayson M. Dubois
//  Mentor:		Dr. Joshua Phillips

#include <map>
#include <vector>

using namespace std;

typedef vector<float> HRR;

class HRREngine {
private:
	map<string, HRR> conceptMemory;
	int vectorSize;

public:

	// Default constructor
	HRREngine();

	// Returns the general vector length
	int getVectorSize();

	// Sets the general vectors length
	void setVectorSize(int size);


	// Generates an hrr representation for the given vector
	HRR generateHRR();

	// Forms a complex concept by performing circular convolution on two hrrs
	HRR convolveHRRs(HRR hrr1, HRR hrr2);

	// Output contents of hrr
	void printHRRVertical(HRR hrr);
	void printHRRHorizontal(HRR hrr);

	// Get user-defined values for an hrr
	void getUserDefinedHRR(HRR& hrr);

	// Method takes a vector of strings an encodes them, assigning them an hrr and storing them in concept memory
	void encodeConcepts(vector<string> concepts);

	// Method lists the map of all concepts. Use only for debugging with small vectors.
	void listAllConcepts();
	
};
