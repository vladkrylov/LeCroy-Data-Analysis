#include "Run.h"

#include <iostream>

ClassImp(Run)

Run::Run(unsigned int run_id) : TObject()
{
	id = run_id;
	testField = 0;
	waveforms = new TList();
}

Run::~Run() {
	waveforms->Delete();
	delete waveforms;
}

void Run::AddWaveform(Waveform *wf)
{
	waveforms->Add(wf);
}

void Run::TestFill(const double t)
{
	testField = t;
}

void Run::Print(Option_t* option) const
{
	cout << "testField = " << testField << endl;
}

void Run::AddWaveform(const int numberOfChannel)
{

}
