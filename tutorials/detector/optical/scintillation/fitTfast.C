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

	TH1F* h = new TH1F("h", ";Scintillation photon generation time [ns]; Entries", 100, 0, 50);
	t.Draw("t>>h", "stp==0 && pdg==-22 && t<50");

	TF1* f0 = new TF1("f0", "expo(0)+expo(2)", 0, 50);
	TF1* f1 = new TF1("f1", "expo", 0, 50);
	TF1* f2 = new TF1("f2", "expo", 0, 50);
	f0->SetLineColor(kRed);
	f0->SetLineWidth(1);
	f0->SetParameters(7,-0.2,11,-0.001);
	f0->SetParNames("norm1", "tau1", "norm2", "tau2");
	h->Fit(f0);

	f1->SetParameters(f0->GetParameter(0), f0->GetParameter(1)); 
	f2->SetParameters(f0->GetParameter(2), f0->GetParameter(3)); 

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

	TLatex l1, l2;
	l1.SetTextFont(22); l1.SetTextSize(0.06); l1.SetTextColor(kRed);
	l2.SetTextFont(22); l2.SetTextSize(0.06);
	l1.DrawLatex(2000, 10, "f(t)=A e^{-t/#tau}");
	l2.DrawLatex(2000, 2, Form("#tau = (%.0f #pm 1) ns", -1/f0->GetParameter(1)));

	c->SetLogy();
	c->Print("Tslow.png");
}
