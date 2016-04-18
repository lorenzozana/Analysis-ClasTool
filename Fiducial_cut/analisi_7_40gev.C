
#include "TH3.h"
#include "TVector3.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "/net/home/lzana/PRODUCTION/packages/ClasTool/include/THEADERClass.h"
#include "/net/home/lzana/PRODUCTION/packages/ClasTool/include/TEVNTClass.h"
#include "/net/home/lzana/PRODUCTION/packages/ClasTool/include/TECPBClass.h"
#include "/net/home/lzana/PRODUCTION/packages/ClasTool/include/TCCPBClass.h"
#include "/net/home/lzana/PRODUCTION/packages/ClasTool/include/TDCPBClass.h"
#include "/net/home/lzana/PRODUCTION/packages/ClasTool/include/TSCPBClass.h"
#include "/net/home/lzana/PRODUCTION/packages/ClasTool/include/TDSTReader.h"
#include "/net/home/lzana/Eg2/Analisi/Fiducial_cut/Clas/fidc_cut.h"



Int_t pid(TDSTReader* R){

 



THEADERClass *head;
TEVNTClass   *evnt;
TEVNTClass   *evnt_all;
TECPBClass   *ecpb;
TDCPBClass   *dcpb;
TCCPBClass   *ccpb;


 TVector3 V3p;
 Double_t p_phi;
 Double_t p_theta;

 Int_t No_Electron_id_Count=0;
 Int_t Z_Cut_fail = 0;
 Int_t Events_left=0;
 Int_t Evnt_stat=0;
 Int_t Evnt_dcstat=0;
 Int_t Dcpb_stat=0;
 Int_t CC_cut=0;
 Int_t EC_cut=0;
 Int_t i2=0;
 Int_t j=0;
 Int_t j2=0;
 Int_t Ro_cut=0;
 Int_t nplus=0;
 Int_t nmin=0;
 Int_t n2_pl_mn=0;
 Double_t ntbt=0;

 if(R==0) {
   cerr << "Bad DSTReader R" <<endl;
   return -1;
 }



 TFidCut test("param40.txt");


TH3F* EFT_S1 = new TH3F("EFT_S1","EC Sector 1; #theta ; #phi ; p",100,0,55,100,-30,30,100,0,5);
TH3F* EFT_S2 = new TH3F("EFT_S2","EC Sector 2; #theta ; #phi ; p",100,0,55,100,30,90,100,0,5);
TH3F* EFT_S3 = new TH3F("EFT_S3","EC Sector 3; #theta ; #phi ; p",100,0,55,100,90,150,100,0,5);
TH3F* EFT_S4 = new TH3F("EFT_S4","EC Sector 4; #theta ; #phi ; p",100,0,55,100,150,210,100,0,5);
TH3F* EFT_S5 = new TH3F("EFT_S5","EC Sector 5; #theta ; #phi ; p",100,0,55,100,210,270,100,0,5);
TH3F* EFT_S6 = new TH3F("EFT_S6","EC Sector 6; #theta ; #phi ; p",100,0,55,100,270,330,100,0,5);


if(!R)R= new TDSTReader();

R->Next();

for(Int_t i=0;i<R->GetEntries();i++){


  R->Next();
  head = R->fEvntHeader;

  if( (i%10000)==0){
    cout << "At " << i << " Event number " << head->NEvent << endl;
  }




  if(R->GetNPart() == 0){
    //    cout << "No particles in event at " << i << " Event number " << head->NEvent << endl;
    //    return;
    continue;
  }
  else {


    evnt = (TEVNTClass *)R->fcaEVNTStore->At(0);
    Int_t ec_stat = evnt->Ecstat;
    Int_t cc_stat = evnt->Ccstat;
    Int_t sc_stat = evnt->Scstat;
    Int_t dc_stat = evnt->Dcstat;
    if ( ec_stat>0 && cc_stat>0  && sc_stat>0 && dc_stat>0 && evnt->Status > 0 ) {
      ecpb = (TECPBClass *)R->fcaECPBStore->At(ec_stat-1);
      ccpb = (TCCPBClass *)R->fcaCCPBStore->At(cc_stat-1);
      dcpb = (TDCPBClass *)R->fcaDCPBStore->At(dc_stat-1);
      Double_t e_mom = sqrt(evnt->Px*evnt->Px+evnt->Py*evnt->Py+evnt->Pz*evnt->Pz);


      //////////// CC CUT /////////////////






      
      ///////////////// EC CUT /////////////////

	int EC_status = ecpb->Status;
	int EC_ok = 0; // cut status flag
	
	float EC_cut_ok = 0, E_EC = ecpb->Etot;
	if ((ecpb->Ein + ecpb->Eout) > ecpb->Etot) {
	  E_EC = ecpb->Ein + ecpb->Eout;
	}
	  
	//float rio = (ecpb->Ein)/(ecpb->Eout);
	float E_EC_out = ecpb->Eout;
	//if(E_EC_out==0. || rio > 10000.) rio = 9.9;//infinity
	
	// EC uvw cut -----------------------------------------------	 
	if (EC_status > 0){ 

	 
	  V3p = (evnt->GetMomVec());
	  p_phi = V3p.Phi()*180/TMath::Pi();
	  p_theta = V3p.Theta()*180/TMath::Pi();

	  if (p_phi < -30) {
	    p_phi+=360;
	  }
	  if (p_phi > 330) {
	    p_phi-=360;
	  }

	}
	






      if (EC_status > 0 && ecpb->Eout>0 && ccpb->Nphe > 25 && ecpb->Ein>0.05 && ecpb->Eout > 0.154 - 1.44 * ecpb->Ein && test.CheckCut(V3p)==1  && E_EC/e_mom > 2.48688e-01 + 1.97737e-01 * exp(-2.52059 *e_mom) -9.54923e-02 /e_mom && E_EC/e_mom < 3.38053e-01 -1.59775e-01 * exp(-2.86707  *e_mom) + 3.72075e-02 /e_mom) {

	if(p_phi>-30 && p_phi<30) {
	  EFT_S1->Fill(p_theta,p_phi,e_mom);
	}
	else if(p_phi>30 && p_phi<90) {
	  EFT_S2->Fill(p_theta,p_phi,e_mom);


	}
	else if(p_phi>90 && p_phi<150) {
	  EFT_S3->Fill(p_theta,p_phi,e_mom);

	}
	else if(p_phi>150 && p_phi<210) {
	  EFT_S4->Fill(p_theta,p_phi,e_mom);


	}
	else if(p_phi>210 && p_phi<270) {
	  EFT_S5->Fill(p_theta,p_phi,e_mom);


	}
	else {
	  EFT_S6->Fill(p_theta,p_phi,e_mom);
	  

	}

      }	
      
    }
  }
  
  
  





  
 }





 
 
 gStyle->SetPalette(1);
 gStyle->SetOptStat(0);


 TCanvas *MyC3 = new TCanvas("MyC3","phi vs theta all cuts 4GeV",1400,800);
 MyC3->Divide(3,2);
 MyC3->cd(1);
 EFT_S1->Draw("COLZ");
 MyC3->cd(2);
 EFT_S2->Draw("COLZ");
 MyC3->cd(3);
 EFT_S3->Draw("COLZ");
 MyC3->cd(4);
 EFT_S4->Draw("COLZ");
 MyC3->cd(5);
 EFT_S5->Draw("COLZ");
 MyC3->cd(6);
 EFT_S6->Draw("COLZ");
 MyC3->Print("pictures/phivstheta_ec_cc_cut.gif");
 MyC3->Print("pictures/phivstheta_ec_cc_cut.ps");


TFile f("/data/EG2/FiducialCut/histos40_test.root","new");
EFT_S1->Write();
EFT_S2->Write();
EFT_S3->Write();
EFT_S4->Write();
EFT_S5->Write();
EFT_S6->Write();


f.Close();





}
