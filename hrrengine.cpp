//  Program:		Holographic Reduced Representation Engine Implementation
//  Filename:		hrrengine.cpp
//  Author:			Grayson M. Dubois
//  Mentor:			Dr. Joshua L. Phillips

#include <random>
#include <vector>
#include <cmath>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "hrrengine.h"

#define THRESHOLD 0.85

using namespace std;

// Generates an hrr representation for the given vector
HRR HRREngine::generateHRR() {
	HRR myVec( getVectorSize() );

	random_device rd;
	mt19937 e2(rd());

	float mean = 0.0;
	float stdDev = 1.0 / sqrt(float( getVectorSize() ));

	normal_distribution<float> dist(mean, stdDev);

	for (int i = 0; i < myVec.size(); i++) {
		myVec[i] = dist(e2);
	}

	return myVec;
}

// Outputs the contents of an hrr
void HRREngine::printHRRVertical(HRR hrr) {
	for (int i = 0; i < hrr.size(); i++) {
		cout << "| " << setprecision(9) << setw(12) << hrr[i] << " |\n";
	}
}
void HRREngine::printHRRHorizontal(HRR hrr){
	cout << "[ ";
	for (int i = 0; i < hrr.size() - 1; i++){
		cout << setprecision(9) << setw(12) << fixed;
		cout << hrr[i] << " , ";
	}
	cout << setprecision(9) << setw(12) << fixed << hrr[hrr.size() - 1] << setw(3) << " ]";
}

// Combines two concepts to form a complex concept
string HRREngine::combineConcepts(string concept1, string concept2){
	
	// Get the HRRs for each concept
	HRR hrr1 = query(concept1);
	HRR hrr2 = query(concept2);

	// Compute the convolution of the concept
	HRR newHrr = convolveHRRs(hrr1, hrr2);

	// Create the new name for the object (lexicographical order)
	//	Break the name of the first concept into its constituent parts, and store in descriptors
	//	Then, add each of the constituent parts of the second concept's name into descriptors
	vector<string> descriptors = explode(concept1);
	for (string str : explode(concept2) ){
		descriptors.push_back(str);
	}

	// Sort the descriptors
	sort(descriptors.begin(), descriptors.end());

	// Build the new name for the concept
	string name = "";
	for (int i = 0; i < descriptors.size(); i++) {
		name += descriptors[i];
		if (i != descriptors.size() -1)
			name += "*";
	}

	// Enter the new concept into concept memory
	query(name);

	return name;
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
		for (int i = 0; i < outerProduct.size(); i++){
			vector<float> newVector(hrr2.size());
			outerProduct[i] = newVector;
		}
		
		/*
		cout << "hrr1:\n";
		printHRRHorizontal(hrr1);
		cout << "\nhrr2:\n";
		printHRRHorizontal(hrr2);
		cout << "\nOuter product of hrr1 and hrr 2 ";*/
		for (int i = 0; i < hrr1.size(); i ++){
			//cout << "\n| ";
			for (int j = 0; j < hrr2.size(); j++){
				outerProduct[i][j] = hrr1[i] * hrr2[j];
				//cout << "\t" << outerProduct[i][j];
			}
			//cout << " |\n";
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

// Perform a circular correlation (involution) operation
HRR HRREngine::correlateHRRs(HRR complexHRR, HRR hrr) {
	HRR newConcept(vectorSize);
	HRR invertedVector(vectorSize);

	// Calculate the approximate inverse of the vector
	invertedVector = invertVector(hrr);

	// Perform involution operation by convolving the complex HRR with the inverted HRR
	newConcept = convolveHRRs(invertedVector, complexHRR);

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

// Method takes a concept name as a string and generates an HRR for it, storing them in concept memory and returning the HRR
HRR HRREngine::encodeConcept(string name){
	
	// Generate an HRR for this concept
	HRR newHRR = generateHRR();

	// Add this concept and its representation into the engine
	conceptMemory.insert( pair<string, HRR>( name, newHRR ));

	return newHRR;
}

// Method takes a vector of strings and stores each as an HRR in conceptMemory, if it does not already exist
void HRREngine::encodeConcepts(vector<string> concepts){
	for (string concept : concepts){
		conceptMemory.insert(pair<string, HRR>(concept, generateHRR()));
	}
}

// Returns the general length of the vector
int HRREngine::getVectorSize(){
	return vectorSize;
}

// Sets the general length of the vector
void HRREngine::setVectorSize(int size){
	vectorSize = size;
}

// Default constructor. Sets vector size to 128
HRREngine::HRREngine(){
	vectorSize = 128;
}

/**
 *  Method query() is a critical method for the engine
 *		query() is overloaded to perform two functions, depending on its usage:
 *			- takes a string value as an argument, checks to see if a representation exists for that value,
 *			  and if a representation exists, then returns the HRR for the concept with that name
 *			- takes an HRR as an argument, checks to see if a representation exists for that value, and if
 *			  a representation exists, then returns the name of the concept that matches that representation
 */
HRR HRREngine::query(string name){

	// Reorder the string
	vector<string> strings = explode(name);
	name = "";
	sort(strings.begin(), strings.end());
	for (int i = 0; i < strings.size(); i++){
		name += strings[i];
		if (i < strings.size() - 1)
			name += "*";
	}

	// See if a value exists for this concept in the map
	//	For each concept in concept memory, check if the key matches the name of the concept we are looking for
	for (pair<string, HRR> concept : conceptMemory){
		
		// If the name for the current concept is the name we are looking for, then we have found the concept 
		if ( concept.first == name ){

			// Return the hrr for this concept
			return concept.second;
		}
	}

	// If we did not return the value, we did not find the concept, thus we need to generate a new HRR for it and add it to the map
	// 	Make sure that if this is a complex concept, we break it into its constituent pieces, encode those, and then build up a
	//	representation through sequential convolutions
	strings = explode(name);
	sort(strings.begin(), strings.end());
	for (string str : strings){
		bool exists = false;
		for (pair<string, HRR> concept : conceptMemory){
			if (concept.first == str)
				exists = true;
		}
		if (!exists)
			encodeConcept(str);
	}

	// Sequentially convolve each concept into a complex one
	HRR newHRR = findHRRByName(strings[0]);
	for (int i = 1; i < strings.size(); i++){
		convolveHRRs(newHRR, findHRRByName(strings[i]));
	}

	name = "";
	sort(strings.begin(), strings.end());
	for (int i = 0; i < strings.size(); i++){
		name += strings[i];
		if (i < strings.size() - 1)
			name += "*";
	}

	conceptMemory.insert(pair<string, HRR>(name, newHRR));

	return newHRR;
}

string HRREngine::query(HRR hrr){
	float dotProduct;
	float bestMatch = 0;
	string match;
	// See if a representation exists for this concept in the map
	//	For each concept in concept memory, compare the HRRs to see if they represent the same concept
	for (pair<string, HRR> concept : conceptMemory){
		
		// Find the dot product of the queried hrr and the current hrr in the map
		dotProduct = dot(hrr, concept.second);

		cout << "\nDot product of hrr and " << concept.first << ": " << dotProduct << "\n";

		// If the dot product is the highest so far, then set the match to be the current representation in the map
		if (dotProduct > bestMatch){

			// The new best match is the current dot product
			bestMatch = dotProduct;

			// The new match is the name of the current concept
			match = concept.first;
		}

	}

	return match;
}

// Find hrr by name
HRR HRREngine::findHRRByName(string name){
	for (pair<string, HRR> concept: conceptMemory)
		if (concept.first == name) return concept.second;
	return vector<float> {0};
}

// Method lists the map of all concepts. Use only for debugging with small vectors.
void HRREngine::listAllConcepts(){
	// Iterate through the concept map, printing out concepts and their represenations
	for (pair<string, HRR> concept : conceptMemory) {
		cout << concept.first << "\t";
		printHRRHorizontal(concept.second);
		cout << "\n";
	}
}

// Method lists the names of all known concepts.
void HRREngine::listAllConceptNames(){
	// Iterate throught the concept map, printing out the names of concepts
	for (pair<string, HRR> concept : conceptMemory) {
		cout << concept.first << "\t";
	}
	cout << "\n";
}

// Private helper method invertVector calculates approximate inversion of an HRR
HRR HRREngine::invertVector(HRR hrr) {
	HRR invertedVector(vectorSize);

	invertedVector[0] = hrr[0];

	for (int i = 1; i < vectorSize; i++) {
		invertedVector[i] = hrr[vectorSize - i];
	}

	return invertedVector;
}

// Compare two HRRs by taking their dot product and checking to see if the result is above a threshold
bool HRREngine::compare(HRR hrr1, HRR hrr2){
	float dotProduct = dot(hrr1, hrr2);
	if (dotProduct >= THRESHOLD){
		return true;
	}
	return false;
}

// Calculate the dot product of two HRRs
float HRREngine::dot(HRR hrr1, HRR hrr2){
	float dotProduct = 0;
	for (int i = 0; i < vectorSize; i++) {
		dotProduct += hrr1[i] * hrr2[i];
	}
	return dotProduct;
}

// Explode a string using '*' as a delimiter
vector<string> HRREngine::explode(string str){
	vector<string> stringVector = vector<string>();
	char delimiter = '*';
	
	int pos = 0;
	string token;

	while ((pos = str.find(delimiter)) != string::npos){
		token = str.substr(0, pos);
		stringVector.push_back(token);
		str.erase(0, pos + 1);
	}
	stringVector.push_back(str);

	return stringVector;
}