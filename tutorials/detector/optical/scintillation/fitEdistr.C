{
	gStyle->SetOptFit(1);
	gStyle->SetStatW(0.20);
	gStyle->SetOptStat(10);
	gStyle->SetPadTopMargin(0.01);
	gStyle->SetPadLeftMargin(0.11);
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetTitleOffset(1.2,"Y");
	TCanvas* c = new TCanvas;

	TChain t("t");
	t.Add("scintillation.root");

	TH1F* h = new TH1F("h", ";Scintillation photon energy [eV]; Entries", 100, 2.7, 4.7);
	t.Draw("k*1000>>h", "stp==0 && pdg==-22");

	TF1* f0 = new TF1("f0", "gausn(0)+gausn(3)", 2.5, 5);
	TF1* f1 = new TF1("f1", "gausn", 2.5, 5);
	TF1* f2 = new TF1("f2", "gausn", 2.5, 5);
	f0->SetLineColor(kRed);
	f0->SetLineWidth(1);
	f0->SetParameters(1e4,3.67,0.2, 200,4.3,0.1);
	f0->SetParNames("norm1", "mean1", "sigma1", "norm2", "mean2", "sigma2");
	h->Fit(f0);

	f1->SetParameters(f0->GetParameter(0), f0->GetParameter(1), f0->GetParameter(2)); 
	f2->SetParameters(f0->GetParameter(3), f0->GetParameter(4), f0->GetParameter(5)); 

	f1->SetLineWidth(1);
	f2->SetLineWidth(1);
	f1->SetLineColor(kBlue);
	f2->SetLineColor(kMagenta);

	f1->Draw("same");
	f2->Draw("same");

	TLegend l(0.15, 0.7, 0.4, 0.9);
	l.AddEntry(f0, "Total", "l");
	l.AddEntry(f1, "Component 1", "l");
	l.AddEntry(f2, "Component 2", "l");
	l.Draw();

	c->Print("Ephotons.png");
}
