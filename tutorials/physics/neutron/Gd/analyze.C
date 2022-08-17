// check multiplicity & spectrum of gamma-rays from nat-Gd(n,gamma)
{
	// input
	TChain *t = new TChain("t");
	t->Add("output.root"); // output from `gears thermal.mac`
	int n; // number of step points
	t->SetBranchAddress("n",&n);
	vector<int> *pid=0, *pdg=0, *pro=0; vector<double> *k=0;
	t->SetBranchAddress("pid", &pid); // parent id
	t->SetBranchAddress("pdg", &pdg); // PDG encoding
	t->SetBranchAddress("pro", &pro); // process id
	t->SetBranchAddress("k", &k); // kinetic energy

	// output
	TFile *output = new TFile("results.root","recreate");
	int ng = 0; // number of gamma-rays (multiplicity)
  TH1I *hNg = new TH1I("hNg",";N_{#gamma};Entries",20,0,20);
	double et; // total energy carried by all gamma-rays
  TH1D *hEt = new TH1D("hEt",";E_{total} [MeV];Entries",100,0,10);
  TH1D *hEg = new TH1D("hEg",";E_{#gamma} [MeV];Entries",100,0,10);

	for (int i=0; i<t->GetEntries(); i++) { // event loop
		t->GetEntry(i);
		ng=0; et=0;
		for (int j=0; j<n; j++) // loop over step points
			if (pid->at(j)==1 && pdg->at(j)==22 && pro->at(j)==4131) {
				ng++; et+=k->at(j)/1000.; hEg->Fill(k->at(j)/1000.);
			}
		hNg->Fill(ng);
		hEt->Fill(et);
	}
	output->Write();
	output->Close();
}
