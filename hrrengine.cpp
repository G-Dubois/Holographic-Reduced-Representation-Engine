//  Program:		Holographic Reduced Representation Engine Implementation
//  Filename:		hrrengine.cpp
//  Author:		Grayson M. Dubois
//  Mentor:		Dr. Joshua L. Phillips

#include<random>

vector<float> HRREngine::generateHRR(int size) {
	vector<float> vector(size);

	std::random_device rd;
	std::mt19937 e2(rd);

	std::normal_distribution<float> dist(0, 1);

	for (int i = 0; i < vector.size(); i++) {
	
	}

	return
}
