void load() {
	gROOT->ProcessLine(".L lib/Waveform.so");
	new TBrowser;
}

