// ROOT script to combine nearby Geant4 step points to hits in a detector
// based on the space resolution of the detector
void combineStepPointsToHits(
		const char *input="gears.root",
		const char *output="hits.root",
		double resolution=1/*mm*/)
{
	// input, which is GEARS output
	TChain *t = new TChain("t");
	t->Add(input);
	int nStepPoints; // number of Geant4 step points
	t->SetBranchAddress("n",&nStepPoints);
	// parameters of step points
	vector<double> *xx=0, *yy=0, *zz=0, *de=0;
	vector<int> *vlm=0; // copy number of a Geant4 volume
	TBranch *bx, *by, *bz, *be, *bv;
	t->SetBranchAddress("xx",&xx, &bx); // local x
	t->SetBranchAddress("yy",&yy, &by); // local y
	t->SetBranchAddress("zz",&zz, &bz); // local z
	t->SetBranchAddress("de",&de, &be); // energy deposition
	t->SetBranchAddress("vlm",&vlm, &bv);

	// output, which contains a tree filled with combined hits
	TFile *file = new TFile(output, "recreate");
	TTree *tree = new TTree("h","combined hits");
	int n; // number of combined hits
	int evt; // id of event from Geant4 simulation
	tree->Branch("n",  &n,  "n/I");
	tree->Branch("evt",&evt,"evt/I");
	// parameters of combined hits
	double x[1000], y[1000], z[1000], e[1000];
	tree->Branch("x",x,"x[n]/D");
	tree->Branch("y",y,"y[n]/D");
	tree->Branch("z",z,"z[n]/D");
	tree->Branch("e",e,"e[n]/D");

	// main loop to combine step points
	double dx=0, dy=0, dz=0, dr=0; // distances between step points
	int nevt = t->GetEntries(); // total number of events simulated
	cout<<nevt<<" events to be processed"<<endl;
	for (evt=0; evt<nevt; evt++) {
		if (evt%10000==0) cout<<evt<<" events processed"<<endl;
		t->GetEntry(evt); // get information of step points from input tree

		n = 0; // reset counter of combined hits for a new event
		for (int i=0; i<nStepPoints; i++) { // loop over step points
			if (de->at(i)==0) continue; // skip step points with no energy deposition
			if (vlm->at(i)!=1) continue; // skip step points not in the detector
			if (n==0) {// no combined hit yet, create the 1st one
				x[n]=xx->at(i); y[n]=yy->at(i); z[n]=zz->at(i); e[n]=de->at(i);
				n++; // increase the hit index by 1
				continue;
			}
			// distance between this step point and the previously combined hit
			dx=xx->at(i)-x[n-1]; dy=yy->at(i)-y[n-1]; dz=zz->at(i)-z[n-1];
			dr=sqrt(dx*dx+dy*dy+dz*dz);
			if (dr>resolution) { // create a new hit far away from the previous one
				x[n]=xx->at(i); y[n]=yy->at(i); z[n]=zz->at(i); e[n]=de->at(i);
				n++;
			} else { // combine a nearby step point with the previously combined hit
				// get energy weighted position
				x[n-1]=(x[n-1]*e[n-1]+xx->at(i)*de->at(i))/(e[n-1]+de->at(i));
				y[n-1]=(y[n-1]*e[n-1]+yy->at(i)*de->at(i))/(e[n-1]+de->at(i));
				z[n-1]=(z[n-1]*e[n-1]+zz->at(i)*de->at(i))/(e[n-1]+de->at(i));
				e[n-1]+=de->at(i); // deposited energies need to be summed
			}
		}
		if (n>0) tree->Fill(); // insert x,y,z,e values to the output tree
	}

	// save the output tree
	tree->Write("", TObject::kWriteDelete); // write tree, then delete previous
	file->Close(); // close output file
}
