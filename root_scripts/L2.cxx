void L2()
{
	/* B scan 4 mm */
//	TString filename_pre = "/run/media/vlad/00789D9D789D91D0/Leetech/RawData/Beamtime2_24-27.02.2015/B_scan_4mm/ROOT_files/Run";
//	char* xbranchName = "magnet_current";
//	char* ybranchName = "amplitude";
//	int startRun = 2;
//	const int N = 15;

	/* B scan 6mm */
//	TString filename_pre = "/run/media/vlad/00789D9D789D91D0/Leetech/RawData/Beamtime2_24-27.02.2015/B_scan_6mm/ROOT_files/Run";
//	char* xbranchName = "magnet_current";
//	char* ybranchName = "amplitude";
//	int startRun = 1;
//	const int N = 15;

	/* Exit1_dX_scan_4mm */
//	TString filename_pre = "/run/media/vlad/00789D9D789D91D0/Leetech/RawData/Beamtime2_24-27.02.2015/Exit1_dX_scan_4mm/ROOT_files/Run";
//	char* xbranchName = "coll_exit1_dX";
//	char* ybranchName = "amplitude";
//	int startRun = 23;
//	const int N = 13;

	/* Exit1_dY_scan_4mm */
	TString filename_pre = "/run/media/vlad/00789D9D789D91D0/Leetech/RawData/Beamtime2_24-27.02.2015/Exit1_dY_scan_4mm/ROOT_files/Run";
	char* xbranchName = "coll_exit1_dY";
	char* ybranchName = "amplitude";
	int startRun = 37;
	const int N = 7;

	TString filename_post = ".root";
	TString filename;

	Double_t currents[N];
	Double_t amps[N];

	for(int i=0; i<N; i++) {
		filename = filename_pre;
		filename += i + startRun;
		filename += filename_post;

		GetPoint(filename.Data(), xbranchName, ybranchName, currents[i], amps[i]);

		cout << currents[i] << "\t";
		cout << amps[i] << endl;
	}
	TGraph *gr = new TGraph(N, currents, amps);
	gr->Draw("AC*");

	gr->SetLineColor(2);
	gr->SetLineWidth(3);
	gr->SetMarkerColor(4);
	gr->SetMarkerSize(1.6);
	gr->SetMarkerStyle(21);
	gr->SetTitle("");

	gr->GetXaxis()->SetTitle("Collimator opening, mm");
//	gr->GetXaxis()->SetLabelSize(0.05);
//	gr->GetXaxis()->SetTitleSize(0.05);
//	gr->GetXaxis()->SetTitleOffset(1.2);

	gr->GetYaxis()->SetTitle("Signal amplitude, a.u.");
//	gr->GetYaxis()->SetLabelSize(0.05);


//	gr->GetXaxis()->SetLimits(0,11.);
//	gr->GetYaxis()->SetRangeUser(0,0.018);
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



