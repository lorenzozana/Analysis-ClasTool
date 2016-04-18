#include "fidc_cut_pim.h"

TFidCutPim::TFidCutPim(Char_t* FileName){
  cout << "Executing constructor" << endl;
 
  Double_t fidc_par[7][2][4][6] ;
  Int_t sector;
  Int_t side;
  Int_t paraf;
  Char_t tmp[10];
  Char_t Title[40];
  float p0, p1, p2, p3, p4, p5;

  cout << "Copying name " << endl;
  fInFile = TString( FileName );


  cout << "Opening file " << fInFile.Data() <<endl;
  ifstream inputfile;
  inputfile.open(fInFile.Data(), ifstream::in);
  if( !inputfile ) {
    cerr << "Error opening input stream" << endl;
    return;
  }              

  cout << "Reading files " << fInFile.Data() << endl; 

 
  
  
  inputfile >> tmp  >> tmp >> tmp  >> tmp >> tmp  >> tmp >> tmp >> tmp  >> tmp >> tmp ;
  while( !inputfile.eof() ){
 
    inputfile >> sector >> side >> paraf >> p0 >> p1 >> p2 >> p3 >> p4 >> p5;

    
    fidc_par[sector][side][paraf][0] = p0;
    fidc_par[sector][side][paraf][1] = p1 ;
    fidc_par[sector][side][paraf][2] = p2;
    fidc_par[sector][side][paraf][3] = p3;
    fidc_par[sector][side][paraf][4] = p4;
    fidc_par[sector][side][paraf][5] = p5;

  }
  inputfile.close();
  
  for(sector = 1 ; sector < 7 ; sector++) {
    for(side = 0 ; side < 2 ; side ++) {
      for(paraf = 0 ; paraf < 3 ; paraf++) {
	sprintf(Title,"fidc_fun_se%i_si%i_p_%i",sector,side,paraf);
	if (paraf==0) {
	  fcfun[sector][side][paraf] = new TF1(Title,"[0] - [1] *TMath::ATan([2] * (x-[3]))",0.2,6);
	}
	else if (paraf==1) {
	  fcfun[sector][side][paraf] = new TF1(Title,"[0]+[1]*x*exp([2]*(x-[3])**2)",0.2,6);
	}
	else if (paraf==2) {
	  fcfun[sector][side][paraf] = new TF1(Title,"[0]+[1]/x**2+[2]*x+[3]/x+[4]*exp([5]*x)",0.2,6);
	}
	else {
	  fcfun[sector][side][paraf] = new TF1(Title,"[0]+[1]*x+[2]/x+[3]*x**2",0.2,6);
	}
	
	
	fcfun[sector][side][paraf]->SetParameter(0,fidc_par[sector][side][paraf][0]);
	fcfun[sector][side][paraf]->SetParameter(1,fidc_par[sector][side][paraf][1]);
	fcfun[sector][side][paraf]->SetParameter(2,fidc_par[sector][side][paraf][2]);
	fcfun[sector][side][paraf]->SetParameter(3,fidc_par[sector][side][paraf][3]);
	if (paraf==2) {
          fcfun[sector][side][paraf]->SetParameter(4,fidc_par[sector][side][paraf][4]);
          fcfun[sector][side][paraf]->SetParameter(5,fidc_par[sector][side][paraf][5]);
	}

	


      }
    }
  }



}








Int_t TFidCutPim::CheckCut(TVector3 Vector){





 

  Int_t sector;
  Int_t side;
  Int_t paraf;
  Double_t theta_low = 0;

  Double_t momento = Vector.Mag();
  Double_t mom_phi = Vector.Phi()*180/3.141592654;
  Double_t p_theta = Vector.Theta()*180/3.141592654;

  fcfidc_fun[0] = new TF1("func2",fitf5,12,60,6);
  fcfidc_fun[1] = new TF1("func3",fitf5,12,60,6);

  if (mom_phi < -30) {
    mom_phi+=360;
  }
  if (mom_phi > 330) {
    mom_phi-=360;
  }
  


  sector = (int) ((mom_phi + 90) /60);


  for(side = 0 ; side < 2 ; side++) {
    for(paraf = 0 ; paraf < 3 ; paraf++) {
      if(side==0) {
	fcfidc_fun[side]->SetParameter(paraf,fcfun[sector][side][paraf]->Eval(momento));
	if(paraf==2) {
	  theta_low=fcfun[sector][side][paraf]->Eval(momento);
	}
      }
      else if(side==1 && paraf==2) {
	fcfidc_fun[side]->SetParameter(paraf,theta_low);
      }
      else {
	fcfidc_fun[side]->SetParameter(paraf,fcfun[sector][side][paraf]->Eval(momento));
      }
    }

    fcfidc_fun[side]->SetParameter(3,120); // theta max
    fcfidc_fun[side]->SetParameter(4, side*2 -1);//fixed: upper-lower switch
    fcfidc_fun[side]->SetParameter(5, sector);//fixed: sector switch

    
  }


  if ( p_theta > theta_low && p_theta < 120 && mom_phi > fcfidc_fun[0]->Eval(p_theta) && mom_phi < fcfidc_fun[1]->Eval(p_theta) ) {
    return 1; // Fiducial Cut passed
  }
  else {
    return 0; // Fiducial Cut not passed
  }
}




