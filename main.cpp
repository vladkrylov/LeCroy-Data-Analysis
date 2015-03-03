#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"

typedef double values_t;

using namespace std;

const int linesToSkip = 5;
const int numberOfSignalPoints = 4002;

void testFill(vector<values_t> &vec, double mean, double sgm);

int main(int argc, char **argv)
{
	if (argc < 2) {
		cout <<"File with list of data files must be specified as an argument"<<endl;
		return 0;
	}

	char *inpFileName = argv[1];
	string currentDataFileName;
	string line;
	ifstream f(inpFileName);

	values_t t, v;
	vector<values_t> ts;
	vector<values_t> vs;

	ts.reserve(numberOfSignalPoints);
	vs.reserve(numberOfSignalPoints);

	TFile rootFile("Data.root","RECREATE");
	TTree *tree = new TTree("T","An example of a ROOT tree");
	tree->Branch("test", &vs);
	testFill(vs, 0, 1.5);
	tree->Fill();

//	int counter = 0;
//	if (f.is_open()) {
//		// loop through all data files
//		while ( getline(f, currentDataFileName) ) {
//			ifstream currentDataFile(currentDataFileName.c_str());
//			if (currentDataFile.is_open()) {
//				cout << ++counter << " Processing "<< currentDataFileName << endl;
//				// skip lines that don't contain signal data
//				for (int i=0; i<linesToSkip; i++) {
//					getline(currentDataFile, line);
//				}
//
//				ts.clear();
//				vs.clear();
//
//				while (getline(currentDataFile, line)) {
//					sscanf(line.c_str(), "%lf,%lf", &t, &v);
//					ts.push_back(t);
//					vs.push_back(v);
//
//
//				}
//				currentDataFile.close();
//			}
//		}
//		f.close();
//	}

	tree->Write();
	cout << "Done." << endl;
	return 0;
}

void testFill(vector<values_t> &vec, double mean, double sgm)
{
	vec.clear();

	TRandom r;
	for(int i=0; i<100; i++) {
		vec.push_back(r.Gaus(mean, sgm));
	}
}


