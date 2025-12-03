{
	gStyle->SetOptFit(1);
	gStyle->SetStatW(0.25);
	gStyle->SetOptStat(1110);
	gStyle->SetPadTopMargin(0.01);
	gStyle->SetPadLeftMargin(0.09);
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetTitleOffset(0.9,"Y");
	TCanvas* c = new TCanvas;

	TChain t("t");
	t.Add("scintillation.root");

	TH1F* h = new TH1F("h", ";Number of scintillation photons; Entries", 100, 0, 310);
	t.Draw("(n-5)/2>>h");

	TF1* f0 = new TF1("f0", "gausn", 0, 310);
	f0->SetLineColor(kRed);
	f0->SetLineWidth(1);
	f0->SetParNames("norm", "mean", "sigma");
	h->Fit(f0);

	c->Print("Nphotons.png");
}
