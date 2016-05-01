//  Program:		Holographic Reduced Representation Engine Implementation
//  Filename:		main.cpp
//  Author:			Grayson M. Dubois
//  Mentor:			Dr. Joshua L. Phillips

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <iomanip>
#include "hrrengine.h"

using namespace std;

void printMenu();
HRR inputHRR();
void printHRRString(HRR hrr);

bool fileoutput;
HRREngine engine;

int main (int argc, char* argv[]) {

	fileoutput = false;

	string flagstring = "fileoutput";
	if ( argc > 1 && strcmp(argv[1], flagstring.c_str()) == 0) fileoutput = true;

	// Declare variables
	int size;
	string option;
	string name = "";
	string name2 = "";
	ifstream fin;
	vector<string> concepts = {};
	string temp;
	string filename;
	HRR hrr;
	HRR hrr2;
	vector<string> unpackedConceptStrings = {};
	vector<HRR> unpackedConceptHrrs = {};

	// Initiate program. Get size to use when working with vectors
	cout << "***Welcome to the HRR Engine tester!***\n"
		 << "What size vectors do you want to create? ";
	cin >> size;

	// For file output testing
	if (fileoutput) cout << size << "\n";

	// Set up the HRR engine
	engine.setVectorSize(size);

	cout << "Options are:\n";
	printMenu();

	do{
		cout << "\n>>> ";
		cin >> option;

		// For file output testing
		if (fileoutput) cout << option << "\n";

		if (option == "encode") {
			cout << "Please enter name of concept to encode: ";
			cin >> name;

			// For file output testing
			if (fileoutput) cout << name << "\n";

			hrr = engine.query(name);
			cout << name << "\t";
			engine.printHRRHorizontal(hrr);
			cout << "\n";
		} else if (option == "search") {
			hrr = inputHRR();
			name = engine.query(hrr);
			cout << "\nThe concept that is most similar to the extracted concept is:\n" << name << "\t";
			engine.printHRRHorizontal(engine.query(name));
			cout << "\n";
		} else if (option == "read") {
			// Get the name of the input file
			cout << "Please input name of file to read from: ";
			cin >> filename;

			// For file output testing
			if (fileoutput) cout << filename << "\n";

			// Open input filestream
			fin.open( filename );

			// While there is more to read, read a concept and query the engine, adding it if it does not exists
			while (fin >> temp){
				engine.query(temp);
			}
			cout << "\n";
		} else if (option == "convolve") {
			// Get the names of the two vectors to combine
			cout << "Input the first concept: ";
			cin >> name;

			// For file output testing
			if (fileoutput) cout << name << "\n";

			cout << "Input the second concept: ";
			cin >> name2;

			// For file output testing
			if (fileoutput) cout << name2 << "\n";

			name = engine.combineConcepts(name, name2);
			cout << "The new concept is:\n" << name << "\t";
			engine.printHRRHorizontal(engine.query(name));
			cout << "\n";
		} else if (option == "correlate") {
			// Get the names of the two vectors to correlate
			cout << "Input the complex concept: ";
			cin >> name;

			// For file output testing
			if (fileoutput) cout << name << "\n";

			cout << "Input the base concept: ";
			cin >> name2;

			// For file output testing
			if (fileoutput) cout << name2 << "\n";

			name = engine.extractConcept(name, name2);
			cout << "\nThe concept that is most similar to the extracted concept is:\n" << name << "\t";
			engine.printHRRHorizontal(engine.query(name));
			cout << "\n";
		} else if (option == "print") {
			engine.listAllConcepts();
		} else if (option == "construct") {
			cout << "Input the name of the concept to construct: ";
			cin >> name;

			// For file output testing
			if (fileoutput) cout << name << "\n";

			engine.construct(name);
		} else if (option == "unpack") {
			cout << "Input the name of the concept to unpack:";
			cin >> name;

			// For file output testing
			if (fileoutput) cout << name << "\n";

			unpackedConceptStrings = engine.unpack(name);
			for (string concept : unpackedConceptStrings) {
				cout << ( concept == "" ? "LOL" : concept + "\t");
				engine.printHRRHorizontal( engine.query(concept) );
				cout << "\n";
			}
		} else if (option == "decode") {
			cout << "Input the name of the concept to unpack by representation: ";
			cin >> name;

			// For file output testing
			if (fileoutput) cout << name << "\n";

			unpackedConceptHrrs = engine.unpack(engine.query(name));
			for (HRR concept : unpackedConceptHrrs)
				cout << ( engine.query(concept) == "" ? "EMPTY" : engine.query(concept)) << "\n";
		} else if (option == "quit") {
			cout << "\nEXIT\n";
		} else if (option == "help") {
			cout << "Options are:\n";
			printMenu();
			cout << "\n";
		} else {
			cout << "ERROR: Incorrect option entered. Use \'help\' to display commands\n";
		}

	}while (!(option == "quit"));

	return 0;
}

// Print menu options to console
void printMenu(){
	cout << "\tencode\t\tEncode a representation for a concept\n"
		 << "\tdecode\t\tDecode a representation to find the concept\n"
		 << "\tsearch\t\tFind a concept in memory\n"
		 << "\tread\t\tRead in concepts from a file\n"
		 << "\tconvolve\tCombine two base concepts using circular convolution\n"
		 << "\tcorrelate\tExtract a base concept from a complex concept using circular correlation\n"
		 << "\tconstruct\tForce construction of all base concepts of a complex concept\n"
		 << "\tprint\t\tPrint all known concepts and their representations\n"
		 << "\tunpack\t\tUnpack a representation into its constituent concepts\n"
		 << "\tquit\n";
}

void printHRRString(HRR hrr) {
	for (double val : hrr) {
		cout << setprecision(3) <<val << " ";
	}
}

HRR inputHRR(){

	cout << "Please input each value for representation. Values needed: " << engine.getVectorSize() <<"\nInput here: ";
	HRR hrr;

	if (fileoutput) {
		string name;
		cin >> name;
		hrr = engine.findHRRByName(name);
		printHRRString(hrr);
	} else {
		vector<double> values(engine.getVectorSize());

		for (int i = 0; i < engine.getVectorSize(); i++){
			cin >> values[i];

			if (fileoutput) cout << values[i];
		}
		hrr = engine.getUserDefinedHRR(values);
	}

	return hrr;
}
