{
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);
	gStyle->SetPadTopMargin(0.01);
	gStyle->SetPadLeftMargin(0.11);
	gStyle->SetPadRightMargin(0.01);
	TCanvas* c = new TCanvas;
	c->SetLogy();

	TChain t("t");
	t.Add("absorption.root");

	TH1F* h = new TH1F("h", ";Penetration depth [m]; Entries", 100, -3.5, 0);
	t.Draw("z/1000>>h", "pdg==-22 && pro==3031");

	h->Fit("expo");
	TF1* f = h->GetFunction("expo");
	f->SetLineColor(kRed);
	f->SetLineWidth(1);

	TLatex l1, l2;
	l1.SetTextFont(22); l1.SetTextSize(0.06); l1.SetTextColor(kRed);
	l2.SetTextFont(22); l2.SetTextSize(0.06);
	l1.DrawLatex(-1.5, 10, "f(z)=A e^{z/#tau}");
	l2.DrawLatex(-1.5, 2, Form("#tau = (%.1f #pm 0.4) cm", 100/f->GetParameter(1)));

	TPad *l = new TPad("l","l",0.02,0.17,0.96,1);
	l->SetFillColorAlpha(kWhite, 0);
	l->Draw(); l->cd();
	TImage *p = TImage::Open("absorption.png");
	p->Draw();

	c->Print("depth.png");
}
