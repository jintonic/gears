// simulation is done by running `gears lead.mac`
// 10,000 gamma-rays at 2614 keV are shot vertically to Pb
{
	gStyle->SetTitleY(0.8);
	gStyle->SetOptFit(111);
	gStyle->SetPadLeftMargin(0.11);
	gStyle->SetTitleOffset(0.9,"y");

	const int n=9; // total number of simulations
	double z[n] = {0, 2, 4, 6, 8, 10, 12, 14, 16}; // thickness of Pb [cm]
	// s = (number of penetrated gamma-rays) / 10,000 * 100
	// number of penetrated gamma rays can be figured out by opening the
	// root file generated with `gears lead.mac` and use the tree in it:
	// t->Draw("k", "trk==1 && vlm==1")
	double s[n] = {100, 54.59, 27.15, 12.57, 5.70, 2.48, 1.18, 0.37, 0.22};
	double dz[n]= {0}; // uncertainty of z
	double ds[n]; // uncertainty of s, assuming Poisson distribution
 	for (int i=0; i<n; i++) ds[i]=sqrt(s[i]*100)/100;

	TGraphErrors g(n, z, s, dz, ds); // graph with error bars
	g.Draw("ap"); // drawing options: a: axes, p: points
	g.SetTitle("Survivability of 2.614 MeV #gamma in Pb" // graph title
		 ";Pb thickness [cm];(# of penetrated)/(# of generated) [%]"); // x,y titles

	TF1 f("f","expo",0,20); // function expo: e^{Constant+Slope*x}
	g.Fit("f"); // fit function, f, to graph, g

	// https://en.wikipedia.org/wiki/Attenuation_length
	cout<<"Attenuation length: "<<-1/f.GetParameter(1)<<" cm"<<endl;
}
