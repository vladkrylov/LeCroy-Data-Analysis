#include "Waveform.h"

#include <algorithm>

ClassImp(Waveform)

Waveform::Waveform(int assumedNumberOfPoints) {
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

