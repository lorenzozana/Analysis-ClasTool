#include "TPart_ident_ct.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
 
using namespace std;

const Double_t fid_theta_max=54;
//For theta_min calculation for electron
const Double_t theta_par0[6]={15        ,15        ,15        ,15        ,13       ,13};
const Double_t theta_par1[6]={-0.425145 ,-1.02217  ,-0.7837   ,-1.47798  ,3.47361  ,3.5714};
const Double_t theta_par2[6]={-0.666294 ,-0.616567 ,-0.673602 ,-0.647113 ,-0.34459 ,-0.398458};
const Double_t theta_par3[6]={5.73077   ,5.51799   ,8.05224   ,7.74737   ,8.45226  ,9.54265};
const Double_t theta_par4[6]={10.4976   ,14.0557   ,15.2178   ,16.7291   ,-63.4556 ,-22.649};
const Double_t theta_par5[6]={-1.13254  ,-1.16189  ,-2.08386  ,-1.79939  ,-3.3791  ,-1.89746};

//For parameter 0 of the phi_min calculation for electron
const Double_t fid_par0_low0[6]={25     ,25       ,25       ,24.6345 ,23.4731 ,24.8599};
const Double_t fid_par0_low1[6]={-12    ,-12      ,-12      ,-12     ,-12     ,-12};
const Double_t fid_par0_low2[6]={0.5605 ,0.714261 ,0.616788 ,0.62982 ,1.84236 ,1.00513};
const Double_t fid_par0_low3[6]={4.4    ,4.4      ,4.4      ,4.4     ,4.4     ,4.4};

//For parameter 1 of the phi_min calculation for electron
const Double_t fid_par1_low0[6]={2.1945    ,4        ,3.3352  ,2.22769   ,1.63143   ,3.19807};
const Double_t fid_par1_low1[6]={1.51417   ,1.56882  ,2       ,2         ,1.90179   ,0.173168};
const Double_t fid_par1_low2[6]={-0.354081 ,-2       ,-2      ,-0.760895 ,-0.213751 ,-0.1};
const Double_t fid_par1_low3[6]={0.5       ,0.5      ,1.01681 ,1.31808   ,0.786844  ,1.6};

//For parameter 0 of the phi_max calculation for electron
const Double_t fid_par0_high0[6]={25       ,25       ,25       ,25       ,23.7067 ,25};
const Double_t fid_par0_high1[6]={-8       ,-10.3277 ,-12      ,-11.3361 ,-12     ,-11.4641};
const Double_t fid_par0_high2[6]={0.479446 ,0.380908 ,0.675835 ,0.636018 ,2.92146 ,0.55553};
const Double_t fid_par0_high3[6]={4.8      ,4.79964  ,4.4      ,4.4815   ,4.4     ,4.41327};

//For parameter 1 of the phi_max calculation for electron
const Double_t fid_par1_high0[6]={3.57349  ,3.02279      ,2.02102    ,3.1948    ,3.0934    ,2.48828};
const Double_t fid_par1_high1[6]={2        ,0.966175     ,2          ,0.192701  ,0.821726  ,2};
const Double_t fid_par1_high2[6]={-2       ,-2           ,-1.70021   ,-1.27578  ,-0.233492 ,-2};
const Double_t fid_par1_high3[6]={0.5      ,0.527823     ,0.68655    ,1.6       ,1.6       ,0.70261};


//FIDUCIAL CUT FOR PI+
//For theta_min calculation for pi+
const Double_t theta_par0_pip[6]={7.00823   ,5.5        ,7.06596     ,6.32763   ,5.5       ,5.5};
const Double_t theta_par1_pip[6]={0.207249  ,0.1        ,0.127764    ,0.1       ,0.211012  ,0.281549};
const Double_t theta_par2_pip[6]={0.169287  ,0.506354   ,-0.0663754  ,0.221727  ,0.640963  ,0.358452};
const Double_t theta_par3_pip[6]={0.1       ,0.1        ,0.100003    ,0.1       ,0.1       ,0.1};
const Double_t theta_par4_pip[6]={0.1       ,3.30779    ,4.499       ,5.30981   ,3.20347   ,0.776161};
const Double_t theta_par5_pip[6]={-0.1      ,-0.651811  , -3.1793    ,-3.3461   ,-1.10808  ,-0.462045};

//For parameter 0 of the phi_min calculation for pi+
const Double_t fid_par0_low0_pip[6]={25.      ,25.      ,25.     ,25.       ,25.       ,25.};
const Double_t fid_par0_low1_pip[6]={-12.     ,-12.     ,-12.    ,-12       ,-12       ,-12};
const Double_t fid_par0_low2_pip[6]={1.64476  ,1.51915  ,1.1095  ,0.977829  ,0.955366  ,0.969146};
const Double_t fid_par0_low3_pip[6]={4.4      ,4.4      ,4.4     ,4.4       ,4.4       ,4.4};

//For parameter 1 of the phi_min calculation for pi+
const Double_t fid_par1_low0_pip[6]={4.         ,4.   ,2.78427   ,3.58539  ,3.32277    ,4.};
const Double_t fid_par1_low1_pip[6]={2.         ,2.   ,2.        ,1.38233  ,0.0410601  ,2.};
const Double_t fid_par1_low2_pip[6]={-0.978469  ,-2.  ,-1.73543  ,-2.      ,-0.953828  ,-2.};
const Double_t fid_par1_low3_pip[6]={0.5        ,0.5  ,0.5       ,0.5      ,0.5        ,1.08576};

//For parameter 0 of the phi_max calculation for pi+
const Double_t fid_par0_high0_pip[6]={25.       ,24.8096  ,24.8758  ,25.       ,25.       ,25.};
const Double_t fid_par0_high1_pip[6]={-11.9735  ,-8.      ,-8.      ,-12.      ,-8.52574  ,-8.};
const Double_t fid_par0_high2_pip[6]={0.803484  ,0.85143  ,1.01249  ,0.910994  ,0.682825  ,0.88846};
const Double_t fid_par0_high3_pip[6]={4.40024   ,4.8      ,4.8      ,4.4       ,4.79866   ,4.8};

//For parameter 1 of the phi_max calculation for pi+
const Double_t fid_par1_high0_pip[6]={2.53606   ,2.65468    ,3.17084  ,2.47156   ,2.42349   ,2.64394};
const Double_t fid_par1_high1_pip[6]={0.442034  ,0.201149   ,1.27519  ,1.76076   ,1.25399   ,0.15892};
const Double_t fid_par1_high2_pip[6]={-2.       ,-0.179631  ,-2.      ,-1.89436  ,-2.       ,-2.};
const Double_t fid_par1_high3_pip[6]={1.02806   ,1.6        ,0.5      ,1.03961   ,0.815707  ,1.31013};


ClassImp(TPart_ident_ct)
  //--------------------------
TPart_ident_ct::TPart_ident_ct():Ebeam(5.014),good1(-100000),M_pi(0.139570)
{ 
  good=0;
}
//-----------------------------
Double_t TPart_ident_ct::betta(Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_betta=good1;
    else
      p_betta=evnt->Betta;
  }
  return p_betta;
}
//-----------------------------
Double_t TPart_ident_ct::betta_alt( Int_t k) {
  p_betta_alt=moment(k)/sqrt(moment(k)*moment(k)+M_pi*M_pi);
  return p_betta_alt;
}
//-----------------------------
Double_t TPart_ident_ct::delta_betta( Int_t k) {
  p_delta_betta=betta(k)-betta_alt(k);
  return p_delta_betta;
}
//-----------------------------
Int_t TPart_ident_ct::deltabeta_cut(Int_t k){
  c_deltabetacut = 0;
//  if (delta_betta(k)<=(0.04+0.015/(moment(k)+0.15)+0.015/pow((moment(k)+0.15),2)) && delta_betta(k)>=(-0.04-0.015/(moment(k)+0.15)-0.015/pow((moment(k)+0.15),2)))    c_deltabetacut = 1;
if ( delta_betta(k)<0.05 && delta_betta(k)>-0.05 ) c_deltabetacut = 1;
  return c_deltabetacut;
}
//------------------------------
Float_t TPart_ident_ct::rf1() {
    header =  GetHEADER()->RF1;   
    if(!header) p_rf1=good1;  
    p_rf1=header;
    return p_rf1;
}
//------------------------------
Float_t TPart_ident_ct::fcg_value() {
    header =  GetHEADER()->GetFCG();
    if(!header) p_fcg=good1;  
    p_fcg=header;
    return p_fcg;
}
//------------------------------
Float_t TPart_ident_ct::nevent() {
    header =  GetHEADER()->NEvent;
    if(!header) p_nevent=good1;  
    p_nevent=header;
    return p_nevent;
}
//------------------------------
Double_t TPart_ident_ct::id( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_id=good1;
    else
      p_id=evnt->Id;
  }
  return p_id;
}
//-----------------------------------------
Double_t TPart_ident_ct::charge( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_charge=good1;
    else
      p_charge=evnt->Charge;
  }
  return p_charge;
}
//-----------------------------------------
Int_t TPart_ident_ct::stat_cc( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_stat_cc=good1;
    else
      p_stat_cc=evnt->Ccstat;
  }
  return p_stat_cc;
}
//------------------------------
Int_t TPart_ident_ct::stat_sc( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_stat_sc=good1;
    else
      p_stat_sc=evnt->Scstat;
  }
  return p_stat_sc;
}
//------------------------------
Int_t TPart_ident_ct::stat_dc( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_stat_dc=good1;
    else
      p_stat_dc=evnt->Dcstat;
  }
  return p_stat_dc;
}
//------------------------------
Int_t TPart_ident_ct::stat_ec( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_stat_ec=good1;
    else
      p_stat_ec=evnt->Ecstat;
  }
  return p_stat_ec;
}
//------------------------------
Double_t TPart_ident_ct::nphe( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("CCPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_nphe=good1;
    else {
      if((evnt->Ccstat)>=1) {
      cc_stat=(evnt->Ccstat)-1;
      ccpb = (TCCPBClass*) GetBankRow("CCPB",cc_stat);
      if(!ccpb) p_nphe=good1;
      else
	p_nphe=ccpb->Nphe;
    } else p_nphe=good1;
    }
  }
  return p_nphe;
}
//------------------------------
Double_t TPart_ident_ct::x( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_x=good1;
    else
      p_x=evnt->X;
  }
  return p_x;
}
//-------------------------------
Double_t TPart_ident_ct::y( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_y=good1;
    else
      p_y=evnt->Y;
  }
  return p_y;
}
//-------------------------------
Double_t TPart_ident_ct::z( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_z=good1;
    else
      p_z=evnt->Z;
  }
  return p_z;
}
//-------------------------------
Double_t TPart_ident_ct::chi2cc( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("CCPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_chi2cc=good1;
    else {
      if((evnt->Ccstat)>=1) {
      cc_stat=(evnt->Ccstat)-1;
      ccpb = (TCCPBClass*) GetBankRow("CCPB",cc_stat);
      if(!ccpb) p_chi2cc=good1;
      else
	p_chi2cc=ccpb->Chi2cc;
      } else p_chi2cc=good1;
    }
  }
  return p_chi2cc;
}
//----------------------------------
Double_t TPart_ident_ct::px( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_px=good1;
    else
      p_px=evnt->Px;
  }
  return p_px;
}
//-----------------------------------
Double_t TPart_ident_ct::py( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_py=good1;
    else
      p_py=evnt->Py;
  }
  return p_py;
}
//-----------------------------------
Double_t TPart_ident_ct::pz( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_pz=good1;
    else
      p_pz=evnt->Pz;
  }
  return p_pz;
}
//------------------------------------------
Double_t TPart_ident_ct::ec_X( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("ECPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_ec_X=good1;
    else {
      if((evnt->Ecstat)>=1) {
      ec_stat=(evnt->Ecstat)-1;
      ecpb = (TECPBClass*) GetBankRow("ECPB",ec_stat);
      if(!ecpb) p_ec_X=good1;
      else
	p_ec_X=ecpb->X;
      } else p_ec_X=good1;
    }
  }
  return p_ec_X;
}
//------------------------------------------
Double_t TPart_ident_ct::ec_Y( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("ECPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_ec_Y=good1;
    else {
      if((evnt->Ecstat)>=1) {
      ec_stat=(evnt->Ecstat)-1;
      ecpb = (TECPBClass*) GetBankRow("ECPB",ec_stat);
      if(!ecpb) p_ec_Y=good1;
      else
	p_ec_Y=ecpb->Y;
      } else p_ec_Y=good1;
    }
  }
  return p_ec_Y;
}
//------------------------------------------
Double_t TPart_ident_ct::ec_Z( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("ECPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_ec_Z=good1;
    else {
      if((evnt->Ecstat)>=1) {
      ec_stat=(evnt->Ecstat)-1;
      ecpb = (TECPBClass*) GetBankRow("ECPB",ec_stat);
      if(!ecpb) p_ec_Z=good1;
      else
	p_ec_Z=ecpb->Z;
      } else p_ec_Z=good1;
    }
  }
  return p_ec_Z;
}
//------------------------------------------
Double_t TPart_ident_ct::etot( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("ECPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_etot=good1;
    else {
      if((evnt->Ecstat)>=1) {
      ec_stat=(evnt->Ecstat)-1;
      ecpb = (TECPBClass*) GetBankRow("ECPB",ec_stat);
      if(!ecpb) p_etot=good1;
      else {
	if(ecpb->Etot < ein(k) +eout(k)) {
	  p_etot =  ein(k) + eout(k);
	}
	else  p_etot=ecpb->Etot;
      }
      } else p_etot=good1;
    }
  }
  return p_etot;
}
//-------------------------------------------
Double_t TPart_ident_ct::ein( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("ECPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_ein=good1;
    else {
      if((evnt->Ecstat)>=1) {
      ec_stat=(evnt->Ecstat)-1;
      ecpb = (TECPBClass*) GetBankRow("ECPB",ec_stat);
      if(!ecpb) p_ein=good1;
      else if ( ( (ecpb->Ein ==0 && ecpb->Innstr>0) || (ecpb->Eout ==0 && ecpb->Outstr>0) ) && ecpb->Etot>0. ) {   
	    Int_t stat=Correct_ECPB_bank(ecpb);
	    p_ein=ecpb->Ein;
      }
      else 
	p_ein=ecpb->Ein;
      } else p_ein=good1;
    }
  }
  return p_ein;
}
//-----------------------------------------
Double_t TPart_ident_ct::eout( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("ECPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_eout=good1;
    else {
      if((evnt->Ecstat)>=1) {
      ec_stat=(evnt->Ecstat)-1;
      ecpb = (TECPBClass*) GetBankRow("ECPB",ec_stat);
      if(!ecpb) p_eout=good1;
      else if ( ( (ecpb->Ein ==0 && ecpb->Innstr>0) || (ecpb->Eout ==0 && ecpb->Outstr>0) ) && ecpb->Etot>0. ) {   
	    Int_t stat=Correct_ECPB_bank(ecpb);
	    p_eout=ecpb->Eout;
      }
      else
	p_eout=ecpb->Eout;
      } else p_eout=good1;
    }
  }
  return p_eout;
}
//-----------------------------------------
Double_t TPart_ident_ct::uvw( Int_t k, Int_t s) {

  const Double_t Ec_the=0.4363323;
  const Double_t ylow=-182.974;
  const Double_t yhi=189.956;
  const Double_t tgrho=1.95325;
  const Double_t sinrho=0.8901256;
  const Double_t cosrho=0.455715;

  Double_t  xec=ec_X(k);
  Double_t  yec=ec_Y(k);
  Double_t phi=TMath::ATan2(yec,xec)*57.29578;
  if(phi<0.)phi=phi+360;
  phi=phi+30;
  if(phi>=360.)phi=phi-360;      
  Double_t Ec_phi=int(phi/60.)*1.0471975;

  Double_t rot[3][3];
  rot[0][0]=cos(Ec_the)*cos(Ec_phi);
  rot[0][1]=-sin(Ec_phi);
  rot[0][2]=sin(Ec_the)*cos(Ec_phi);
  rot[1][0]=cos(Ec_the)*sin(Ec_phi);
  rot[1][1]=cos(Ec_phi);
  rot[1][2]==sin(Ec_the)*sin(Ec_phi);
  rot[2][0]=-sin(Ec_the);
  rot[2][1]=0.;
  rot[2][2]=cos(Ec_the);

  Double_t yi=ec_X(k)*rot[0][0]+ec_Y(k)*rot[1][0]+ec_Z(k)*rot[2][0];
  Double_t xi=ec_X(k)*rot[0][1]+ec_Y(k)*rot[1][1]+ec_Z(k)*rot[2][1];
  Double_t zi=ec_X(k)*rot[0][2]+ec_Y(k)*rot[1][2]+ec_Z(k)*rot[2][2]-510.32;

  if(s==1) p_uvw=(yi-ylow)/sinrho;
  else if(s==2) p_uvw=(yhi-ylow)/tgrho-xi+(yhi-yi)/tgrho;
  else if(s==3) p_uvw=((yhi-ylow)/tgrho+xi+(yhi-yi)/tgrho)/(2*cosrho);
  else cout<<"your third parameter in function uvw() is wrong"<<endl;
  return p_uvw;
}
//-----------------------------------------
Int_t TPart_ident_ct::fcg_cut() {
  c_fcgcut = 0;
  if (fcg_value() > 0 && nevent() > 200000) {
    c_fcgcut = 1;
  }
  else if (nevent() <= 200000) {
    c_fcgcut = 1;
  }
  
  return c_fcgcut;

}
//-----------------------------------------
Bool_t TPart_ident_ct::nphecut( Int_t k) {
  c_nphecut = 0;
  if ((moment(k)<2 && nphe(k)>=25) || (moment(k)>=2 && nphe(k)>=5)) c_nphecut = 1;
  
  return c_nphecut;

}

//-----------------------------------------
Bool_t TPart_ident_ct::nphecut_pi( Int_t k) {
  c_nphecut = 0;
  if ((moment(k)>2.5 && nphe(k)>=25) || ( nphe(k)<25)) c_nphecut = 1;
  
  return c_nphecut;
  
}

//-----------------------------------------
Bool_t TPart_ident_ct::mine_eccut( Int_t k) {
  p_mine_eccut = 0;
  Double_t ec_in  = ein(k);
  Double_t ec_out = eout(k);
  Double_t ec_tot = etot(k);
  Double_t e_mom = moment(k);

  if ( ec_in > 0.05 && ec_out > 0.1725 - 1.25 * ec_in && ec_tot / e_mom > 2.20765e-01 - 2.60992e-01 * exp(-6.72254e-01 *e_mom) + 6.15724e-02/e_mom && ec_tot/e_mom < 3.49817e-01 + 3.26175e-02 * exp(-5.53412e-01 *e_mom) + 2.08615e-03/e_mom)  p_mine_eccut = 1;

  return p_mine_eccut;

}
//-----------------------------------------
Double_t  TPart_ident_ct::delta_t_pi(Int_t k){
  if( GetNRows("EVNT")>0 &&  GetNRows("SCPB")>0){ 
    Double_t Start_time =  GetHEADER()->GetSTT(); 
    Double_t Beta_pi = moment(k) / pow((pow(moment(k),2) + pow(0.13957,2)),.5) ;
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_delta_t_pi=good1;
    else {
      if((evnt->Scstat)>=1) {
	sc_stat=(evnt->Scstat)-1;
	scpb = (TSCPBClass*) GetBankRow("SCPB",sc_stat);
	if(!scpb) p_delta_t_pi=good1;
	else {
	  Double_t tsc=scpb->Time;
	  Double_t lsc=scpb->Path;
	  p_delta_t_pi =  (tsc-lsc/(Beta_pi*29.978)-Start_time) ;	
	}
      } else p_delta_t_pi=good1;
    }
  }
  return p_delta_t_pi;

}
//-----------------------------------------
//-----------------------------------------
Double_t  TPart_ident_ct::delta_t_proton(Int_t k){
  if( GetNRows("EVNT")>0 &&  GetNRows("SCPB")>0){ 
    Double_t Start_time =  GetHEADER()->GetSTT(); 
    Double_t Beta_pi = moment(k) / pow((pow(moment(k),2) + pow(0.938272046,2)),.5) ;
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_delta_t_pi=good1;
    else {
      if((evnt->Scstat)>=1) {
	sc_stat=(evnt->Scstat)-1;
	scpb = (TSCPBClass*) GetBankRow("SCPB",sc_stat);
	if(!scpb) p_delta_t_pi=good1;
	else {
	  Double_t tsc=scpb->Time;
	  Double_t lsc=scpb->Path;
	  p_delta_t_pi =  (tsc-lsc/(Beta_pi*29.978)-Start_time) ;	
	}
      } else p_delta_t_pi=good1;
    }
  }
  return p_delta_t_pi;

}
//-----------------------------------------


Int_t  TPart_ident_ct::delta_t_pip_cut(Int_t k){
  c_delta_t_pip = 0;
  Double_t delta_t_pip = fabs( delta_t_pi(k) ) ;
  if (delta_t_pip < 6.50148e-01 - 1.97200e-02 * exp(6.44555e-01 *moment(k)) + 1.58093e-01/moment(k)) c_delta_t_pip = 1 ;

  return c_delta_t_pip;
}
//-----------------------------------------

Int_t  TPart_ident_ct::delta_t_proton_cut(Int_t k){
  c_delta_t_pip = 0;
  Double_t delta_t_pip = fabs( delta_t_proton(k) ) ;
  if (delta_t_pip < 4.0) c_delta_t_pip = 1 ;
  //  cout << delta_t_pip << " " << c_delta_t_pip << endl;
  return c_delta_t_pip;
}
//-----------------------------------------

Int_t  TPart_ident_ct::delta_t_pim_cut(Int_t k){
  c_delta_t_pim = 0;
  Double_t delta_t_pim = fabs( delta_t_pi(k) ) ;
  if (delta_t_pim < 4.30082e-01 - 6.32486e-01 * exp(-2.71598*moment(k)) + 2.03471e-01/moment(k)) c_delta_t_pim = 1 ;

  return c_delta_t_pim;

}
//-----------------------------------------
Bool_t TPart_ident_ct::pfid_ecinout( Int_t k) {
  
  Double_t rout=eout(k)/moment(k);
  Double_t rinn=ein(k)/moment(k)-0.2713;
  const Double_t cons=0.2713*0.3;
  Double_t low_rout=-rinn-cons/sqrt(0.5);
  Double_t rinnout=rout+rinn;
  p_ieccut=0;
  
  if(ein(k)>=0.04 && rout>=low_rout){
    if(moment(k)<0.7 && rinnout<cons/sqrt(0.85)) p_ieccut = 1;
    else if (moment(k)>=0.7 && moment(k)<0.9 && rinnout<cons/sqrt(0.80)) p_ieccut = 1;	   
    else if (moment(k)>=0.9 && moment(k)<1.1 && rinnout<cons/sqrt(0.85)) p_ieccut = 1;	   
    else if (moment(k)>=1.1 && moment(k)<1.3 && rinnout<cons/sqrt(1.05)) p_ieccut = 1;
    else if (moment(k)>=1.3 && moment(k)<1.5 && rinnout<cons/sqrt(1.10)) p_ieccut = 1;
    else if (moment(k)>=1.5 && moment(k)<1.7 && rinnout<cons/sqrt(1.35)) p_ieccut = 1;
    else if (moment(k)>=1.7 && moment(k)<1.9 && rinnout<cons/sqrt(1.35)) p_ieccut = 1;
    else if (moment(k)>=1.9 && moment(k)<2.1 && rinnout<cons/sqrt(1.45)) p_ieccut = 1;
    else if (moment(k)>=2.1 && moment(k)<2.3 && rinnout<cons/sqrt(1.35)) p_ieccut = 1;
    else if (moment(k)>=2.3 && moment(k)<2.5 && rinnout<cons/sqrt(1.35)) p_ieccut = 1;
    else if (moment(k)>=2.5 && moment(k)<2.7 && rinnout<cons/sqrt(1.35)) p_ieccut = 1;
    else if (moment(k)>=2.7 && moment(k)<2.9 && rinnout<cons/sqrt(1.30)) p_ieccut = 1;
    else if (moment(k)>=2.9 && moment(k)<3.1 && rinnout<cons/sqrt(1.35)) p_ieccut = 1;
    else if (moment(k)>=3.1 && moment(k)<3.3 && rinnout<cons/sqrt(1.35)) p_ieccut = 1;
    else if (moment(k)>=3.3 && moment(k)<3.5 && rinnout<cons/sqrt(1.50)) p_ieccut = 1;
    else if (moment(k)>=3.5 && moment(k)<3.7 && rinnout<cons/sqrt(1.60)) p_ieccut = 1;
    else if (moment(k)>=3.7 && moment(k)<3.9 && rinnout<cons/sqrt(1.80)) p_ieccut = 1;
    else if (moment(k)>=3.9 && moment(k)<4.1 && rinnout<cons/sqrt(1.80)) p_ieccut = 1;
    else if (moment(k)>=4.1 && moment(k)<4.3 && rinnout<cons/sqrt(1.80)) p_ieccut = 1;
    else if (moment(k)>=4.3 && rinnout<cons/sqrt(1.80)) p_ieccut = 1;
  }
  
  return p_ieccut;
}
//-----------------------------------------
Int_t TPart_ident_ct::sector_alt( Int_t k) {
  const Double_t r2d=57.2957795;
  Double_t pex=px(k);
  Double_t pey=py(k);
  Double_t phi=TMath::ATan2(pey,pex)*r2d;
  if(phi>=-30) phi=phi+30;
  else phi=phi+390;
  p_sector_alt=int(phi/60.);
  return p_sector_alt;
}
//-----------------------------------------
Int_t TPart_ident_ct::vertex_cut_elec() {
  p_vertex_cut_elec=0;
  Double_t ele_liq_lim[6][2];
  Double_t ele_sol_low[6];
  ele_liq_lim[0][0]=-32.5;
  ele_liq_lim[0][1]=-28;
  ele_liq_lim[1][0]=-32.5;
  ele_liq_lim[1][1]=-27.5;
  ele_liq_lim[2][0]=-32;
  ele_liq_lim[2][1]=-27.25;
  ele_liq_lim[3][0]=-32;
  ele_liq_lim[3][1]=-27.75;
  ele_liq_lim[4][0]=-32.5;
  ele_liq_lim[4][1]=-28.35;
  ele_liq_lim[5][0]=-33.5;
  ele_liq_lim[5][1]=-28.75;
  Double_t ele_sol_high=-20;
  ele_sol_low[0]=-26.5;
  ele_sol_low[1]=-26.;
  ele_sol_low[2]=-25.65;
  ele_sol_low[3]=-25.85;
  ele_sol_low[4]=-26.65;
  ele_sol_low[5]=-27.15;
  Int_t n_sector=sector_alt(0);
  //if((z(0)>=ele_liq_lim[n_sector][0] && z(0)<=ele_liq_lim[n_sector][1]) || (z(0)>=ele_sol_low[n_sector] && z(0)<=ele_sol_high)) p_vertex_cut_elec=1;
  if(z(0)>=ele_liq_lim[n_sector][0] && z(0)<=ele_liq_lim[n_sector][1]) p_vertex_cut_elec=1;
  if(z(0)>=ele_sol_low[n_sector] && z(0)<=ele_sol_high) p_vertex_cut_elec=2;

  return p_vertex_cut_elec;
}

//-----------------------------------------
Int_t TPart_ident_ct::vertex_cut_proton( Int_t k) {
  p_vertex_cut_pion=0;
  if (x(k)>-1. && x(k)<1. &&  y(k)>-2. && y(k)<2. && z(k)>-27. && z(k)<-23.) p_vertex_cut_pion=1;
  return p_vertex_cut_pion;
}
//-----------------------------------------
Int_t TPart_ident_ct::vertex_cut_pion( Int_t k) {
  p_vertex_cut_pion=0;
  //electron originates from liquid target
  Double_t pion_liq_low,pion_liq_high,pion_sol_low,pion_sol_high;
  Int_t n_ele_sector=sector_alt(0);
  Int_t n_pion_sector=sector_alt(k);
  if(n_pion_sector==5 || (n_ele_sector==3 && n_pion_sector==4) || (n_pion_sector==0 && n_ele_sector!=1 && n_ele_sector!=4)) pion_liq_low=-36.;
  else pion_liq_low=-35.;
  if(n_ele_sector==3 && n_pion_sector==2) pion_liq_high=-24.;
  else if((n_ele_sector==5 && n_pion_sector!=2 && n_pion_sector!=3)|| (n_pion_sector==5 && n_ele_sector!=2)|| (n_ele_sector==0 && n_pion_sector==0)|| (n_ele_sector==1 && n_pion_sector==1)|| (n_pion_sector==4 && (n_ele_sector==3 || n_ele_sector==4))) pion_liq_high=-26.;
  else pion_liq_high=-25.;
  pion_sol_low=-30.;
  pion_sol_high=-18.;
  //if((z(k)>=pion_liq_low && z(k)<=pion_liq_high) || (z(k)>=-30 && z(k)<=-18)) p_vertex_cut_pion=1;
  if(vertex_cut_elec()==1 && z(k)>=pion_liq_low && z(k)<=pion_liq_high) p_vertex_cut_pion=1;
  else if(vertex_cut_elec()==2 && z(k)>=pion_sol_low && z(k)<=pion_sol_high) p_vertex_cut_pion=2;
  else p_vertex_cut_pion = 0;
  return p_vertex_cut_pion;
}

//-----------------------------------------
Int_t TPart_ident_ct::vertex_cut_mine( Int_t k, Int_t m) {

  c_vertex_cut_mine = 0; //k = pi- ; m = pi+
  if (z(0) >-32.5 && z(0) <-27.5 && z(k)>-35 && z(k)<-25 && z(m)>-35 && z(m)<-25 && z(k) < -z(m) -54)  c_vertex_cut_mine = 1 ; // Liquid Target
  else if (z(0) >-27 && z(0) <-23 && z(k)>-28 && z(k)<-20 && z(m)>-28 && z(m)<-20 && z(k) > -z(m) -53)  c_vertex_cut_mine = 2 ; // Solid Target

  return c_vertex_cut_mine ;

}

Int_t TPart_ident_ct::vertex_cut_el_mine() {

  c_vertex_cut_mine = 0; // only electron
  if (z(0) >-32.5 && z(0) <-27.5)  c_vertex_cut_mine = 1 ; // Liquid Target
  else if (z(0) >-27 && z(0) <-23)  c_vertex_cut_mine = 2 ; // Solid Target

  return c_vertex_cut_mine ;

}


//-----------------------------------------
Double_t TPart_ident_ct::M2( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("ECPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_m2=good1;
    else {
      if((evnt->Ecstat)>=1) {
      ec_stat=(evnt->Ecstat)-1;
      ecpb = (TECPBClass*) GetBankRow("ECPB",ec_stat);
      if(!ecpb) p_m2=good1;
      else
	p_m2=ecpb->M2_hit;
      } else p_m2=good1;
    }
  }
  return p_m2;
}
//-----------------------------------------
Double_t TPart_ident_ct::M3( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("ECPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_m3=good1;
    else {
      if((evnt->Ecstat)>=1) {
      ec_stat=(evnt->Ecstat)-1;
      ecpb = (TECPBClass*) GetBankRow("ECPB",ec_stat);
      if(!ecpb) p_m3=good1;
      else
	p_m3=ecpb->M3_hit;
      } else p_m3=good1;
    }
  }
  return p_m3;
}
//-----------------------------------------
Double_t TPart_ident_ct::M4( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("ECPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_m4=good1;
    else {
      if((evnt->Ecstat)>=1) {
      ec_stat=(evnt->Ecstat)-1;
      ecpb = (TECPBClass*) GetBankRow("ECPB",ec_stat);
      if(!ecpb) p_m4=good1;
      else
	p_m4=ecpb->M4_hit;
      } else p_m4=good1;
    }
  }
  return p_m4;
}
//------------------------------
Double_t TPart_ident_ct::status( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_status=good1;
    else
      p_status=evnt->Status;
  }
  return p_status;
}
//------------------------------
Double_t TPart_ident_ct::cc_status( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("CCPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_cc_status=good1;
    else {
      if((evnt->Ccstat)>=1) {
      cc_stat=(evnt->Ccstat)-1;
      ccpb = (TCCPBClass*) GetBankRow("CCPB",cc_stat);
      if(!ccpb) p_cc_status=good1;
      else
	p_cc_status=ccpb->Status;
    } else p_cc_status=good1;
    }
  }
  return p_cc_status;
}
//------------------------------
Double_t TPart_ident_ct::ec_status( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("ECPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_ec_status=good1;
    else {
      if((evnt->Ecstat)>=1) {
      ec_stat=(evnt->Ecstat)-1;
      ecpb = (TECPBClass*) GetBankRow("ECPB",ec_stat);
      if(!ecpb) p_ec_status=good1;
      else
	p_ec_status=ecpb->Status;
      } else p_ec_status=good1;
    }
  }
  return p_ec_status;
}
//-----------------------------------------
Double_t TPart_ident_ct::dc_status( Int_t k) {
  if( GetNRows("EVNT")>0 &&  GetNRows("DCPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) p_dc_status=good1;
    else {
      if((evnt->Dcstat)>=1) {
      dc_stat=(evnt->Dcstat)-1;
      dcpb = (TDCPBClass*) GetBankRow("DCPB",dc_stat);
      if(!dcpb) p_dc_status=good1;
      else
	p_dc_status=dcpb->Status;
      } else p_dc_status=good1;
    }
  }
  return p_dc_status;
}
//--------------------------------
Double_t TPart_ident_ct::theta( Int_t k) {
  p_theta = acos(pz(k)/moment(k));
  return p_theta;
}
//----------------------------------
Double_t TPart_ident_ct::theta_virt() {
  p_theta_virt = acos((Ebeam-moment(0)*cos(theta(0)))/(sqrt(Q2()+nu()*nu())));
  return p_theta_virt;
}
//-----------------------------------
Double_t TPart_ident_ct::moment( Int_t k) {
  p_moment=sqrt(px(k)*px(k)+py(k)*py(k)+pz(k)*pz(k));
  return p_moment;
}
//-----------------------------------
Double_t TPart_ident_ct::mass2( Int_t k) {
  p_mass2=moment(k)*moment(k)*(pow(betta(k),-2)-1);
  return p_mass2;
}
//-----------------------------------
Double_t TPart_ident_ct::Q2() {

  TVector3 V3_1 , V3_2 ,V3_3;
  V3_1.SetXYZ(px(0),py(0),pz(0));
  V3_2.SetXYZ(0,0,Ebeam);
  V3_3 = V3_2 - V3_1;   // Virtual photon momentum vector
  

  TLorentzVector V4_1(V3_3,(Ebeam - V3_1.Mag())); // Virtual photon quadrimomentum

  p_Q2 = - V4_1 * V4_1; 
  return p_Q2;
}
//------------------------------------
Double_t TPart_ident_ct::W() {
  p_W=sqrt(0.938*0.938+2*0.938*nu()-Q2());
  return p_W;
}
//------------------------------------
//Double_t TPart_ident_ct::pt2(TClasTool * Int_t k) {
//p_pt2 = pow(moment(k),2)-pow((pz(k)*(Ebeam-pz(0))-sqrt(pow(px(0),2)+pow(py(0),2))*(px(k)*sin(phi(0)/57.3)+py(k)*cos(phi(0)/57.3))),2)/(nu()*nu()+Q2());
//return p_pt2;
//}
//---------------------------------------
Double_t TPart_ident_ct::pt2( Int_t k) {
  p_pt2 = moment(k)*moment(k)*(1-cos_theta_pq(k)*cos_theta_pq(k));
  return p_pt2;
}
//---------------------------------------
Double_t TPart_ident_ct::cos_theta_pq( Int_t k) {//The angle between particle and virtual photon
  p_theta_pq = (pz(k)*(Ebeam-pz(0))-px(k)*px(0)-py(k)*py(0))/(sqrt(nu()*nu()+Q2())*moment(k));
  return p_theta_pq;
}
//---------------------------------------
Double_t TPart_ident_ct::Z_pi( Int_t k) {
  p_Z_pi=sqrt(0.139*0.139+moment(k)*moment(k))/nu();
  return p_Z_pi;
}
//----------------------------------------
Double_t TPart_ident_ct::Z_pi_zero( Int_t k) {
  p_Z_pi_zero=sqrt(0.135*0.135+moment(k)*moment(k))/nu();
  return p_Z_pi_zero;
}
//----------------------------------------
Double_t TPart_ident_ct::nu() {
  p_nu=Ebeam-moment(0);
  return p_nu;
}
//-----------------------------------------
Int_t TPart_ident_ct::Good_evnt( Int_t k)
{
  if(betta(k)>0.01 && charge(k)>good1/2 && moment(k)>0.0001 && nu()>0.001 && Q2()>0.001 && z(k)>good1/2 && px(k)>good1/2 && py(k)>good1/2 && pz(k)>good1/2 && status(k)>0 && status(k)<100) good=1; else good=0;
  return good;
}
//------------------------------------------
Int_t TPart_ident_ct::Good_ccpb( Int_t k)
{
  if(nphe(k)>good1/2 && chi2cc(k)>good1/2 && cc_status(k)>good1/2) good=1; else good=0;
  return good;
}
//------------------------------------------
Int_t TPart_ident_ct::Good_ecpb( Int_t k)
{
  if(etot(k)>good1/2 && ein(k)>good1/2  && eout(k)>good1/2 && ec_status(k)>good1/2 && ec_X(k)>good1/2 && ec_Y(k)>good1/2 && ec_Z(k)>good1/2) good=1; else good=0;
  return good;
}
//------------------------------------------
Double_t TPart_ident_ct::phi( Int_t k) {
  if( GetNRows("EVNT")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",k);
    if(!evnt) {
      p_phi=good1;
    }
    else {
      Double_t angle = 57.3*atan((evnt->Px)/(evnt->Py)) ;
     if((evnt->Py)>=0 && (evnt->Px)>=0) p_phi = fabs(angle);else
       if((evnt->Py)>=0 && (evnt->Px)<0) p_phi = -fabs(angle);else
	 if((evnt->Py)<0 && (evnt->Px)>=0) p_phi = 180-fabs(angle);else
	   if((evnt->Py)<0 && (evnt->Px)<0) p_phi = -180+fabs(angle);else p_phi=good1;
    }
  }
  return p_phi;
}
//-----------------------------------------
Double_t TPart_ident_ct::phi_virt() {
  if(phi(0)>0) p_phi_virt=-180+phi(0);
  if(phi(0)<=0) p_phi_virt=180+phi(0);
  return p_phi_virt;
}
//-----------------------------------------
Double_t TPart_ident_ct::phi_cut( Int_t k) {
  if(phi(k)>-30 && phi(k)<30) {
    if((z(k)>-30.75 && z(k)<-28.75) || (z(k)>-24.75 && z(k)<-23.5)) 
      p_phi_cut=1; else p_phi_cut=0;
  }else
    if(phi(k)>30 && phi(k)<90) {
      if((z(k)>-31.25 && z(k)<-29) || (z(k)>-25.25 && z(k)<-23.75)) 
	p_phi_cut=1; else p_phi_cut=0;
    }else
      if(phi(k)>90 && phi(k)<150) { 
	if((z(k)>-31.5 && z(k)<-29.5) || (z(k)>-25.75 && z(k)<-24.5)) 
	  p_phi_cut=1; else p_phi_cut=0;
      }else
	if(phi(k)>150 && phi(k)<180) {
	  if((z(k)>-32 && z(k)<-29.75) || (z(k)>-26.25 && z(k)<-24.75)) 
	    p_phi_cut=1; else p_phi_cut=0;
	}else
	  if(phi(k)>-180 && phi(k)<-150) {
	    if((z(k)>-32 && z(k)<-29.75) || (z(k)>-26.25 && z(k)<-24.75)) 
	      p_phi_cut=1; else p_phi_cut=0;
	  }else
	    if(phi(k)>-150 && phi(k)<-90) { 
	      if((z(k)>-31.5 && z(k)<-29.25) || (z(k)>-25.5 && z(k)<-24)) 
		p_phi_cut=1; else p_phi_cut=0;
	    }else
	      if(phi(k)>-90 && phi(k)<-30) {
		if((z(k)>-31 && z(k)<-28.75) || (z(k)>-25 && z(k)<-23.5)) 
		  p_phi_cut=1; else p_phi_cut=0;
	      }else p_phi_cut=0;
		return p_phi_cut;
}
//-----------------------------------------
//Bool_t TPart_ident_ct::FID_CUT_ELEC(TClasTool *R){

//return p_FID_CUT_ELE;
//}
//-----------------------------------------
Double_t TPart_ident_ct::fid_theta( Int_t k) {
  Double_t fid_theta_val;
  TVector3 V3p(px(k),py(k),pz(k));
  fid_theta_val=V3p.Theta()*180/(TMath::Pi());
  return fid_theta_val;
}
//-----------------------------------------
Double_t TPart_ident_ct::fid_phi( Int_t k) {
  Double_t fid_phi_val;
  TVector3 V3p(px(k),py(k),pz(k));
  fid_phi_val = V3p.Phi()*180/(TMath::Pi());
  if(fid_phi_val<-30) fid_phi_val+=360;
  if(fid_phi_val>330) fid_phi_val-=360;
  return fid_phi_val;
}
//-----------------------------------------
Int_t TPart_ident_ct::fid_sector( Int_t k) {
  Int_t sector;
  if(fid_phi(k)!=330){
    sector=int((fid_phi(k)+90)/60)-1;
    return sector;
  } else return 5;
}
//-----------------------------------------[0]+[1]/x**2+[2]*x+[3]/x+[4]*exp([5]*x)
Double_t TPart_ident_ct::fid_theta_min() {
  Int_t sector=fid_sector(0);
  Double_t theta_min_val=theta_par0[sector]+theta_par1[sector]/pow(moment(0),2)+theta_par2[sector]*moment(0)+theta_par3[sector]/moment(0)+theta_par4[sector]*exp(theta_par5[sector]*moment(0));
  return theta_min_val;
}
//-----------------------------------------[0]+[1]*x*exp([2]*(x-[3])**2)
Double_t TPart_ident_ct::fid_func( Int_t side, Int_t param) {
  Int_t sector=fid_sector(0);
  Double_t fid_func_val;
  if(side==0 && param==0) fid_func_val=fid_par0_low0[sector]+fid_par0_low1[sector]*exp(fid_par0_low2[sector]*(moment(0)-fid_par0_low3[sector]));
  if(side==1 && param==0) fid_func_val=fid_par0_high0[sector]+fid_par0_high1[sector]*exp(fid_par0_high2[sector]*(moment(0)-fid_par0_high3[sector]));
  if(side==0 && param==1) fid_func_val=fid_par1_low0[sector]+fid_par1_low1[sector]*moment(0)*exp(fid_par1_low2[sector]*pow((moment(0)-fid_par1_low3[sector]),2));
  if(side==1 && param==1) fid_func_val=fid_par1_high0[sector]+fid_par1_high1[sector]*moment(0)*exp(fid_par1_high2[sector]*pow((moment(0)-fid_par1_high3[sector]),2));
  return fid_func_val;
}												
//-----------------------------------------60.*(par2[5]-1)+par2[4]*par2[0]*(1.-1./((arg-par2[2])/(par2[1])+1.))
Double_t TPart_ident_ct::fid_phi_min() {
  Int_t sector=fid_sector(0);
  Double_t fid_phi_min_val;
  if(fid_theta(0)<=fid_theta_min() || fid_theta(0)>=fid_theta_max){
    fid_phi_min_val=60.*sector;
    return fid_phi_min_val;
  } else {
    fid_phi_min_val=60.*sector-fid_func(0,0)*(1-1/(1+(fid_theta(0)-fid_theta_min())/fid_func(0,1)));
    return fid_phi_min_val;
  }
}
//-----------------------------------------60.*(par2[5]-1)+par2[4]*par2[0]*(1.-1./((arg-par2[2])/(par2[1])+1.))
Double_t TPart_ident_ct::fid_phi_max() {
  Int_t sector=fid_sector(0);
  Double_t fid_phi_max_val;
  if(fid_theta(0)<=fid_theta_min() || fid_theta(0)>=fid_theta_max){
    fid_phi_max_val=60.*sector;
    return fid_phi_max_val;
  } else {
    fid_phi_max_val=60.*sector+fid_func(1,0)*(1-1/(1+(fid_theta(0)-fid_theta_min())/fid_func(1,1)));
    return fid_phi_max_val;
  }
}
//-----------------------------------------
Bool_t TPart_ident_ct::fid_CheckCut() {
  if(fid_theta(0)>fid_theta_min() && fid_theta(0)<fid_theta_max && fid_phi(0)>fid_phi_min() && fid_phi(0)<fid_phi_max())  return 1; // Fiducial Cut passed
  else return 0; // Fiducial Cut not passed
}
//-----------------------------------------

//CUTS FOR PI+ FIDUCIAL CUT
//-----------------------------------------[0]+[1]/x**2+[2]*x+[3]/x+[4]*exp([5]*x)
Double_t TPart_ident_ct::fid_theta_min_pip( Int_t k) {
  Int_t sector=fid_sector(k);
  Double_t theta_min_val=theta_par0_pip[sector]+theta_par1_pip[sector]/pow(moment(k),2)+theta_par2_pip[sector]*moment(k)+theta_par3_pip[sector]/moment(k)+theta_par4_pip[sector]*exp(theta_par5_pip[sector]*moment(k));
  return theta_min_val;
}
//-----------------------------------------[0]+[1]*x*exp([2]*(x-[3])**2)
Double_t TPart_ident_ct::fid_func_pip( Int_t side, Int_t param, Int_t k) {
  Int_t sector=fid_sector(k);
  Double_t fid_func_val_pip;
  if(side==0 && param==0) fid_func_val_pip=fid_par0_low0_pip[sector]+fid_par0_low1_pip[sector]*exp(fid_par0_low2_pip[sector]*(moment(k)-fid_par0_low3_pip[sector]));
  if(side==1 && param==0) fid_func_val_pip=fid_par0_high0_pip[sector]+fid_par0_high1_pip[sector]*exp(fid_par0_high2_pip[sector]*(moment(k)-fid_par0_high3_pip[sector]));
  if(side==0 && param==1) fid_func_val_pip=fid_par1_low0_pip[sector]+fid_par1_low1_pip[sector]*moment(k)*exp(fid_par1_low2_pip[sector]*pow((moment(k)-fid_par1_low3_pip[sector]),2));
  if(side==1 && param==1) fid_func_val_pip=fid_par1_high0_pip[sector]+fid_par1_high1_pip[sector]*moment(k)*exp(fid_par1_high2_pip[sector]*pow((moment(k)-fid_par1_high3_pip[sector]),2));
  return fid_func_val_pip;
}												
//-----------------------------------------60.*(par2[5]-1)+par2[4]*par2[0]*(1.-1./((arg-par2[2])/(par2[1])+1.))
Double_t TPart_ident_ct::fid_phi_min_pip( Int_t k) {
  Int_t sector=fid_sector(k);
  Double_t fid_phi_min_val;
  if(fid_theta(k)<=fid_theta_min_pip(k) || fid_theta(k)>=fid_theta_max){
    fid_phi_min_val=60.*sector;
    return fid_phi_min_val;
  } else {
    fid_phi_min_val=60.*sector-fid_func_pip(0,0,k)*(1-1/(1+(fid_theta(k)-fid_theta_min_pip(k))/fid_func_pip(0,1,k)));
    return fid_phi_min_val;
  }
}
//-----------------------------------------60.*(par2[5]-1)+par2[4]*par2[0]*(1.-1./((arg-par2[2])/(par2[1])+1.))
Double_t TPart_ident_ct::fid_phi_max_pip( Int_t k) {
  Int_t sector=fid_sector(k);
  Double_t fid_phi_max_val;
  if(fid_theta(k)<=fid_theta_min_pip(k) || fid_theta(k)>=fid_theta_max){
    fid_phi_max_val=60.*sector;
    return fid_phi_max_val;
  } else {
    fid_phi_max_val=60.*sector+fid_func_pip(1,0,k)*(1-1/(1+(fid_theta(k)-fid_theta_min_pip(k))/fid_func_pip(1,1,k)));
    return fid_phi_max_val;
  }
}
//-----------------------------------------
Bool_t TPart_ident_ct::fid_CheckCut_pip( Int_t k) {
  if(fid_theta(k)>fid_theta_min_pip(k) && fid_theta(k)<fid_theta_max && fid_phi(k)>fid_phi_min_pip(k) && fid_phi(k)<fid_phi_max_pip(k))  return 1; // Fiducial Cut passed
  else return 0; // Fiducial Cut not passed
}
//-----------------------------------------

Double_t TPart_ident_ct::invariant_mass(Int_t k, Int_t m) {

  evnt1 = (TEVNTClass*) GetBankRow("EVNT",k);
  evnt2 = (TEVNTClass*) GetBankRow("EVNT",m);
  TVector3 V3_1 , V3_2; 
  V3_1 = (evnt1->GetMomVec());
  V3_2 = (evnt2->GetMomVec());

  TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(M_pi,2)));
  TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(M_pi,2))); 
  
  inv_mass =sqrt((V4_1 + V4_2) * (V4_1 + V4_2));

  return inv_mass;

}
//-----------------------------------------
Double_t TPart_ident_ct::Get_lc(Int_t k, Int_t m) {
 p_lc = 2 * nu() / (Q2() + pow(invariant_mass(k,m),2));
  return p_lc;
}
//-----------------------------------------
Double_t TPart_ident_ct::find_t_rho(Int_t k , Int_t m , Int_t j) {

  // evnt1 = electron , evnt2 = pi- , evnt3= pi+

  evnt1 = (TEVNTClass*) GetBankRow("EVNT",k);
  evnt2 = (TEVNTClass*) GetBankRow("EVNT",m);
  evnt3 = (TEVNTClass*) GetBankRow("EVNT",j); 

  TVector3 V3_1 , V3_2 ,V3_3;
  V3_1 = (evnt1->GetMomVec());
  V3_2.SetXYZ(0,0,Ebeam);
  V3_3 = V3_2 - V3_1;   // Virtual photon momentum vector
  

  TLorentzVector V4_1(V3_3,(Ebeam - V3_1.Mag())); // Virtual photon quadrimomentum
  V3_1 = (evnt2->GetMomVec());
  V3_2 = (evnt3->GetMomVec());

  TLorentzVector V4_2(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
  TLorentzVector V4_3(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum
  
  
  t_rho = - (V4_1 - V4_2 - V4_3) * (V4_1 - V4_2 - V4_3);

  return t_rho;

}

//-----------------------------------------


Int_t TPart_ident_ct::cut_t_rho(Int_t k , Int_t m , Int_t j) {
  c_cut_t_rho = 0;
  if (find_t_rho(k,m,j) <= 0.45 && find_t_rho(k,m,j) > 0,1) c_cut_t_rho = 1;
  
  return c_cut_t_rho;
}
//-----------------------------------------

Double_t TPart_ident_ct::find_rho_energy(Int_t k, Int_t m) {
  
  rho_energy = sqrt(M_pi*M_pi + pow(moment(k),2)) + sqrt(M_pi*M_pi + pow(moment(m),2)) ;
  return rho_energy;
}

//-----------------------------------------

Double_t TPart_ident_ct::find_Delta_E(Int_t k , Int_t m , Int_t j) {

  // k = electron     m = pi-    j = pi+  
  Delta_E = Ebeam - sqrt(0.000511*0.000511 +pow(moment(k),2)) - find_rho_energy(m,j)  - find_t_rho(k,m,j)/(2*0.938272);
  Delta_E = fabs(Delta_E);
  return Delta_E;
}


//-----------------------------------------

Double_t TPart_ident_ct::find_zrho(Int_t k , Int_t m , Int_t j) {

  // k = electron     m = pi-    j = pi+  
  zrho  = find_rho_energy(m,j) / (Ebeam - sqrt(0.000511*0.000511 +pow(moment(k),2)));
  return zrho;
}
//-----------------------------------------


Int_t TPart_ident_ct::cut_zrho(Int_t k , Int_t m , Int_t j) {
  c_cut_zrho = 0;
  if (find_zrho(k,m,j) > 0.9) c_cut_zrho = 1;
  
  return c_cut_zrho;
}
//-----------------------------------------
// Double_t  TPart_ident_ct::delta_t_rhomass(Int_t k, Int_t m){
//   if( GetNRows("EVNT")>0 &&  GetNRows("SCPB")>0){ 

//     // THIS FUNCTION HAVE TO BE REDONE
//     Double_t Start_time =  GetHEADER()->GetSTT(); 
//     Double_t Beta_pi = moment(k) / pow((pow(moment(k),2) + pow(0.13957,2)),.5) ;
//     evnt1 = (TEVNTClass*) GetBankRow("EVNT",k);
//     evnt2 = (TEVNTClass*) GetBankRow("EVNT",m); 
//     if(!evnt1) p_delta_t_pi=good1;
//     else {
//       if((evnt1->Scstat)>=1) {
// 	sc_stat=(evnt1->Scstat)-1;
// 	scpb = (TSCPBClass*) GetBankRow("SCPB",sc_stat);
// 	if(!scpb) p_delta_t_pi=good1;
// 	else {
// 	  Double_t tsc=scpb->Time;
// 	  Double_t lsc=scpb->Path;
// 	  p_delta_t_pi =  (tsc-lsc/(Beta_pi*29.978)-Start_time) ;	
// 	}
//       } else p_delta_t_pi=good1;
//     }
//   }
//   return p_delta_t_pi;

// }

//-----------------------------------------



Double_t TPart_ident_ct::px_mc( Int_t k) {
  if( GetNRows("GSIM")>0){
    for (Int_t i = 0 ; i < GetNRows("GSIM") ; i++) {
      gsim = (TGSIMClass*) GetBankRow("GSIM",i);
      if(!gsim) p_px=good1;
      else {
	if ( gsim->GetId() == k) { 
	  p_px= (double)(gsim->GetPx()) ;
	}
      }
    }
  }
  return p_px;
}

//----------------------------------


Double_t TPart_ident_ct::py_mc( Int_t k) {
  if( GetNRows("GSIM")>0){
    for (Int_t i = 0 ; i < GetNRows("GSIM") ; i++) {
      gsim = (TGSIMClass*) GetBankRow("GSIM",i);
      if(!gsim) p_py=good1;
      else {
	if ( gsim->GetId() == k) { 
	  p_py = (double)(gsim->GetPy()) ;
	}
      }
    }
  }
  return p_py;
}

//----------------------------------

Double_t TPart_ident_ct::pz_mc( Int_t k) {
  if( GetNRows("GSIM")>0){
    for (Int_t i = 0 ; i < GetNRows("GSIM") ; i++) {
      gsim = (TGSIMClass*) GetBankRow("GSIM",i);
      if(!gsim) p_pz=good1;
      else {
	if ( gsim->GetId() == k) { 
	  p_pz= (double)(gsim->GetPz()) ;
	}
      }
    }
  }
  return p_pz;
}

//----------------------------------

Double_t TPart_ident_ct::Q2_mc() {

  TVector3 V3_1 , V3_2 ,V3_3;
  V3_1.SetXYZ(px_mc(11),py_mc(11),pz_mc(11));
  V3_2.SetXYZ(0,0,Ebeam);
  V3_3 = V3_2 - V3_1;   // Virtual photon momentum vector
  

  TLorentzVector V4_1(V3_3,(Ebeam - V3_1.Mag())); // Virtual photon quadrimomentum

  p_Q2 = - V4_1 * V4_1; 
  return p_Q2;
}
//------------------------------------

Double_t TPart_ident_ct::moment_mc( Int_t k) {
  p_moment=sqrt(px_mc(k)*px_mc(k)+py_mc(k)*py_mc(k)+pz_mc(k)*pz_mc(k));
  return p_moment;
}
//-----------------------------------

Double_t TPart_ident_ct::nu_mc() {
  p_nu=Ebeam-sqrt(0.000511*0.000511 +pow(moment_mc(11),2));
  return p_nu;
}
//-----------------------------------------


Double_t TPart_ident_ct::W_mc() {
  p_W=sqrt(0.938*0.938+2*0.938*nu_mc()-Q2_mc());
  return p_W;
}
//------------------------------------


Double_t TPart_ident_ct::t_mc() {

  // 11 = electron , -211 = pi- , 211 = pi+



  TVector3 V3_1 , V3_2 ,V3_3;
  V3_1.SetXYZ(px_mc(11),py_mc(11),pz_mc(11));
  V3_2.SetXYZ(0,0,Ebeam);
  V3_3 = V3_2 - V3_1;   // Virtual photon momentum vector
  

  TLorentzVector V4_1(V3_3,(Ebeam - V3_1.Mag())); // Virtual photon quadrimomentum
  V3_1.SetXYZ(px_mc(-211),py_mc(-211),pz_mc(-211));
  V3_2.SetXYZ(px_mc(211),py_mc(211),pz_mc(211));

  TLorentzVector V4_2(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
  TLorentzVector V4_3(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum
  
  
  t_rho = - (V4_1 - V4_2 - V4_3) * (V4_1 - V4_2 - V4_3);

  return t_rho;

}

//-----------------------------------------

Double_t TPart_ident_ct::find_rho_energy_mc() {
  
  rho_energy = sqrt(M_pi*M_pi + pow(moment_mc(211),2)) + sqrt(M_pi*M_pi + pow(moment_mc(-211),2)) ;
  return rho_energy;
}


//-----------------------------------------

Double_t TPart_ident_ct::find_Delta_E_mc() {

  // k = electron     m = pi-    j = pi+  
  Delta_E = nu_mc() - find_rho_energy_mc()  - t_mc()/(2*0.938272);
  Delta_E = fabs(Delta_E);
  return Delta_E;
}



//-----------------------------------------

Double_t TPart_ident_ct::find_zrho_mc() {

  // k = electron     m = pi-    j = pi+  
  zrho  = find_rho_energy_mc() / nu_mc();
  return zrho;
}
//-----------------------------------------


//-----------------------------------------



Double_t TPart_ident_ct::rho_mom_mc() {
  p_mom_rho_mc = sqrt((px_mc(211)+px_mc(-211))*(px_mc(211)+px_mc(-211))+(py_mc(211)+py_mc(-211))*(py_mc(211)+py_mc(-211))+(pz_mc(-211)+pz_mc(211))*(pz_mc(-211)+pz_mc(211)));
  return p_mom_rho_mc;
  


}

//-----------------------------------------

Double_t TPart_ident_ct::theta_pip_mc() {

  p_theta_pip_mc = 0;

  TVector3 V3_e, V3_e2;
  TVector3 V3_1 , V3_2 , V3_3, V3_4;

  V3_e.SetXYZ(0,0,Ebeam); // e beam momentum
  V3_e2.SetXYZ(px_mc(11),py_mc(11),pz_mc(11)); // Scattered electron  
  V3_1.SetXYZ(px_mc(-211),py_mc(-211),pz_mc(-211)); // pi- 3-momentum
  V3_2.SetXYZ(px_mc(211),py_mc(211),pz_mc(211)); // pi+ 3-momentum
  V3_4 = ( V3_e - V3_e2 ) - ( V3_1 + V3_2) ; // outgoing proton
					     // 3-momentum = - t =
					     // gamma* - rho0

  TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
  TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum
  TLorentzVector V4_4(V3_4,sqrt(V3_4.Mag2() + pow(0.938272,2))); // outgoing proton quadrimomentum


  TLorentzVector V4_3 ; // rho momentum
  V4_3 = V4_1 + V4_2; 
  V3_3 = V3_1 + V3_2;

  TVector3 b_3 ; // beta to boost the LAB frame for going in the rho0
		 // rest frame 

  b_3 = V4_3.BoostVector(); // return (px/E,py/E,pz/E) (is all in GeV)

  b_3 = - b_3; // the Boost function in TLorentzVector is an anti-lorentz transform 

  V4_4.Boost(b_3); // proton in the rho0 frame

  V4_2.Boost(b_3); // pi+ in the rho0 frame

  V3_4.SetXYZ(V4_4.Px(),V4_4.Py(),V4_4.Pz()) ; // proton momentum in
					       // the rho0 frame
  V3_2.SetXYZ(V4_2.Px(),V4_2.Py(),V4_2.Pz()) ; // pi+ momentum in
					       // the rho0 frame
  
  p_theta_pip_mc = TMath::Pi() - V3_2.Angle(V3_4) ;  // angle between
						     // the opposite 
						     // of the
						     // direction of
						     // the proton and
						     // the pi+
  
  return p_theta_pip_mc;
  
  
  


}

//-----------------------------------------

Double_t TPart_ident_ct::phi_lep_had_mc() {

  // 11 = electron , -211 = pi- , 211 = pi+

  p_phi_lep_had = 0;

  TVector3 V3_1 , V3_2 ,V3_3 , V3_4, V3_5, V3_6;
  V3_1.SetXYZ(px_mc(11),py_mc(11),pz_mc(11)); // e' momentum
  V3_2.SetXYZ(0,0,Ebeam); // e momentum
  V3_3 = V3_2 - V3_1;   // Virtual photon momentum vector
  V3_4.SetXYZ(px_mc(211),py_mc(211),pz_mc(211)); // pi+ momentum
  V3_5.SetXYZ(px_mc(-211),py_mc(-211),pz_mc(-211)); // pi- momentum
  V3_6 = V3_4 + V3_5; // rho0 momentum


  TVector3 n_lep, n_had;

  n_lep = V3_2.Cross(V3_1);

  n_had = V3_3.Cross(V3_6);

  
  p_phi_lep_had = n_lep.Angle(n_had);

  return p_phi_lep_had;

}

//-----------------------------------------
// Double_t TPart_ident_ct::phi_pip_mc() {
// p_phi_pip_mc = 0;
// 
//   TVector3 V3_1 , V3_2 , V3_3, V3_4;
//   TVector3 V3_e , V3_e2 , V3_g;
// 
//   V3_e.SetXYZ(px_mc(11),py_mc(11),pz_mc(11)); // e' momentum
//   V3_e2.SetXYZ(0,0,Ebeam); // e momentum
// 
//   V3_g = V3_e2 - V3_e;
// 
//   V3_1.SetXYZ(px_mc(-211),py_mc(-211),pz_mc(-211)); // pi- 3-momentum
//   V3_2.SetXYZ(px_mc(211),py_mc(211),pz_mc(211)); // pi+ 3-momentum
//   V3_4.SetXYZ(px_mc(2212),py_mc(2212),pz_mc(2212)); // outgoing proton 3-momentum
// 
//   TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
//   TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum
//   TLorentzVector V4_4(V3_4,sqrt(V3_4.Mag2() + pow(0.938272,2))); // outgoing proton quadrimomentum
// 
// 
//   TLorentzVector V4_3 ; // rho momentum
//   V4_3 = V4_1 + V4_2; 
//   V3_3 = V3_1 + V3_2;
// 
// 
//   TVector3 n_had, n_z, n_x , opip;
// 
//   n_had = V3_g.Cross(V3_3);  // p_gamma* X p_rho    : is parallel to
// 			     //                       the y axis and
// 			     //                       is perpendicular
// 			     //                       to the boost
//                              // it is let unchanged from the boost
// 
//   n_had = n_had.Unit();      // creatin the unit vector in the
// 			     // y direction 
// 
//   TVector3 b_3 ; // beta to boost the LAB frame for going in the rho0
// 		 // rest frame 
// 
//   b_3 = V4_3.BoostVector(); // return (px/E,py/E,pz/E) (is all in GeV)
// 
//   b_3 = - b_3;
// 
//   V4_4.Boost(b_3); // proton in the rho0 frame
// 
//   V4_2.Boost(b_3); // pi+ in the rho0 frame
// 
//   V3_4.SetXYZ(V4_4.Px(),V4_4.Py(),V4_4.Pz()) ; // proton momentum in
// 					       // the rho0 frame
//   V3_2.SetXYZ(V4_2.Px(),V4_2.Py(),V4_2.Pz()) ; // pi+ momentum in
// 					       // the rho0 frame
//   
//   n_z = - V3_4.Unit();  // z axis is opposite to the outgoing proton
//   n_x = n_had.Cross(n_z);  
// 
//   opip = n_z.Cross(V3_2);
// 
//   Double_t sen_phi_mc = asin( - n_x.Dot(opip) / opip.Mag());
// 
//   p_phi_pip_mc = acos(n_had.Dot(opip) / opip.Mag()); // this angle is
// 						     // defined from 0
// 						     // to 2 Pi
//   if (sen_phi_mc < 0 ) {
//     p_phi_pip_mc = 2 * TMath::Pi() - p_phi_pip_mc ;  // if sen (phi)<0
// 						     // phi= 2Pi - phi
// 			     
//   }
//   
//   
//   return p_phi_pip_mc;
//   
// }

Double_t TPart_ident_ct::phi_pip_mc() {

   p_phi_pip_mc = 0;
  
  TVector3 V3_e, V3_e2, V3_g;
  TVector3 V3_1 , V3_2 , V3_3, V3_4;

  V3_e.SetXYZ(0,0,Ebeam); // e beam momentum
  V3_e2.SetXYZ(px_mc(11),py_mc(11),pz_mc(11)); // Scattered electron  
  V3_1.SetXYZ(px_mc(-211),py_mc(-211),pz_mc(-211)); // pi- 3-momentum
  V3_2.SetXYZ(px_mc(211),py_mc(211),pz_mc(211)); // pi+ 3-momentum
  V3_4 = ( V3_e - V3_e2 ) - ( V3_1 + V3_2) ; // outgoing proton
					     // 3-momentum = - t =
					     // gamma* - rho0
  V3_g = V3_e - V3_e2;  // gamma* momentum

  TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
  TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum
  TLorentzVector V4_4(V3_4,sqrt(V3_4.Mag2() + pow(0.938272,2))); // outgoing proton quadrimomentum


  TLorentzVector V4_3 ; // rho momentum
  V4_3 = V4_1 + V4_2; 
  V3_3 = V3_1 + V3_2;


  TVector3 n_had, n_z, n_x , opip;

  n_had = V3_g.Cross(V3_3);  // p_gamma* X p_rho    : is parallel to
			     //                       the y axis and
			     //                       is perpendicular
			     //                       to the boost
                             // it is let unchanged from the boost

  n_had = n_had.Unit();      // creatin the unit vector in the
			     // y direction 

  TVector3 b_3 ; // beta to boost the LAB frame for going in the rho0
		 // rest frame 

  b_3 = V4_3.BoostVector(); // return (px/E,py/E,pz/E) (is all in GeV)

  b_3 = - b_3;

  V4_4.Boost(b_3); // proton in the rho0 frame

  V4_2.Boost(b_3); // pi+ in the rho0 frame

  V3_4.SetXYZ(V4_4.Px(),V4_4.Py(),V4_4.Pz()) ; // proton momentum in
					       // the rho0 frame
  V3_2.SetXYZ(V4_2.Px(),V4_2.Py(),V4_2.Pz()) ; // pi+ momentum in
					       // the rho0 frame
  
  n_z = - V3_4.Unit();  // z axis is opposite to the outgoing proton
  n_x = n_had.Cross(n_z); // x axis = (y axis) X (z axis)  

  opip = n_z.Cross(V3_2);

  Double_t sen_phi_ev = asin( - n_x.Dot(opip) / opip.Mag());

  p_phi_pip_mc = acos(n_had.Dot(opip) / opip.Mag()); // this angle is
						     // defined from 0
						     // to 2 Pi
  if (sen_phi_ev < 0 ) {
    p_phi_pip_mc = 2 * TMath::Pi() - p_phi_pip_mc ;  // if sen (phi)<0
						     // phi= 2Pi - phi
			     
  }
   
  
  return p_phi_pip_mc;
  
  


}

//-----------------------------------------


Double_t TPart_ident_ct::rho_mom_ev(Int_t k , Int_t m) { 

  // k = pi+     m = pi-

  evnt1 = (TEVNTClass*) GetBankRow("EVNT",k);
  evnt2 = (TEVNTClass*) GetBankRow("EVNT",m);


  TVector3 V3_1 , V3_2 ,V3_3;
  V3_1 = (evnt1->GetMomVec());
  V3_2 = (evnt2->GetMomVec());
  V3_3 = V3_1 + V3_2;
  p_mom_rho_ev = V3_3.Mag();


  return p_mom_rho_ev;
  
}

//-----------------------------------------

Double_t TPart_ident_ct::theta_pip_ev(Int_t k , Int_t m, Int_t j) {

  p_theta_pip_ev = 0;

  // k = e-     m = pi-    j = pi+

  evnt1 = (TEVNTClass*) GetBankRow("EVNT",k);
  evnt2 = (TEVNTClass*) GetBankRow("EVNT",m);
  evnt3 = (TEVNTClass*) GetBankRow("EVNT",j);



  TVector3 V3_e, V3_e2;
  TVector3 V3_1 , V3_2 , V3_3, V3_4;

  V3_e.SetXYZ(0,0,Ebeam); // e beam momentum
  V3_e2 = (evnt1->GetMomVec()); // Scattered electron  
  V3_1 = (evnt2->GetMomVec()); // pi- 3-momentum
  V3_2 = (evnt3->GetMomVec()); // pi+ 3-momentum
  V3_4 = ( V3_e - V3_e2 ) - ( V3_1 + V3_2) ; // outgoing proton
					     // 3-momentum = - t =
					     // gamma* - rho0

  TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
  TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum
  TLorentzVector V4_4(V3_4,sqrt(V3_4.Mag2() + pow(0.938272,2))); // outgoing proton quadrimomentum


  TLorentzVector V4_3 ; // rho momentum
  V4_3 = V4_1 + V4_2; 
  V3_3 = V3_1 + V3_2;

  TVector3 b_3 ; // beta to boost the LAB frame for going in the rho0
		 // rest frame 

  b_3 = V4_3.BoostVector(); // return (px/E,py/E,pz/E) (is all in GeV)

  b_3 = - b_3; // the Boost function in TLorentzVector is an anti-lorentz transform 

  V4_4.Boost(b_3); // proton in the rho0 frame

  V4_2.Boost(b_3); // pi+ in the rho0 frame

  V3_4.SetXYZ(V4_4.Px(),V4_4.Py(),V4_4.Pz()) ; // proton momentum in
					       // the rho0 frame
  V3_2.SetXYZ(V4_2.Px(),V4_2.Py(),V4_2.Pz()) ; // pi+ momentum in
					       // the rho0 frame
  
  p_theta_pip_ev = TMath::Pi() - V3_2.Angle(V3_4) ;  // angle between
						     // the opposite 
						     // of the
						     // direction of
						     // the proton and
						     // the pi+
  
  return p_theta_pip_ev;

}


Double_t TPart_ident_ct::phi_lep_had_ev(Int_t k , Int_t m, Int_t j) {


  // k = e-     m = pi-    j = pi+

  evnt1 = (TEVNTClass*) GetBankRow("EVNT",k);
  evnt2 = (TEVNTClass*) GetBankRow("EVNT",m);
  evnt3 = (TEVNTClass*) GetBankRow("EVNT",j);



  TVector3 V3_e, V3_e2;
  TVector3 V3_1 , V3_2 , V3_3, V3_4;

  V3_e.SetXYZ(0,0,Ebeam); // e beam momentum
  V3_e2 = (evnt1->GetMomVec()); // Scattered electron  
  V3_1 = (evnt2->GetMomVec()); // pi- 3-momentum
  V3_2 = (evnt3->GetMomVec()); // pi+ 3-momentum
  V3_3 = V3_e - V3_e2; // Virtual photon momentum vector
  V3_4 = V3_1 + V3_2 ; // rho momentum
					   


  TVector3 n_lep, n_had;

  n_lep = V3_e.Cross(V3_e2);

  n_had = V3_3.Cross(V3_4);

  
  p_phi_lep_had = n_lep.Angle(n_had);

  return p_phi_lep_had;

}

//-----------------------------------------



Double_t TPart_ident_ct::phi_pip_ev(Int_t k , Int_t m, Int_t j) {

  p_phi_pip_ev = 0;

  // k = e-     m = pi-    j = pi+

  evnt1 = (TEVNTClass*) GetBankRow("EVNT",k);
  evnt2 = (TEVNTClass*) GetBankRow("EVNT",m);
  evnt3 = (TEVNTClass*) GetBankRow("EVNT",j);



  TVector3 V3_e, V3_e2, V3_g;
  TVector3 V3_1 , V3_2 , V3_3, V3_4;

  V3_e.SetXYZ(0,0,Ebeam); // e beam momentum
  V3_e2 = (evnt1->GetMomVec()); // Scattered electron  
  V3_1 = (evnt2->GetMomVec()); // pi- 3-momentum
  V3_2 = (evnt3->GetMomVec()); // pi+ 3-momentum
  V3_4 = ( V3_e - V3_e2 ) - ( V3_1 + V3_2) ; // outgoing proton
					     // 3-momentum = - t =
					     // gamma* - rho0
  V3_g = V3_e - V3_e2;  // gamma* momentum

  TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
  TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum
  TLorentzVector V4_4(V3_4,sqrt(V3_4.Mag2() + pow(0.938272,2))); // outgoing proton quadrimomentum


  TLorentzVector V4_3 ; // rho momentum
  V4_3 = V4_1 + V4_2; 
  V3_3 = V3_1 + V3_2;


  TVector3 n_had, n_z, n_x , opip;

  n_had = V3_g.Cross(V3_3);  // p_gamma* X p_rho    : is parallel to
			     //                       the y axis and
			     //                       is perpendicular
			     //                       to the boost
                             // it is let unchanged from the boost

  n_had = n_had.Unit();      // creatin the unit vector in the
			     // y direction 

  TVector3 b_3 ; // beta to boost the LAB frame for going in the rho0
		 // rest frame 

  b_3 = V4_3.BoostVector(); // return (px/E,py/E,pz/E) (is all in GeV)

  b_3 = - b_3;

  V4_4.Boost(b_3); // proton in the rho0 frame

  V4_2.Boost(b_3); // pi+ in the rho0 frame

  V3_4.SetXYZ(V4_4.Px(),V4_4.Py(),V4_4.Pz()) ; // proton momentum in
					       // the rho0 frame
  V3_2.SetXYZ(V4_2.Px(),V4_2.Py(),V4_2.Pz()) ; // pi+ momentum in
					       // the rho0 frame
  
  n_z = - V3_4.Unit();  // z axis is opposite to the outgoing proton
  n_x = n_had.Cross(n_z); // x axis = (y axis) X (z axis)  

  opip = n_z.Cross(V3_2);

  Double_t sen_phi_ev = asin( - n_x.Dot(opip) / opip.Mag());

  p_phi_pip_ev = acos(n_had.Dot(opip) / opip.Mag()); // this angle is
						     // defined from 0
						     // to 2 Pi
  if (sen_phi_ev < 0 ) {
    p_phi_pip_ev = 2 * TMath::Pi() - p_phi_pip_ev ;  // if sen (phi)<0
						     // phi= 2Pi - phi
			     
  }
  
  return p_phi_pip_ev;


}
//-----------------------------------------

Int_t TPart_ident_ct::id_mc() {
  Int_t p_id_mc = 0;

  if ( GetHEADER()->NRun == 10 &&  GetNRows("MCHD")>0) {  // simulation runs have runnnumber =10
				// , data files different
    mchd = (TMCHDClass*) GetBankRow("MCHD",0);
    p_id_mc = mchd->GetNrun() ;
  }

  return p_id_mc;
}


//-----------------------------------------


Double_t TPart_ident_ct::invariant_mass_mc() {

  TVector3 V3_1 , V3_2; 

  V3_1.SetXYZ(px_mc(-211),py_mc(-211),pz_mc(-211)); // pi- 3-momentum
  V3_2.SetXYZ(px_mc(211),py_mc(211),pz_mc(211)); // pi+ 3-momentum

  TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(M_pi,2)));
  TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(M_pi,2))); 
  
  inv_mass =sqrt((V4_1 + V4_2) * (V4_1 + V4_2));

  return inv_mass;

}

//-----------------------------------------
Double_t TPart_ident_ct::Get_lc_mc() {
 p_lc = 2 * nu_mc() / (Q2_mc() + pow(invariant_mass_mc(),2));
  return p_lc;
}
//-----------------------------------------


Double_t TPart_ident_ct::theta_lam_mc() {
  
  p_theta_pip_mc = 0;
  TVector3 V3_1 , V3_2 , V3_3 , V3_4 , V3_5;
  
  
  V3_1.SetXYZ(px_mc(-211),py_mc(-211),pz_mc(-211)); // pi- 3-momentum
  V3_2.SetXYZ(px_mc(211),py_mc(211),pz_mc(211)); // pi+ 3-momentum
  
  TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
  TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum  
  
  TLorentzVector V4_3 ; // rho momentum
  V4_3 = V4_1 + V4_2; 
  V3_3 = V3_1 + V3_2;
  
  Double_t th = V3_3.Theta(); // theta rho
  Double_t ph = V3_3.Phi(); // phi rho
  
  //rotated coordinate frame with z with rho0 for the pi+
  Double_t ppx = V3_2.X() * cos(th) * cos(ph) + V3_2.Y() * cos(th)* sin(ph) - V3_2.Z() * sin(th);
  Double_t ppy = - V3_2.X() * sin(ph) + V3_2.Y() * cos(ph);
  Double_t ppz = V3_2.X() * sin(th) * cos(ph) + V3_2.Y() * sin(th)* sin(ph) + V3_2.Z() * cos(th);
  V3_4.SetXYZ(ppx,ppy,ppz); 
  TLorentzVector V4_4(V3_4,(V4_2.E())); // pi+ 4 momentum in rho0->z frame
  
  Double_t gamma = V4_3.E() / V4_3.M();
  Double_t gammabeta = sqrt(pow(V4_3.Px(),2) + pow(V4_3.Py(),2) + pow(V4_3.Pz(),2) ) / V4_3.M();
  
  V3_5.SetXYZ(V4_4.Px(),V4_4.Py(),(gamma * V4_4.Pz() - gammabeta * V4_4.E())); 
  
  p_theta_pip_mc = V3_5.Theta();
  return  p_theta_pip_mc ;
}

//-----------------------------------------

Double_t TPart_ident_ct::phi_lam_mc() {
  
  p_phi_pip_mc = 0;
  TVector3 V3_1 , V3_2 , V3_3 , V3_4 , V3_5;
  
  
  V3_1.SetXYZ(px_mc(-211),py_mc(-211),pz_mc(-211)); // pi- 3-momentum
  V3_2.SetXYZ(px_mc(211),py_mc(211),pz_mc(211)); // pi+ 3-momentum
  
  TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
  TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum  
  
  TLorentzVector V4_3 ; // rho momentum
  V4_3 = V4_1 + V4_2; 
  V3_3 = V3_1 + V3_2;
  
  Double_t th = V3_3.Theta(); // theta rho
  Double_t ph = V3_3.Phi(); // phi rho
  
  //rotated coordinate frame with z with rho0 for the pi+
  Double_t ppx = V3_2.X() * cos(th) * cos(ph) + V3_2.Y() * cos(th)* sin(ph) - V3_2.Z() * sin(th);
  Double_t ppy = - V3_2.X() * sin(ph) + V3_2.Y() * cos(ph);
  Double_t ppz = V3_2.X() * sin(th) * cos(ph) + V3_2.Y() * sin(th)* sin(ph) + V3_2.Z() * cos(th);
  V3_4.SetXYZ(ppx,ppy,ppz); 
  TLorentzVector V4_4(V3_4,(V4_2.E())); // pi+ 4 momentum in rho0->z frame
  
  Double_t gamma = V4_3.E() / V4_3.M();
  Double_t gammabeta = sqrt(pow(V4_3.Px(),2) + pow(V4_3.Py(),2) + pow(V4_3.Pz(),2) ) / V4_3.M();
  
  V3_5.SetXYZ(V4_4.Px(),V4_4.Py(),(gamma * V4_4.Pz() - gammabeta * V4_4.E())); 
  
  p_phi_pip_mc = V3_5.Phi();
  return  p_phi_pip_mc ;
}

//-----------------------------------------

Double_t TPart_ident_ct::theta_lam_ev(Int_t m, Int_t j) {
  
  p_theta_pip_ev = 0;
  TVector3 V3_1 , V3_2 , V3_3 , V3_4 , V3_5;
  
  evnt2 = (TEVNTClass*) GetBankRow("EVNT",m);
  evnt3 = (TEVNTClass*) GetBankRow("EVNT",j);

  V3_1 = (evnt2->GetMomVec()); // pi- 3-momentum
  V3_2 = (evnt3->GetMomVec()); // pi+ 3-momentum
   
  TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
  TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum  
  
  TLorentzVector V4_3 ; // rho momentum
  V4_3 = V4_1 + V4_2; 
  V3_3 = V3_1 + V3_2;
  
  Double_t th = V3_3.Theta(); // theta rho
  Double_t ph = V3_3.Phi(); // phi rho
  
  //rotated coordinate frame with z with rho0 for the pi+
  Double_t ppx = V3_2.X() * cos(th) * cos(ph) + V3_2.Y() * cos(th)* sin(ph) - V3_2.Z() * sin(th);
  Double_t ppy = - V3_2.X() * sin(ph) + V3_2.Y() * cos(ph);
  Double_t ppz = V3_2.X() * sin(th) * cos(ph) + V3_2.Y() * sin(th)* sin(ph) + V3_2.Z() * cos(th);
  V3_4.SetXYZ(ppx,ppy,ppz); 
  TLorentzVector V4_4(V3_4,(V4_2.E())); // pi+ 4 momentum in rho0->z frame
  
  Double_t gamma = V4_3.E() / V4_3.M();
  Double_t gammabeta = sqrt(pow(V4_3.Px(),2) + pow(V4_3.Py(),2) + pow(V4_3.Pz(),2) ) / V4_3.M();
  
  V3_5.SetXYZ(V4_4.Px(),V4_4.Py(),(gamma * V4_4.Pz() - gammabeta * V4_4.E())); 
  
  p_theta_pip_ev = V3_5.Theta();
  return  p_theta_pip_ev ;
}

//-----------------------------------------

Double_t TPart_ident_ct::phi_lam_ev(Int_t m, Int_t j) {
  
  p_phi_pip_ev = 0;
  TVector3 V3_1 , V3_2 , V3_3 , V3_4 , V3_5;
  
    
  evnt2 = (TEVNTClass*) GetBankRow("EVNT",m);
  evnt3 = (TEVNTClass*) GetBankRow("EVNT",j);

  V3_1 = (evnt2->GetMomVec()); // pi- 3-momentum
  V3_2 = (evnt3->GetMomVec()); // pi+ 3-momentum
    
  TLorentzVector V4_1(V3_1,sqrt(V3_1.Mag2() + pow(0.13957,2))); // pi- quadrimomentum
  TLorentzVector V4_2(V3_2,sqrt(V3_2.Mag2() + pow(0.13957,2))); // pi+ quadrimomentum  
  
  TLorentzVector V4_3 ; // rho momentum
  V4_3 = V4_1 + V4_2; 
  V3_3 = V3_1 + V3_2;
  
  Double_t th = V3_3.Theta(); // theta rho
  Double_t ph = V3_3.Phi(); // phi rho
  
  //rotated coordinate frame with z with rho0 for the pi+
  Double_t ppx = V3_2.X() * cos(th) * cos(ph) + V3_2.Y() * cos(th)* sin(ph) - V3_2.Z() * sin(th);
  Double_t ppy = - V3_2.X() * sin(ph) + V3_2.Y() * cos(ph);
  Double_t ppz = V3_2.X() * sin(th) * cos(ph) + V3_2.Y() * sin(th)* sin(ph) + V3_2.Z() * cos(th);
  V3_4.SetXYZ(ppx,ppy,ppz); 
  TLorentzVector V4_4(V3_4,(V4_2.E())); // pi+ 4 momentum in rho0->z frame
  
  Double_t gamma = V4_3.E() / V4_3.M();
  Double_t gammabeta = sqrt(pow(V4_3.Px(),2) + pow(V4_3.Py(),2) + pow(V4_3.Pz(),2) ) / V4_3.M();
  
  V3_5.SetXYZ(V4_4.Px(),V4_4.Py(),(gamma * V4_4.Pz() - gammabeta * V4_4.E())); 
  
  p_phi_pip_ev = V3_5.Phi();
  return  p_phi_pip_ev ;
}

//---------------------------------------------

Int_t TPart_ident_ct::Run_Number() {
    c_runnum =  GetHEADER()->NRun;   
    if(!c_runnum) p_runnum=good1;  
    p_runnum=c_runnum;
    return p_runnum; 
}


//------------------------------------------
Double_t TPart_ident_ct::sc_X() {
  if( GetNRows("EVNT")>0 &&  GetNRows("DCPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",0);
    if(!evnt) p_sc_X=good1;
    else {
      if((evnt->Dcstat)>=1) {
      dc_stat=(evnt->Dcstat)-1;
      dcpb = (TDCPBClass*) GetBankRow("DCPB",dc_stat);
      if(!dcpb) p_sc_X=good1;
      else
	p_sc_X=dcpb->X_sc;
      } else p_sc_X=good1;
    }
  }
  return p_sc_X;
}

//------------------------------------------
Double_t TPart_ident_ct::sc_Y() {
  if( GetNRows("EVNT")>0 &&  GetNRows("DCPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",0);
    if(!evnt) p_sc_Y=good1;
    else {
      if((evnt->Dcstat)>=1) {
      dc_stat=(evnt->Dcstat)-1;
      dcpb = (TDCPBClass*) GetBankRow("DCPB",dc_stat);
      if(!dcpb) p_sc_Y=good1;
      else
	p_sc_Y=dcpb->Y_sc;
      } else p_sc_Y=good1;
    }
  }
  return p_sc_Y;
}

//------------------------------------------
Double_t TPart_ident_ct::sc_Z() {
  if( GetNRows("EVNT")>0 &&  GetNRows("DCPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",0);
    if(!evnt) p_sc_Z=good1;
    else {
      if((evnt->Dcstat)>=1) {
      dc_stat=(evnt->Dcstat)-1;
      dcpb = (TDCPBClass*) GetBankRow("DCPB",dc_stat);
      if(!dcpb) p_sc_Z=good1;
      else
	p_sc_Z=dcpb->Z_sc;
      } else p_sc_Z=good1;
    }
  }
  return p_sc_Z;
}


//------------------------------------------
Double_t TPart_ident_ct::sc_CX() {
  if( GetNRows("EVNT")>0 &&  GetNRows("DCPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",0);
    if(!evnt) p_sc_CX=good1;
    else {
      if((evnt->Dcstat)>=1) {
      dc_stat=(evnt->Dcstat)-1;
      dcpb = (TDCPBClass*) GetBankRow("DCPB",dc_stat);
      if(!dcpb) p_sc_CX=good1;
      else
	p_sc_CX=dcpb->Cx_sc;
      } else p_sc_CX=good1;
    }
  }
  return p_sc_CX;
}

//------------------------------------------
Double_t TPart_ident_ct::sc_CY() {
  if( GetNRows("EVNT")>0 &&  GetNRows("DCPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",0);
    if(!evnt) p_sc_CY=good1;
    else {
      if((evnt->Dcstat)>=1) {
      dc_stat=(evnt->Dcstat)-1;
      dcpb = (TDCPBClass*) GetBankRow("DCPB",dc_stat);
      if(!dcpb) p_sc_CY=good1;
      else
	p_sc_CY=dcpb->Cy_sc;
      } else p_sc_CY=good1;
    }
  }
  return p_sc_CY;
}

//------------------------------------------
Double_t TPart_ident_ct::sc_CZ() {
  if( GetNRows("EVNT")>0 &&  GetNRows("DCPB")>0){
    evnt = (TEVNTClass*) GetBankRow("EVNT",0);
    if(!evnt) p_sc_CZ=good1;
    else {
      if((evnt->Dcstat)>=1) {
      dc_stat=(evnt->Dcstat)-1;
      dcpb = (TDCPBClass*) GetBankRow("DCPB",dc_stat);
      if(!dcpb) p_sc_CZ=good1;
      else
	p_sc_CZ=dcpb->Cz_sc;
      } else p_sc_CZ=good1;
    }
  }
  return p_sc_CZ;
}

