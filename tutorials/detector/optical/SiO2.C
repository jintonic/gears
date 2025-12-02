// ROOT script to generate SiO2.tg
{
   // refractive index as a function of photon energy [eV]
   // https://refractiveindex.info/?shelf=main&book=SiO2&page=Malitson

   TF1 *fn = new TF1("fn", "sqrt(1"
         "+0.6961663/(1-pow(0.0684043/4.135667662e-15/2.99792458e14*x,2))"
         "+0.4079426/(1-pow(0.1162414/4.135667662e-15/2.99792458e14*x,2))"
         "+0.8974794/(1-pow(9.896161/4.135667662e-15/2.99792458e14*x,2)))", 0.2, 6.0);

   // create graphs to check results
   const int N = 101; // number of data points
   double e[N]; // photon energy [eV]
   double n[N]; // refractive index

   for (int i=0; i<N; i++) {
      e[i]=0.2+(6.0-0.2)/(N-1)*i;
      n[i]=fn->Eval(e[i]);
   }

   gStyle->SetPadTopMargin(0.01);
   gStyle->SetPadRightMargin(0.01);
   gStyle->SetPadLeftMargin(0.1);
   gStyle->SetTitleOffset(1,"Y");
   gStyle->SetTitleX(0.55);
   gStyle->SetTitleY(0.985);
   gStyle->SetTitleW(0.85);

   TGraph *gn = new TGraph(N,e,n);
	 gn->SetTitle("https://refractiveindex.info/?shelf=main&book=SiO2&page=Malitson;"
			 "Optical photon energy [eV]; Refractive index of SiO_{2}");
	 gn->SetLineColor(kBlue);
   gn->Draw("la");

	 TText t0(2.2, 1.39, "Contents of SiO2.tg");
	 t0.SetTextFont(22); t0.Draw();
	 TText t1(0.7, 1.36, ":prop G4_SILICON_DIOXIDE");
	 t1.SetTextFont(8); t1.SetTextSize(25); t1.Draw();
	 TText t2(0.9, 1.33, "photon_energies 101 0.2*eV 0.258*eV ... 6*eV");
	 t2.SetTextFont(8); t2.SetTextSize(25); t2.Draw();
	 TText t3(0.9, 1.30, "Rindex 1.235 1.352 ... 1.542");
	 t3.SetTextFont(8); t3.SetTextSize(25); t3.Draw();
	 TLine l1(0.6, 1.38, 6.1, 1.38); l1.Draw();
	 TLine l2(0.6, 1.29, 6.1, 1.29); l2.Draw();

	 gPad->Print("nSiO2.png");

   // generate SiO2.tg
   ofstream tg("SiO2.tg");
   tg.precision(4);
   tg<<":prop G4_SILICON_DIOXIDE"<<endl;
   tg<<"  photon_energies "<<N;
   for (int i=0; i<N; i++) tg<<" "<<e[i]<<"*eV"; tg<<endl;
   tg<<"  RINDEX";
   for (int i=0; i<N; i++) tg<<" "<<n[i]; tg<<endl;
   tg.close();
}
// -*- c++ -*-
// vim: set ft=cpp:
