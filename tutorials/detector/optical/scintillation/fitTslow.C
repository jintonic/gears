{
	gStyle->SetOptFit(0);
	gStyle->SetStatW(0.25);
	gStyle->SetOptStat(1110);
	gStyle->SetPadTopMargin(0.01);
	gStyle->SetPadLeftMargin(0.09);
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetTitleOffset(0.9,"Y");
	TCanvas* c = new TCanvas;

	TChain t("t");
	t.Add("scintillation.root");

	TH1F* h = new TH1F("h", ";Scintillation photon generation time [ns]; Entries", 100, 0, 1.5e4);
	t.Draw("t>>h", "stp==0 && pdg==-22");

	h->Fit("expo", "", "", 100, 1.3e4);
	TF1* f = h->GetFunction("expo");
	f->SetLineColor(kRed);
	f->SetLineWidth(1);

	TLatex l1, l2;
	l1.SetTextFont(22); l1.SetTextSize(0.06); l1.SetTextColor(kRed);
	l2.SetTextFont(22); l2.SetTextSize(0.06);
	l1.DrawLatex(2000, 10, "f(t)=A e^{-t/#tau}");
	l2.DrawLatex(2000, 2, Form("#tau = (%.0f #pm 1) ns", -1/f->GetParameter(1)));

	c->SetLogy();
	c->Print("Tslow.png");
}
