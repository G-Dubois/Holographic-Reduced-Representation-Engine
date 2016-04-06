//  Program:		Holographic Reduced Representation Engine Specification
//  Filename:		hrrengine.h
//  Author:			Grayson M. Dubois
//  Mentor:			Dr. Joshua Phillips

#include <map>
#include <vector>

using namespace std;

typedef vector<float> HRR;

class HRREngine {
private:

	// Map stores all concepts as string name and HRR
	map<string, HRR> conceptMemory;

	// Integer indicates the size of vectors used in this engine
	int vectorSize;

	// Helper method invertVector calculates the approximate inversion of an HRR
	HRR invertVector(HRR hrr);

	// Calculate the dot product of two HRRs
	float dot(HRR hrr1, HRR hrr2);

	// Explode a string using '*' as a delimiter
	vector<string> explode(string str);

public:

	// Default constructor
	HRREngine();

	// Returns the general vector length
	int getVectorSize();

	// Sets the general vectors length
	void setVectorSize(int size);

	// Generates an hrr representation for the given vector
	HRR generateHRR();

	// Combines two concepts to form a complex concept
	string combineConcepts(string concept1, string concept2);

	// Extract a base concept from a complex concept and the former's complementary base concept
	string extractConcept(string complexConcept, string baseConcept);

	// Forms a complex concept by performing circular convolution on two hrrs
	HRR convolveHRRs(HRR hrr1, HRR hrr2);

	// Perform a circular correlation (involution) operation
	HRR correlateHRRs(HRR complexHRR, HRR hrr);

	// Output contents of hrr
	void printHRRVertical(HRR hrr);
	void printHRRHorizontal(HRR hrr);

	// Get user-defined values for an hrr
	void getUserDefinedHRR(HRR& hrr);

	// Method takes a concept name as a string and generates an HRR for it, storing them in concept memory and returning the HRR
	HRR encodeConcept(string name);

	// Method takes a vector of strings and encodes them, assigning them an hrr and storing them in concept memory
	void encodeConcepts(vector<string> concepts);

	// Method constructs a concept and all of its constituent concepts using a tree-like recursive algorithm
	HRR constructConcept(vector<string> concepts);


	/**
	 *  Method query() is a critical method for the engine
	 *		query() is overloaded to perform two functions, depending on its usage:
	 *			- takes a string value as an argument, checks to see if a representation exists for that value,
	 *			  and if a representation exists, then returns the HRR for the concept with that name
	 *			- takes an HRR as an argument, checks to see if a representation exists for that value, and if
	 *			  a representation exists, then returns the name of the concept that matches that representation
	 */
	HRR query(string name);
	string query(HRR hrr);

	// Find hrr by name
	HRR findHRRByName(string name);

	// Method lists the map of all concepts. Use only for debugging with small vectors.
	void listAllConcepts();

	// Method lists the names of all known concepts.
	void listAllConceptNames();

	// Compare two HRRs by taking their dot product and checking to see if the result is above a threshold
	bool compare(HRR hrr1, HRR hrr2);
};
