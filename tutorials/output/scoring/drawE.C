{
	TGraph *ge = new TGraph("electron.csv", "%lg,%*lg,%*lg,%lg");
	ge->Draw("ac");
	ge->SetLineColor(kRed);
	ge->SetTitle(";X_{0}; Energy [keV]");

	TGraph *gg = new TGraph("gamma.csv", "%lg,%*lg,%*lg,%lg");
	gg->Draw("c");
	gg->SetLineColor(kBlue);

	TLegend *l = new TLegend(0.5, 0.6, 0.8, 0.8);
	l->AddEntry(ge,"e^{-}","l");
	l->AddEntry(gg,"#gamma","l");
	l->Draw();
}
