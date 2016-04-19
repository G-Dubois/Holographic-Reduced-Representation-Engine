//  Program:		Holographic Reduced Representation Engine Implementation
//  Filename:		main.cpp
//  Author:			Grayson M. Dubois
//  Mentor:			Dr. Joshua L. Phillips

#include <fstream>
#include <iostream>
#include <vector>
#include "hrrengine.h"

using namespace std;

void printMenu();

int main (int argc, char** argv) {

	// Declare variables
	int size;
	char option;
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

	// Set up the HRR engine
	HRREngine engine;
	engine.setVectorSize(size);

	do{

		printMenu();
		cin >> option;

		switch (option){
			case '1':
				cout << "Please enter name of concept to search for: ";
				cin >> name;
				hrr = engine.query(name);
				//engine.printHRRHorizontal(hrr);
				break;
			case '2':
				cout << "Please enter name of concept to search for by representation: ";
				cin >> name;
				hrr = engine.query(name);
				//cout << "Representation: ";
				//engine.printHRRHorizontal(hrr);
				cout << "\nRepresentation is most like: ";
				cout << engine.query(hrr) << "\n\n";
				break;
			case '3':
				// Get the name of the input file
				cout << "Please input name of file to read from: ";
				cin >> filename;

				// Open input filestream
				fin.open( filename );

				// While there is more to read, read a concept and query the engine, adding it if it does not exists
				while (fin >> temp){
					engine.query(temp);
				}
				break;
			case '4':
				// Get the names of the two vectors to combine
				cout << "Input the first concept: ";
				cin >> name;
				cout << "Input the second concept: ";
				cin >> name2;

				name = engine.combineConcepts(name, name2);
				cout << "The new concept is: " << name << "\n";
				break;
			case '5':
				// Get the names of the two vectors to correlate
				cout << "Input the complex concept: ";
				cin >> name;
				cout << "Input the base concept: ";
				cin >> name2;

				name = engine.extractConcept(name, name2);
				cout << "The concept that is most similar to the extracted concept is: " << name << "\n";
				break;
			case '6':
				engine.listAllConcepts();
				break;
			case '7':
				engine.listAllConceptNames();
				break;
			case '8':
				cout << "Input the name of the concept to unpack by name: ";
				cin >> name;
			 	unpackedConceptStrings = engine.unpack(name);
				for (string concept : unpackedConceptStrings)
					cout << ( concept == "" ? "LOL" : concept) << "\n";
				break;
			case '9':
				cout << "Input the name of the concept to unpack by representation: ";
				cin >> name;
			 	unpackedConceptHrrs = engine.unpack(engine.query(name));
				for (HRR concept : unpackedConceptHrrs)
					cout << ( engine.query(concept) == "" ? "LOL" : engine.query(concept)) << "\n";
				break;
			case '0':
				cout << "\nEXIT";
				break;
			default:
				cout << "ERROR: Incorrect option entered\n";
				break;
		}
		cout << "\n";

	}while (!(option == '0'));

	return 0;
}

// Print menu options to console
void printMenu(){

	cout << "\nInput a value to select which operation to perform\n"
		 << "\t1 - Search for a concept by name\n"
		 << "\t2 - Search for a concept by representation\n"
		 << "\t3 - Read in concepts from file\n"
		 << "\t4 - Convolve two concepts\n"
		 << "\t5 - Correlate two concepts\n"
		 << "\t6 - Print all known concepts\n"
		 << "\t7 - Print concepts names\n"
		 << "\t8 - Unpack a concept by name\n"
		 << "\t9 - Unpack a concept by representation\n"
		 << "\t0 - Quit\n"
		 << "INPUT: ";
}
