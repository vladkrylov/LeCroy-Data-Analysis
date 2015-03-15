#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

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
	if (argc < 4) {
		// FIXME
		cout <<"File with list of data files must be specified as an argument"<<endl;
		return 0;
	}

	char *inpFileName = argv[1];
	char *outRootFileName = argv[2];
	char *infoFileName = argv[3];
	int polarity = -1;

	string currentDataFileName;
	string line;
	ifstream f(inpFileName);

	values_t t, v;

	Waveform *wf = new Waveform(numberOfSignalPoints, polarity);

	TFile rootFile(outRootFileName,"RECREATE");

	/**--------------------------------------------------------------------------
	 * Here we add another tree to .root file that contains all the additional
	 * information about the current run if corresponded .yaml file was provided
	 * in argv arguments
	 *---------------------------------------------------------------------------
	 */
	char parName[30];
	float parValue;
	ifstream info(infoFileName);
	vector<float> paramsValues;
	paramsValues.reserve(32);
	TBranch *tb;

	int paramsCounter = 0;

	if (info.is_open()) {
		TTree *infoTree = new TTree("Info","Run info tree");
		while ( getline(info, line) ) {
			sscanf(line.c_str(), "%[^:]: %f", parName, &parValue);
			paramsValues.push_back(parValue);
//			cout << parName << " --> " << parValue << endl;

			tb = infoTree->Branch(parName, &paramsValues.at(paramsCounter));
			tb->Fill();
			paramsCounter++;
		}
		infoTree->Fill();
		infoTree->Write();
	}


	/*------------------------------------------------------------------------------
	 * Here we process all the waveforms and write to .root file their parameters
	 * Also if specified we write all the waveforms as objects to separate directory
	 * in the same .root file
	 *------------------------------------------------------------------------------
	 */
	rootFile.mkdir("Waveforms", "Waveforms");
	rootFile.cd("Waveforms");
	TTree *tree = new TTree("T","Data tree");

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

	rootFile.cd();
	tree->Write();

	cout << "Done." << endl;
	return 0;
}




