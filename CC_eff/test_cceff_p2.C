{
  TFidCut electron_fid_l("/net/home/lzana/Eg2/Code/Clas_5.20/Fiducial_cut/param50_liq.dat");
  TF1 * fcfidc_fun[2];
  fcfidc_fun[0] = new TF1("func2",fitf5_2,12,60,6);
  fcfidc_fun[1] = new TF1("func3",fitf5_2,12,60,6);
  fcfidc_fun[0]->SetLineColor(1);
  fcfidc_fun[1]->SetLineColor(1);
  Double_t mom, theta_low;
  gStyle->SetTitleYOffset(1.3);
  c1= new TCanvas("c1","c1",800,800);
  Float_t gev_m;
  Int_t bin_phi;
  Int_t sectorf;
  for (Int_t i=0; i<50; i++) {
    mom = double(i)/10 ;
    for (Int_t sector=0; sector<6; sector++) {
      sprintf(Title,"HEff_sec%i_mom%i",sector,i);
      gev_m = float(i)/10; 
      sprintf(Title2,"Efficiency Sec%i e-@ %f00 MeV;#theta(deg);#phi(deg)",sector,gev_m);
      Hist[sector][i] = new TH2F(Title,Title2,100,0,60,100,(sector*60),(sector*60+60));
      Int_t sec_low = sector * 100;
      Int_t sec_high= (sector + 1 ) * 100;
      sectorf = sector + 1;
      for(Int_t side = 0 ; side < 2 ; side++) {
	for(Int_t paraf = 0 ; paraf < 3 ; paraf++) {
	  if(side==0) {
	    fcfidc_fun[side]->SetParameter(paraf,electron_fid_l->Get_Par(sectorf,side,paraf,mom));
	    if(paraf==2) {
	      theta_low=electron_fid_l->Get_Par(sectorf,side,paraf,mom);
	    }
	  }
	  else if(side==1 && paraf==2) {
	    fcfidc_fun[side]->SetParameter(paraf,theta_low);
	  }
	  else {
	    fcfidc_fun[side]->SetParameter(paraf,electron_fid_l->Get_Par(sectorf,side,paraf,mom));
	  }
	}
	
	fcfidc_fun[side]->SetParameter(3,54); // theta max                                                                                                              
	fcfidc_fun[side]->SetParameter(4, side*2 -1);//fixed: upper-lower switch                                                                                        
	fcfidc_fun[side]->SetParameter(5, sectorf);//fixed: sector switch                                                                                             
      }
      for (Int_t j=sec_low ; j<sec_high ; j++) {
	for (Int_t k=0; k<100; k++) {
	  bin_phi = j - sec_low;
	  if (cc_eff_content[k][j][i] > 0 ) {
	    Hist[sector][i]-> SetBinContent(k,bin_phi,(cc_eff_eff[k][j][i]/cc_eff_content[k][j][i]));
//	    cout << "writing variable on histogram" << endl;
	  }
	  else Hist[sector][i]-> SetBinContent(k,bin_phi,0) ;

    

	}
      }
      if (sector ==5 && theta_low > 0) {
//	Double_t factor_c = Hist[sector][i]->GetBinContent((int(theta_low/60*100)),50);
	Double_t factor_c = Hist[sector][i]->GetMaximum();
	for (k=0;k<100;k++) {
	  for (bin_phi = 50 ; bin_phi<100 ; bin_phi++) {
	    j=bin_phi+500;
	    if (factor_c > 0 && cc_eff_content[k][j][i] > 0) Hist[sector][i]-> SetBinContent(k,bin_phi,(Hist[4][i]->GetBinContent(k,bin_phi)));
	    Hist[sector][i]->SetMaximum(1);
	  } 
	}
      }
      Hist[sector][i]->Draw("COLZ");
      fcfidc_fun[0]->Draw("SAME");
      fcfidc_fun[1]->Draw("SAME");
      Int_t secbin = sector + 1;
      sprintf(Title,"pictures/cc_eff_plot_sec%i_mom%i.root",secbin,i);
      c1->Print(Title);
      sprintf(Title,"pictures/cc_eff_plot_sec%i_mom%i.gif",secbin,i);
      c1->Print(Title);
      sprintf(Title,"pictures/cc_eff_plot_sec%i_mom%i.eps",secbin,i);
      c1->Print(Title);
      

    }
  }












}
