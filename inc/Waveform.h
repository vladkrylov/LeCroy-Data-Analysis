#ifndef WAVEFORM_H_
#define WAVEFORM_H_

#include <vector>

#include "TObject.h"
#include "Rtypes.h"

using namespace std;

class Waveform {
public:
	Waveform(int assumedNumberOfPoints = 0);
	Waveform(int assumedNumberOfPoints, const char *fname);
	virtual ~Waveform();

	void Init(int assumedNumberOfPoints);
	void Init(int assumedNumberOfPoints, const char *fname);
	void AddPoint(double x, double y);

private:
	char filename[100];
	vector<double> time;
	vector<double> voltage;

	// this is made to add this class to ROOT
	// see the links below for details:
	//
	// ROOT manual chapter 15 Adding a Class
	// also:
	// http://www.phys.ufl.edu/LIGO/wavelet/root_shared_lib.html
	// https://root.cern.ch/drupal/content/adding-your-class-root-classdef
	// https://root.cern.ch/drupal/content/interacting-shared-libraries-rootcint
	//
	ClassDef(Waveform, 1)

};

#endif /* WAVEFORM_H_ */
