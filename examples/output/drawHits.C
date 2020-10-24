// Draw combined hits in a simulated event
void drawHits(int evt=16, const char *intput="hits.root")
{
	TChain *h = new TChain("h");
	h->Add(intput);

	gStyle->SetPadTopMargin(0.02);
	gStyle->SetPadRightMargin(0.025);
	TCanvas *c = new TCanvas("c","c",500,500);

	// draw all hits to show the detector cross section
	h->SetMarkerColor(30);
	h->SetMarkerStyle(kDot);
	h->Draw("y:x");
	((TH2F*) gPad->GetPrimitive("htemp"))->SetTitle(";x [mm];y [mm]");

	// draw combined hits in an event
	h->SetMarkerColor(kRed);
	h->SetMarkerStyle(kFullDotLarge);
	h->Draw("y:x","","samelp",1,evt);

	TText *txt1 = new TText(-20,-16,"Combined hits");
	txt1->SetTextColor(kRed);
	txt1->Draw();
	TText *txt2 = new TText(-20,36,"Detector cross section");
	txt2->SetTextColor(30);
	txt2->Draw();

	c->Print("combinedHits.png");
}
