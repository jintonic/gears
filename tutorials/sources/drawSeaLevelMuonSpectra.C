// draw muon spectra at sea level based on eq.(1)
// in http://arxiv.org/abs/nucl-ex/0601019
{
	TCanvas canvas; // create a window for plotting
  canvas.SetRightMargin(0.12);
	canvas.Print("seaLevelMuonSpectra.pdf["); // open an output file

	// define the 2D function of dI/dp with x=p, y=theta
	double pmin=1, pmax=1e5; // p from 1 to 1e5 GeV/c
	double	tmin=0, tmax=M_PI/2; // theta from 0 to pi/2
	TF2 f2d("f2d",
		 	"18/(x*cos(y)+145) * pow(x+2.7/cos(y),-2.7) * (x+5)/(x+5/cos(y))",
		 	pmin, pmax, tmin, tmax);

	f2d.SetTitle("dI(p,#theta)/dp;Momentum p [GeV/c];Zenith angle #theta [rad]");
	f2d.Draw("colz"); // draw 2D function with color
	canvas.Print("seaLevelMuonSpectra.pdf"); // save a plot

	canvas.SetLogz(); canvas.SetLogx(); // enlarge small values
	f2d.Draw("colz"); // redraw 2D function with color
	canvas.Print("seaLevelMuonSpectra.pdf"); // save another plot

	const int n=101; // number of points for plotting
	TGraph gp(n); // dI/dp (p) @ theta = 0 degree
	gp.SetTitle(";Momentum p [GeV/c];dI/dp [1/cm^{2}/s/sr/(GeV/c)]");
	double p, dp=(log10(pmax)-log10(pmin))/n;
	for (int i=0; i<n; i++) {
	 	p = pow(10, log10(pmin)+i*dp);
		gp.AddPoint(p, f2d.Eval(p,0));
	}
	canvas.SetLogy(); canvas.SetGridx(); canvas.SetGridy();
	gp.Draw("al");
	canvas.Print("seaLevelMuonSpectra.pdf"); // save another plot

	TGraph g3(n); // p^3 * dI/dp (p) @ theta = 0 degree
	g3.SetTitle(";Momentum p [GeV/c];p^{3} dI/dp [(GeV/c)^{2}/cm^{2}/s/sr]");
	for (int i=0; i<n; i++) {
	 	p = pow(10, log10(pmin)+i*dp);
		g3.AddPoint(p, p*p*p*f2d.Eval(p,0));
	}
	g3.Draw("al");
	canvas.Print("seaLevelMuonSpectra.pdf"); // save another plot

	TGraph g0(n); // dI/dp (p=0~10 GeV/c) @ theta = 0 degree
	g0.SetTitle(";Momentum p [GeV/c];dI/dp [1/cm^{2}/s/sr/(GeV/c)]");
	pmin=0; pmax=20; dp=(pmax-pmin)/n;
	for (int i=0; i<n; i++) {
	 	p = pmin + i*dp;
		g0.AddPoint(p, f2d.Eval(p,0));
	}
	canvas.SetLogx(0); canvas.SetLogy(0);
	g0.Draw("al");
	canvas.Print("seaLevelMuonSpectra.pdf"); // save another plot

	TGraph g(n); // dI(theta)/dI(0) @ a fixed p
	p=4; // GeV/c
	g.SetTitle(Form("p=%.0f GeV/c;Zenith angle #theta [rad];dI(#theta)/dI(0)",p));
	for (int i=0; i<=90; i++) {
		g.AddPoint(i, f2d.Eval(p,M_PI/2*i/90)/f2d.Eval(p,0));
	}
	g.Draw("al");
	TF1 f("f","cos(x*3.14159265/180)*cos(x*3.14159265/180)",0,90);
	f.SetLineColor(kRed); f.SetLineStyle(kDotted);
	f.Draw("same");

	TLegend leg(0.5,0.7,0.7,0.85);
	leg.AddEntry(&g, "eq. (1)", "l");
	leg.AddEntry(&f, "cos^{2}", "l");
	leg.Draw();

	canvas.Print("seaLevelMuonSpectra.pdf"); // save another plot

	canvas.Print("seaLevelMuonSpectra.pdf]"); // close output file
}
