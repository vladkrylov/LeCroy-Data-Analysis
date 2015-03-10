#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TGraph.h"

#include "Waveform.h"

using namespace std;

const int linesToSkip = 5;
const int numberOfSignalPoints = 4002;

void testVectorFill(vector<double> &vec, double mean, double sgm);
void testWaveformFill(Waveform *wf, double mean, double sgm);

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

	double t, v;

	TFile rootFile("Data.root","RECREATE");
	TTree *tree = new TTree("T","Run tree");

	Waveform *wf = new Waveform(numberOfSignalPoints);
	tree->Branch("Waveforms", "Waveform", &wf);

//	for (double mean=0.; mean<50.2; mean += 0.5) {
//		wf->Init(numberOfSignalPoints, "test");
//		testWaveformFill(wf, mean, 0.5);
//		wf->CalculateParameters();
//		tree->Fill();
//	}

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

				wf->Init(numberOfSignalPoints, currentDataFileName.c_str());

				while (getline(currentDataFile, line)) {
					sscanf(line.c_str(), "%lf,%lf", &t, &v);
					wf->AddPoint(t, v);
				}
				wf->CalculateParameters();

//				tree->Fill();
				wf->Write();
				currentDataFile.close();
			}
		}
		f.close();
	}

	tree->Write();

	delete tree;
	delete wf;

	rootFile.Close();
	cout << "Done." << endl;

	/////////////////////////////////////
	return 0;
}

void testVectorFill(vector<double> &vec, double mean, double sgm)
{
	vec.clear();

	TRandom r;
	for(int i=0; i<1000; i++) {
		vec.push_back(r.Gaus(mean, sgm));
	}
}

void testWaveformFill(Waveform *wf, double mean, double sgm)
{
	TRandom r;
	for(int i=0; i<1000; i++) {
		wf->AddPoint(i, r.Gaus(mean, sgm));
	}
}

