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
/*
  TList *FileList;
  FileList = new TList();
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42011.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42012.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42013.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42014.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42015.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42016.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42017.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42022.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42024.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42025.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42026.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42027.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42028.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42029.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42030.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42031.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42032.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42033.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42034.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42037.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42038.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42039.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42040.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42041.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42042.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42043.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42044.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42047.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42048.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42049.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42050.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42051.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42052.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42053.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42054.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42055.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42056.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42057.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42058.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42059.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42060.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42061.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42062.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42063.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42064.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42065.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42066.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42067.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42068.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42069.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42070.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42071.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42072.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42073.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42074.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42075.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42076.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42077.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42078.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42079.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42080.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42081.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42082.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42083.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42084.root") );                  
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42085.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42086.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42087.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42088.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42089.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42090.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42097.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42098.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42099.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42100.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42101.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42102.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42103.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42104.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42105.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42106.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42107.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42108.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42109.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42111.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42112.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42113.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42114.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42115.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42116.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42117.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42118.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42119.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42120.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42121.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42122.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42123.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42124.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42125.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42126.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42127.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42128.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42129.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42130.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42131.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42132.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42133.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42134.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42135.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42136.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42137.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42138.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42139.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42141.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42142.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42143.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42144.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42145.root") );
  FileList->Add( TFile::Open("/net/data/pumpkin1/lzana/Carbon/CC_eff/elec_42146.root") );


  TFile *first_source = (TFile*)FileList->First();
  TH3D *CC_eff = (TH3D*)first_source.Get("H3_cc_eff");  
  TH3D *CC_fid = (TH3D*)first_source.Get("H3_cc_eff_fid");  

  TFile *nextsource = (TFile*)FileList->After( first_source );
  while ( nextsource ) {
    TH3D *CC_eff2 = (TH3D*)nextsource.Get("H3_cc_eff");  
    TH3D *CC_fid2 = (TH3D*)nextsource.Get("H3_cc_eff_fid"); 
    CC_eff->Add( CC_eff2 );
    CC_fid->Add( CC_fid2 );
    delete CC_eff2;
    delete CC_fid2;
    nextsource = (TFile*)FileList->After( nextsource );
  }
	
  TFile *Target;
  Target = TFile::Open( "/net/data/pumpkin1/lzana/Carbon/CC_eff/cc_eff.root", "RECREATE" );
  CC_eff->Write();
  CC_fid->Write();
  Target->Close();
  */
  
//   //   TFile f("Histo/histos_c.root");
  TFile f("/net/data/pumpkin1/lzana/Carbon/CC_eff/cc_eff.root");


  TH3D *CC_eff = (TH3D*)f.Get("H3_cc_eff");
  TH3D *CC_fid = (TH3D*)f.Get("H3_cc_eff_fid");  
  TFidCut electron_fid_l("/net/home/lzana/Eg2/Code/Clas_5.20/Fiducial_cut/param50_liq.dat",0);
  TF1 * fcfidc_fun[2];
  fcfidc_fun[0] = new TF1("func2",fitf5_2,12,60,6);
  fcfidc_fun[1] = new TF1("func3",fitf5_2,12,60,6);
  fcfidc_fun[0]->SetLineColor(2);
  fcfidc_fun[1]->SetLineColor(2);
  Double_t mom, theta_low;
  Int_t sector = 2;
  gStyle->SetTitleYOffset(1.3);
  c1= new TCanvas("c1","c1",800,800);
//  c1->Divide(2,1);
   CC_eff.GetYaxis()->SetRange(83,167);
   CC_fid.GetYaxis()->SetRange(83,167);
  for( Int_t mombin = 1 ; mombin < 41 ; mombin++) {
    CC_eff.GetZaxis()->SetRange(2*mombin - 1,2*mombin);
    CC_fid.GetZaxis()->SetRange(2*mombin - 1,2*mombin);
    mom = CC_eff->GetMean(3);
    cout << "mean momentum= " << mom << endl;
    for(Int_t side = 0 ; side < 2 ; side++) {
      for(Int_t paraf = 0 ; paraf < 3 ; paraf++) {
	if(side==0) {
	  fcfidc_fun[side]->SetParameter(paraf,electron_fid_l->Get_Par(sector,side,paraf,mom));
	  if(paraf==2) {
	    theta_low=electron_fid_l->Get_Par(sector,side,paraf,mom);
	  }
	}
	else if(side==1 && paraf==2) {
	  fcfidc_fun[side]->SetParameter(paraf,theta_low);
	}
	else {
	  fcfidc_fun[side]->SetParameter(paraf,electron_fid_l->Get_Par(sector,side,paraf,mom));
	}
      }

      fcfidc_fun[side]->SetParameter(3,54); // theta max
      fcfidc_fun[side]->SetParameter(4, side*2 -1);//fixed: upper-lower switch
      fcfidc_fun[side]->SetParameter(5, sector);//fixed: sector switch

    
    }
    TH2F *Hist[1][mombin-1] = (TH2F*)CC_eff->Project3D("yx");
    sprintf(Title,"EFT_S1_%i",mombin);
    Hist[1][mombin-1]->SetName(Title);
    Hist[1][mombin-1]->SetTitle(Title);
//    c1->cd(1);
    Hist[1][mombin-1]->Draw("COL");
    fcfidc_fun[0]->Draw("SAME");
    fcfidc_fun[1]->Draw("SAME");
//     TH2F *Hist[2][mombin-1] = (TH2F*)CC_fid->Project3D("yx");
//     sprintf(Title,"EFT_S2_%i",mombin);
//     Hist[2][mombin-1]->SetName(Title);
//     Hist[2][mombin-1]->SetTitle(Title);
// //    c1->cd(2);
//     Hist[2][mombin-1]->Draw("SAME");
    sprintf(Title,"pictures/cc_eff_plot_mom%i.root",mombin);
    c1->Print(Title);
    sprintf(Title,"pictures/cc_eff_plot_mom%i.gif",mombin);
    c1->Print(Title);
    sprintf(Title,"pictures/cc_eff_plot_mom%i.eps",mombin);
    c1->Print(Title);
    
  }



  


  



}
