// ROOT script to generate CsI.tg
{
   // refractive index as a function of photon energy [eV]
   // https://refractiveindex.info/?shelf=main&book=CsI&page=Li
   TF1 *fn = new TF1("fn", "sqrt(1"
         "+0.27587+0.68689/(1-pow(0.130/4.135667662e-15/2.99792458e14*x,2))"
         "+0.26090/(1-pow(0.147/4.135667662e-15/2.99792458e14*x,2))"
         "+0.06256/(1-pow(0.163/4.135667662e-15/2.99792458e14*x,2))"
         "+0.06527/(1-pow(0.177/4.135667662e-15/2.99792458e14*x,2))"
         "+0.14991/(1-pow(0.185/4.135667662e-15/2.99792458e14*x,2))"
         "+0.51818/(1-pow(0.206/4.135667662e-15/2.99792458e14*x,2))"
         "+0.01918/(1-pow(0.218/4.135667662e-15/2.99792458e14*x,2))"
         "+3.38229/(1-pow(161.29/4.135667662e-15/2.99792458e14*x,2)))", 0.0, 4.96);

   // intensity of 3.7 eV band, tau = 1*us [Nishimura95]
   TF1 *fslow = new TF1("fslow", "gaus", 0.0185, 4.96);
   fslow->SetParameters(2.5,3.67,0.2);

   // intensity of 4.2 eV band, tau = 2*ns [Nishimura95]
   TF1 *ffast = new TF1("ffast", "gaus", 0.0185, 4.96);
   ffast->SetParameters(2.5,4.3,0.1);

   // create graphs to check results
   int N = 100; // number of data points
   double e[N]; // photon energy [eV]
   double n[N]; // refractive index
   double slow[N]; // intensity of 3.7 eV band
   double fast[N]; // intensity of 4.e eV band

   for (int i=0; i<N; i++) {
      e[i]=2.5+(5.0-2.5)/N*i;
      n[i]=fn->Eval(e[i]);
      slow[i]=fslow->Eval(e[i]);
      fast[i]=ffast->Eval(e[i]);
      if (slow[i]<1e-5) slow[i]=0;
      if (fast[i]<1e-5) fast[i]=0;
   }

   TGraph *gn = new TGraph(N,e,n);
   TGraph *gs = new TGraph(N,e,slow);
   TGraph *gf = new TGraph(N,e,fast);
   
   gs->SetMarkerColor(kRed);
   gf->SetMarkerColor(kBlue);
   gs->Draw("pa");
   gf->Draw("p");
   gn->Draw("p");
   
   // generate CsI.tg
   ofstream tg("CsI.tg");
   tg.precision(4);
   tg<<":prop G4_CESIUM_IODIDE"<<endl;
   tg<<"  SCINTILLATIONYIELD 100./keV"<<endl;
   tg<<"  RESOLUTIONSCALE 2."<<endl;
   tg<<"  FASTTIMECONSTANT 2*ns"<<endl;
   tg<<"  SLOWTIMECONSTANT 1*us"<<endl;
   tg<<"  YIELDRATIO 0.05"<<endl;
   tg<<"  photon_energies "<<N;
   for (int i=0; i<N; i++) tg<<" "<<e[i]<<"*eV"; tg<<endl;
   tg<<"  FASTCOMPONENT";
   for (int i=0; i<N; i++) tg<<" "<<fast[i]; tg<<endl;
   tg<<"  SLOWCOMPONENT";
   for (int i=0; i<N; i++) tg<<" "<<slow[i]; tg<<endl;
   tg<<"  RINDEX";
   for (int i=0; i<N; i++) tg<<" "<<n[i]; tg<<endl;
   tg.close();
}
// -*- c++ -*-
// vim: set ft=cpp:
