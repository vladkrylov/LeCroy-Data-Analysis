void L2()
{
	TString filename_pre = "/home/vlad/Program_Files/Eclipse/g45work/LeetechDataAnalysis/test_data/ROOT_files/Run";
	TString filename_post = ".root";
	TString filename;
	char* branchName = "amplitude";

	const int N = 19;
	double currents[N] = {7.5, 7.2, 7.0, 6.8, 6.6, 6.4, 6.2, 6.0, 5.8, 5.6, 5.4, 5.2, 5.0, 4.8, 4.6, 4.4, 4.2, 4.0, 3.8};
	double amps[N];

	for(int i=1; i<N; i++) {
		filename = filename_pre;
		filename += i+1;
		filename += filename_post;

		amps[i] = -GetMean(filename.Data(), branchName);

		cout << currents[i] << "\t";
		cout << amps[i] << endl;
	}
	TGraph *gr = new TGraph(N, currents, amps);
	gr->Draw("ALP");
}

double GetMean(const char* fileName, const char* branchName)
{
	TFile *f = new TFile(fileName);
	TTree *t1 = (TTree*)f->Get("T");
	Double_t y;
	TH1F *h = new TH1F("test", "test", 200, -10, 10);
	t1->SetBranchAddress(branchName, &y);
	for (int i=0; i<t1->GetEntries(); i++) {
		t1->GetEntry(i);
		h->Fill(y);
	}
	double res = h->GetMean();
	return res;
}
