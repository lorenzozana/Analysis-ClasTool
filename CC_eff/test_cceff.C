{
  gStyle->SetOptFit(1);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gROOT->SetStyle("BABAR");
  gSystem->Load("/net/home/lzana/Eg2/Code/Clas_5.20/Analisi_samebin/Tools_cc_C.so");



  char Title[60];
  TH2F *Hist[7][50];

  Double_t sfitpar[7][100][100][6];
  Double_t fitpar[7][100][100][7];
  Double_t theta[7][100][100];
  Int_t Num[7][100];

  //  TH1D *Slice[4100];

  char Title2[60];
  char Title3[60];
  Int_t bin;
  
  Double_t theta_ev;
  Double_t phi_ev;
  Double_t mom_ev;
  Double_t eff_ev;

  TChain chain_d("Efficiency_cc_tree");
  chain_d->Add("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_*.root");
  chain_d->SetBranchAddress("CC_theta_ev",&theta_ev);
  chain_d->SetBranchAddress("CC_phi_ev",&phi_ev);
  chain_d->SetBranchAddress("CC_mom_ev",&mom_ev);
  chain_d->SetBranchAddress("CC_eff_ev",&eff_ev);
   
  TH3D *H3_count = new TH3D("H3_count","Efficiency count;#theta(deg);#phi(deg);mom{GeV)",100,0,60,600,0,360,50,0,5);
  TH3D *H3_eff = new TH3D("H3_eff","Efficiency ;#theta(deg);#phi(deg);mom{GeV)",100,0,60,600,0,360,50,0,5);
  Double_t cc_eff_content[100][600][50];
  Double_t cc_eff_eff[100][600][50];
  Double_t cc_eff_avg[100][600][50];
  for (Int_t i=0; i<100; i++) {
    for (Int_t j=0; j<600; j++) {
      for (Int_t k=0; k<50; k++) {
	cc_eff_content[i][j][k] = 0;
	cc_eff_eff[i][j][k] = 0;
	cc_eff_avg[i][j][k] = 0;
      }
    }
  }
  Int_t thetabin,phibin,mombin;

  cout << "Getting efficiency data" << endl;
  Int_t nentries = (Int_t)chain_d->GetEntries();
  for (Int_t i=0;i<nentries;i++) {
    chain_d->GetEntry(i);
    H3_count->Fill(theta_ev,phi_ev,mom_ev);
    thetabin = int(theta_ev/60*100) ;
    phibin = int(phi_ev/360*600) ;
    mombin = int(mom_ev/5*50);
//    cout << thetabin << phibin << mombin<< endl;
    if (thetabin<100) {
      cc_eff_eff[thetabin][phibin][mombin] =  cc_eff_eff[thetabin][phibin][mombin] + eff_ev ;
      cc_eff_content[thetabin][phibin][mombin] =  cc_eff_content[thetabin][phibin][mombin] + 1 ;
      if (phi_ev > 330 && eff_ev < 1) cout << "Phibin= "<< phibin <<  "  Efficiency = " << eff_ev << endl;
    }
  }


  
    
  }



  


  



}
