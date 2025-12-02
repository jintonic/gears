{
	gStyle->SetOptStat(0);
	gStyle->SetPadTopMargin(0.01);
	gStyle->SetPadLeftMargin(0.09);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadBottomMargin(0.19);
	gStyle->SetTitleOffset(0.53,"Y");
	gStyle->SetTitleSize(0.09,"XY");
	gStyle->SetLabelSize(0.09,"XY");

	TCanvas* c = new TCanvas("c", "c", 800, 300);

	TChain t("t");
	t.Add("Cherenkov.root");

	TH1F* h = new TH1F("h", ";Cherenkov photon energy [eV]; Entries", 100, 0, 6.5);
	h->SetLineWidth(2);
	t.Draw("k*1000>>h", "stp==0 && pdg==-22");

	c->Print("crkvE.png");
}
