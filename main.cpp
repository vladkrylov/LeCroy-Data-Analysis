#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TGraph.h"
#include "TDirectory.h"

#include "Waveform.h"

using namespace std;

const int linesToSkip = 5;
const int numberOfSignalPoints = 4002;

void testVectorFill(vector<double> &vec, double mean, double sgm);
void testWaveformFill(Waveform *wf, double mean, double sgm);
int GetChannelNumber(const char* filename);

int main(int argc, char **argv)
{
	if (argc < 2) {
		cout <<"File with list of data files must be specified as an argument"<<endl;
		return 0;
	}
	int p = 1;	// polarity

	char *inpFileName = argv[1];
	string currentDataFileName;
	string line;
	ifstream f(inpFileName);

	double t, v;

	TString branchName = "Waveforms";
	TFile rootFile("Data.root","RECREATE");
	TTree *tree = new TTree("T","Run tree");

	Waveform *wf = new Waveform(numberOfSignalPoints, p);
	tree->Branch(branchName.Data(), "Waveform", &wf);

//	TString branchNameBase = "Waveforms";
//	TString branchName;
//
//	int numberOfChannels = 4;
//	Waveform **wf = new Waveform*[];
//	for(int i=0; i<numberOfChannels; i++) {
//		 wf[i] = new Waveform(numberOfSignalPoints);
//		 branchName = branchNameBase + i;
//		 tree->Branch(branchName.Data(), "Waveform", &wf[i]);
//	}

//	rootFile.mkdir("a");
//	rootFile.cd("a");

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

				tree->Fill();
				wf->Write();
				currentDataFile.close();
			}
		}
		f.close();
	}

	tree->Write();

	delete tree;
//	for(int i=0; i<numberOfChannels; i++) {
//		delete wf[i];
//	}
//	delete[] wf;
	delete wf;

	rootFile.Close();
	cout << "Done." << endl;

	/////////////////////////////////////
	return 0;
}

int GetChannelNumber(const char* filename)
{

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

