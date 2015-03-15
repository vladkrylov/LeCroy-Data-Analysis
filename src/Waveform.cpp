#include "Waveform.h"

#include <algorithm>
#include <iostream>

#include "TGraph.h"
#include "TVirtualPad.h"
#include "TPad.h"

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

	amplitude = 0.;
	gr = new TGraph();
	gr_processed = new TGraph();
}

void Waveform::Init(int assumedNumberOfPoints, const char *fname) {
	Init(assumedNumberOfPoints);
	strcpy(filename, fname);
}

Waveform::~Waveform() {
	// TODO Auto-generated destructor stub
	delete gr;
	delete gr_processed;
}

void Waveform::AddPoint(double x, double y)
{
	time.push_back(x);
	voltage.push_back(y);
}

void Waveform::CalculateParameters()
{
	RemoveTimeOffset();
	CalculateAmplitude();
	Process();
}

void Waveform::Browse(TBrowser* b)
{
	TVirtualPad *p;
	p = gPad;
	gPad->cd(0);
	gPad->Clear();
	gPad->Divide(1,2);
	gPad->cd(1);
	size_t N = time.size();

	if (N != voltage.size()) {
		cout << "Cannot draw the waveform. Time and amplitudes vectors have different size." << endl;
	} else {
		gr->Set(N);
		for(size_t i=0; i<N; i++) {
			gr->SetPoint(i, time.at(i), voltage.at(i));
		}
		gr->Draw("AL");
		gr->SetTitle("Measured signal");
	}

	/*
	 * ------------------------------------------------------------------------------
	 */
	p->cd(2);
	if (N != processed_voltage.size()) {
		cout << "Cannot draw the waveform. Time and processed amplitudes vectors have different size." << endl;
		cout << time.size() << " != " << processed_voltage.size() << endl;
	} else {
		for(size_t i=0; i<N; i++) {
			gr_processed->SetPoint(i, time.at(i), processed_voltage.at(i)/2);
		}
		gr_processed->Draw("AL");
		gr_processed->SetTitle("Processed signal");
	}
	gPad = p;
}

void Waveform::RemoveTimeOffset()
{
	double o = time.at(0);
	if (!time.empty()) {
		for(size_t i=0; i<time.size(); i++) {
			time.at(i) -= o;
		}
	}
}

double Waveform::GetAmplitude() const
{
	return amplitude;
}

void Waveform::CalculateAmplitude()
{
	if (polarity > 0) {
		amplitude = *max_element(voltage.begin(), voltage.end());
	} else {
		amplitude = *min_element(voltage.begin(), voltage.end());
	}
}

void Waveform::Process()
{
	processed_voltage = voltage;
}


