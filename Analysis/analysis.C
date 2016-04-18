{
  char Title[60];
  char Title2[60];
  int total = 30;
  Int_t n_particles;
  double weight;
  vector<int> *PID = new vector<int>;
  vector<double> *P_X = new vector<double>;
  vector<double> *P_Y = new vector<double>;; 
  vector<double> *P_Z = new vector<double>;;
  vector<double> *E = new vector<double>;;
  vector<double> *M = new vector<double>;;

  TFile *f = new TFile("newdensity.root");
  TTree *Physics = (TTree*)f->Get("Physics");

  Physics->SetBranchAddress("n_particles",&n_particles);
  Physics->SetBranchAddress("weight",&weight);
  Physics->SetBranchAddress("PID",&PID);
  Physics->SetBranchAddress("P_X",&P_X);
  Physics->SetBranchAddress("P_Y",&P_Y);
  Physics->SetBranchAddress("P_Z",&P_Z);
  Physics->SetBranchAddress("E",&E);
  Physics->SetBranchAddress("M",&M);

  TH1F *N_proton = new TH1F("N_proton","Number of protons produced; N",10,0,10);
  TH1F *E_e = new TH1F("E_e","Number of protons produced; N",100,0,4);
  TH1F *MissMass[100];
  for (int i=0; i<100; i++) {
    sprintf(Title,"MissMass%i",i);
    sprintf(Title2,"Missing Mass for %i p knockout;M(GeV)",i);
    MissMass[i] = new TH1F(Title,Title2,100,187.,197.); 
  }
  int n_p;
  TLorentzVector v4_p;
  TLorentzVector v4;
  TLorentzVector v4_beam(0.,0.,5.,pow((pow(0.000511,2)+pow(5.,2)),0.5)); // It is probably missing the 4-momentum of the Lead nucleus at rest.
  TLorentzVector v4_tg(0.,0.,0.,193.728); // Target = Lead208 at rest
  TLorentzVector v4_e;
  TLorentzVector v4_t;
  Int_t n_entries = (Int_t)Physics->GetEntries();

  for (Int_t i=0; i<n_entries; i++) {
    //    cout << i << endl;
    Physics->GetEntry(i);
    n_p = 0;
    v4_p.SetPxPyPzE(0.,0.,0.,0.);
    for (int j=0 ; j<n_particles-1; j++) { // last one by construction is the scattered electron
      if (PID->at(j)==2212) {
	v4.SetPxPyPzE(P_X->at(j),P_Y->at(j),P_Z->at(j),E->at(j));
	if (E->at(j) < 0.938) {
	  cout << E->at(j) << endl;
	}
	v4_p = v4_p + v4;
	n_p++;
      }
    }      
    if (n_p >= 0) {
      v4_e.SetPxPyPzE(P_X->at(n_particles - 1),P_Y->at(n_particles - 1),P_Z->at(n_particles - 1),E->at(n_particles - 1)); // the electron id the last one in the array
      v4_t = v4_beam + v4_tg - v4_e - v4_p;
	//Fill the histogram with the weight (V4_t.M2(),weight)
    }
    E_e->Fill(E->at(n_particles - 1));
      //      cout << (pow(E->at(n_particles - 1),2) - pow(P_X->at(n_particles - 1),2) -  pow(P_Y->at(n_particles - 1),2) -  pow(P_Z->at(n_particles - 1),2) ) << endl;
    //   cout << n_p << endl;  

    N_proton->Fill(float(n_p)+0.1); // Adding 0.1 in order to avoid problems in translating it to float
    MissMass[n_p]->Fill(v4_t.M(),weight);
    //    cout << i << " " << n_particles << " " << PID->at(n_particles - 1) << endl;
  }



}
