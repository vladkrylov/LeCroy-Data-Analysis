#ifndef SRC_RUN_H_
#define SRC_RUN_H_

#include <vector>

#include "TObject.h"

#include "Waveform.h"

class Run : public TObject {
public:
	Run(unsigned int run_id = 0);
	virtual ~Run();

	void AddWaveform(Waveform *wf);

private:
	unsigned int id;
	vector<Waveform*> waveforms;
};

#endif /* SRC_RUN_H_ */
