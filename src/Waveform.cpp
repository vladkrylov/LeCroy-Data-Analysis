#include "Waveform.h"

#include <algorithm>
#include <iostream>

#include "TGraph.h"
#include "TVirtualPad.h"

ClassImp(Waveform)

Waveform::Waveform(int assumedNumberOfPoints) : TObject() {
	Init(assumedNumberOfPoints);
}

Waveform::Waveform(int assumedNumberOfPoints, const char *fname) {
	Init(assumedNumberOfPoints);
	strcpy(filename, fname);
}

void Waveform::Init(int assumedNumberOfPoints) {
	time.clear();
	voltage.clear();

	time.reserve(assumedNumberOfPoints);
	voltage.reserve(assumedNumberOfPoints);

	amplitude = 0.;
}

void Waveform::Init(int assumedNumberOfPoints, const char *fname) {
	Init(assumedNumberOfPoints);
	strcpy(filename, fname);
}

Waveform::~Waveform() {
	// TODO Auto-generated destructor stub
}

void Waveform::AddPoint(double x, double y)
{
	time.push_back(x);
	voltage.push_back(y);
}

void Waveform::CalculateParameters()
{
	amplitude = *max_element(voltage.begin(), voltage.end());
}

void Waveform::Browse(TBrowser* b)
{
//	size_t length = time.size();
//	if (length != voltage.size()) {
//		cout << "Cannot draw the waveform. Time and amplitudes vectors have different size." << endl;
//		return;
//	}
//	TGraph *gr = new TGraph(length);
//	for(size_t i=0; i<length; i++) {
//		gr->SetPoint(i, time.at(i), voltage.at(i));
//	}
//	gr->Draw();
//	gPad->Update();
	cout << "bingo" << endl;
}
