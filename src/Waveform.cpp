#include "Waveform.h"

#include <algorithm>
#include <iostream>

#include "TGraph.h"
#include "TVirtualPad.h"

ClassImp(Waveform)

Waveform::Waveform(int assumedNumberOfPoints) : TObject() {
	Init(assumedNumberOfPoints);
	polarity = +1;
}

Waveform::Waveform(int assumedNumberOfPoints, int pol) {
	Init(assumedNumberOfPoints);
	polarity = pol;
}

void Waveform::Init(int assumedNumberOfPoints) {
	time.clear();
	voltage.clear();

	time.reserve(assumedNumberOfPoints);
	voltage.reserve(assumedNumberOfPoints);
	time.push_back(0.); // this is done to carefully substract time[0] from all others time points

	amplitude = 0.;
	gr = new TGraph();
}

void Waveform::Init(int assumedNumberOfPoints, const char *fname) {
	Init(assumedNumberOfPoints);
	strcpy(filename, fname);
}

Waveform::~Waveform() {
	// TODO Auto-generated destructor stub
	delete gr;
}

void Waveform::AddPoint(double x, double y)
{
	time.push_back(x - time.at(0));
	voltage.push_back(y);
}

void Waveform::CalculateParameters()
{
	amplitude = *max_element(voltage.begin(), voltage.end());
}

void Waveform::Browse(TBrowser* b)
{
	size_t N = time.size();

	if (N != voltage.size()) {
		cout << "Cannot draw the waveform. Time and amplitudes vectors have different size." << endl;
		return;
	}

	gr->Set(N);
	for(size_t i=0; i<N; i++) {
		gr->SetPoint(i, time[i], voltage[i]);
	}
	gr->Draw("AL");
//	cout << "bingo" << endl;
}

