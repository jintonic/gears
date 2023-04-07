{ // https://root.cern.ch/doc/master/classTStyle.html
	// margins
	gStyle->SetPadRightMargin(0.02);
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadTopMargin(0.02);
	gStyle->SetPadBottomMargin(0.11);

	// axes
	gStyle->SetLabelFont(22,"xyz");
	gStyle->SetTitleFont(22,"xyz");
	gStyle->SetLabelSize(0.05,"xyz");
	gStyle->SetTitleSize(0.05,"xyz");

	// title
	gStyle->SetTitleY(0.95);
	gStyle->SetTitleFont(22,"h");
	gStyle->SetTitleSize(0.05,"h");

	// statistic box
	gStyle->SetOptStat(111110);
	gStyle->SetStatX(0.98);
	gStyle->SetStatY(0.98);
	gStyle->SetStatW(0.25);
	gStyle->SetStatFont(22);
	gStyle->SetStatFontSize(0.05);

	// legend
	gStyle->SetLegendBorderSize(1);
	gStyle->SetLegendFont(22);
}
