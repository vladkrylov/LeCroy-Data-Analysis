#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"

typedef double values_t;

using namespace std;

const int linesToSkip = 5;
const int numberOfSignalPoints = 4002;

double GetAmplitude(vector<double> &v, int polarity)
{
	double defAmp = 0.;
	int defPol = +1;

	if (v.empty()) {
		cout << "Warning from GetAmplitude: ";
		cout << "cannot calculate the amplitude of empty waveform" << endl;
		cout << "                           GetAmplitude returns " << defAmp << endl;
		return defAmp;
	}

	if (polarity == 0) {
		cout << "Warning from GetAmplitude: ";
		cout << "wrong polarity argument provided" << endl;
		cout << "                           set default polarity to " << defPol << endl;
		polarity = defPol;
	}

	double amp;
	if (polarity > 0) {
		amp = *max_element(v.begin(), v.end());
	} else {
		amp = *min_element(v.begin(), v.end());
	}
	return amp;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		cout <<"File with list of data files must be specified as an argument"<<endl;
		return 0;
	}

	char *inpFileName = argv[1];
	int polarity = 1;

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

	tree->Branch("time", &ts);
	tree->Branch("voltage", &vs);

	double amplitude;
	tree->Branch("amplitude", &amplitude);

	int counter = 0;
	if (f.is_open()) {
		// loop through all data files
		while ( getline(f, currentDataFileName) ) {
			ifstream currentDataFile(currentDataFileName.c_str());
			if (currentDataFile.is_open()) {
				cout << ++counter << " Processing "<< currentDataFileName << endl;
				// skip lines that don't contain signal data
				for (int i=0; i<linesToSkip; i++) {
					getline(currentDataFile, line);
				}

				ts.clear();
				vs.clear();

				while (getline(currentDataFile, line)) {
					sscanf(line.c_str(), "%lf,%lf", &t, &v);
					ts.push_back(t);
					vs.push_back(v);
				}
/**
 *  Here we have the entire waveform - time and voltage vectors
 *  All operations to get parameters of the waveform must be performed here
 *
 */
				amplitude = GetAmplitude(vs, polarity);
				tree->Fill();
				currentDataFile.close();
			}
		}
		f.close();
	}

	tree->Write();
	cout << "Done." << endl;
	return 0;
}




