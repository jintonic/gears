// ROOT script to generate SiO2.tg
{
   // refractive index as a function of photon energy [eV]
   // https://refractiveindex.info/?shelf=main&book=SiO2&page=Malitson

   TF1 *fn = new TF1("fn", "sqrt(1"
         "+0.6961663/(1-pow(0.0684043/4.135667662e-15/2.99792458e14*x,2))"
         "+0.4079426/(1-pow(0.1162414/4.135667662e-15/2.99792458e14*x,2))"
         "+0.8974794/(1-pow(9.896161/4.135667662e-15/2.99792458e14*x,2)))", 0.2, 6.0);

   // create graphs to check results
   int N = 100; // number of data points
   double e[N]; // photon energy [eV]
   double n[N]; // refractive index

   for (int i=0; i<N; i++) {
      e[i]=0.2+(6.0-0.2)/N*i;
      n[i]=fn->Eval(e[i]);
   }

   TGraph *gn = new TGraph(N,e,n);

   gn->Draw("pa");

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
