#ifndef SRC_RUN_H_
#define SRC_RUN_H_

#include <vector>

#include "TObject.h"
#include "TList.h"

#include "Waveform.h"

class Run : public TObject {
public:
	Run(unsigned int run_id = 0);
	virtual ~Run();

	void AddWaveform(Waveform *wf);
	void TestFill(const double t);
	void AddWaveform(const int numberOfChannel);

	void Print(Option_t* option = "") const;

private:
	unsigned int id;
	double testField;
	TList *waveforms;
//	vector<Waveform*> waveforms;

	ClassDef(Run, 1)
};

#endif /* SRC_RUN_H_ */
