#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"

#include "Waveform.h"

typedef double values_t;

using namespace std;

const int linesToSkip = 5;
const int numberOfSignalPoints = 4002;

int main(int argc, char **argv)
{
	if (argc < 3) {
		// FIXME
		cout <<"File with list of data files must be specified as an argument"<<endl;
		return 0;
	}

	char *inpFileName = argv[1];
	char *outRootFileName = argv[2];
	int polarity = -1;

	string currentDataFileName;
	string line;
	ifstream f(inpFileName);

	values_t t, v;

	Waveform *wf = new Waveform(numberOfSignalPoints, polarity);

	TFile rootFile(outRootFileName,"RECREATE");
	TTree *tree = new TTree("T","An example of a ROOT tree");

	double amplitude;
	tree->Branch("amplitude", &amplitude);

	int counter = 0;
	if (f.is_open()) {
		// loop through all data files
		while ( getline(f, currentDataFileName) ) {
			ifstream currentDataFile(currentDataFileName.c_str());
			if (currentDataFile.is_open()) {
//				cout << ++counter << " Processing "<< currentDataFileName << endl;
				// skip lines that don't contain signal data
				for (int i=0; i<linesToSkip; i++) {
					getline(currentDataFile, line);
				}

				wf->Init(numberOfSignalPoints, currentDataFileName.c_str());
				while (getline(currentDataFile, line)) {
					sscanf(line.c_str(), "%lf,%lf", &t, &v);
					wf->AddPoint(t, v);
				}
				wf->CalculateParameters();
/**
 *  Here we have the entire waveform stored in object of class Waveform
 *  All operations to get parameters of the waveform must be performed here
 *
 */
				amplitude = wf->GetAmplitude();
				tree->Fill();
				wf->Write();
				currentDataFile.close();
			}
		}
		f.close();
	}

	tree->Write();
	cout << "Done." << endl;
	return 0;
}




