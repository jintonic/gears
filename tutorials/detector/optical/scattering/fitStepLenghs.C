{
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(1110);
	gStyle->SetStatX(0.965);
	gStyle->SetStatW(0.2);
	gStyle->SetPadTopMargin(0.01);
	gStyle->SetPadLeftMargin(0.11);
	gStyle->SetPadRightMargin(0.035);
	gStyle->SetTitleOffset(1.2,"Y");
	TCanvas* c = new TCanvas;

	TChain t("t");
	t.Add("scattering.root");

	TH1F* h = new TH1F("h", ";Step length [cm]; Entries", 100, 0, 3500);
	t.Draw("l>>h", "stp==1 && pro==3033");

	h->Fit("expo");
	TF1* f = h->GetFunction("expo");
	f->SetLineColor(kRed);
	f->SetLineWidth(1);

	TLatex l1, l2;
	l1.SetTextFont(22); l1.SetTextSize(0.06); l1.SetTextColor(kRed);
	l2.SetTextFont(22); l2.SetTextSize(0.06);
	l1.DrawLatex(680, 1800, "f(z)=A e^{-z/#tau}");
	l2.DrawLatex(800, 1000, Form("#tau = (%.0f #pm 1) cm", -1/f->GetParameter(1)));

	TPad *l = new TPad("l","l",0.08,0,1,1);
	l->SetFillColorAlpha(kWhite, 0);
	l->Draw(); l->cd();
	TImage *p = TImage::Open("Rayleigh.png");
	p->Draw();

	c->Print("scattering.png");
}
