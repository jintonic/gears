{
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);
	gStyle->SetPadTopMargin(0.01);
	gStyle->SetPadLeftMargin(0.09);
	gStyle->SetPadRightMargin(0.02);
	gStyle->SetTitleOffset(0.9,"Y");
	TCanvas* c = new TCanvas;

	TChain t("t");
	t.Add("scintillation.root");

	TH1F* h = new TH1F("h", ";Scintillation photon generation time [ns]; Entries", 100, 0, 45);
	t.Draw("t>>h", "stp==0 && pdg==-22 && t<45");

	TF1* f0 = new TF1("f0", "expo(0)+expo(2)", 0, 45);
	TF1* f1 = new TF1("f1", "expo", 0, 45);
	TF1* f2 = new TF1("f2", "expo", 0, 45);
	f0->SetLineColor(kRed);
	f0->SetLineWidth(1);
	f0->SetParameters(7,-0.2,11,-0.001);
	f0->FixParameter(3, -0.001);
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

	TLegend l(0.5, 0.5, 0.95, 0.9);
	l.AddEntry(f0, "Total", "l");
	l.AddEntry(f1, Form("#tau_{fast} = (%.2f #pm 0.05) ns", -1/f0->GetParameter(1)), "l");
	l.AddEntry(f2, "#tau_{slow} = 1000 ns", "l");
	l.Draw();

	TLatex l1;
	l1.SetTextFont(22); l1.SetTextSize(0.06); l1.SetTextColor(kRed);
	l1.DrawLatex(10, 300, "f(t)=N_{1} e^{-t/#tau_{fast}} + N_{2} e^{-t/#tau_{slow}}");

	c->SetLogy();
	c->Print("Tfast.png");
}
