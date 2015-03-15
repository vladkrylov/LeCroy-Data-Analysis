void L2()
{
	TString filename_pre = "/home/vlad/Program_Files/Eclipse/g45work/LeetechDataAnalysis/test_data/ROOT_files/Run";
	TString filename_post = ".root";
	TString filename;
	char* xbranchName = "magnet_current";
	char* ybranchName = "amplitude";

	const int N = 18;
	Double_t currents[N];
	Double_t amps[N];

	for(int i=0; i<N; i++) {
		filename = filename_pre;
		filename += i+2;
		filename += filename_post;

		GetPoint(filename.Data(), xbranchName, ybranchName, currents[i], amps[i]);

		cout << currents[i] << "\t";
		cout << amps[i] << endl;
	}
	TGraph *gr = new TGraph(N, currents, amps);
	gr->Draw("ALP");
}

void GetPoint(const char* fileName, const char* xbranchName, const char* ybranchName, Double_t &x, Double_t &y)
{
	TFile *f = new TFile(fileName);
	TTree *t1 = (TTree*)f->Get("T");
	Double_t ty;
	TH1F *h = new TH1F("test", "test", 200, -10, 10);
	t1->SetBranchAddress(ybranchName, &ty);
	for (int i=0; i<t1->GetEntries(); i++) {
		t1->GetEntry(i);
		h->Fill(ty);
	}
	y = h->GetMean();

	// get the current through the magnet and polarity
	Float_t tmpx, tmpp;
	TTree *t2 = (TTree*)f->Get("Info");

	t2->SetBranchAddress("polarity", &tmpp);
	t2->SetBranchAddress(xbranchName, &tmpx);

	t2->GetEntry(0);
	x = tmpx;
	if (tmpp < 0) {
		y = -y;
	}

}



