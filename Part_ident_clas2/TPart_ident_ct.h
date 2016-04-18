#ifndef __TPart_ident_ct__
#define __TPart_ident_ct__


#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/THEADERClass.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TClasTool.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TDSTReader.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TEVNTClass.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TCCPBClass.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TECPBClass.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TSCPBClass.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TGSIMClass.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TMCHDClass.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TDCPBClass.h"
using namespace std;


class TPart_ident_ct: public TClasTool{

  protected:
  Int_t cc_stat;
  Int_t ec_stat;
  Int_t sc_stat;
  Int_t sc_stat1;
  Int_t dc_stat;
  Int_t p_stat_cc;
  Int_t p_stat_sc;
  Int_t p_stat_dc;
  Int_t p_stat_ec;
  Double_t p_betta;
  Double_t p_betta_alt;
  Double_t p_delta_betta;
  Double_t p_px;
  Double_t p_py;
  Double_t p_pz;
  Double_t p_moment;
  Double_t p_mass2;
  Double_t p_theta;
  Double_t p_theta_virt;
  Double_t p_phi;
  Double_t p_phi_virt;
  Double_t p_phi_cut;
  Double_t p_Q2;
  Double_t p_W;
  Double_t p_lc;
  Double_t p_pt2;
  Double_t p_theta_pq;
  Double_t p_Z_pi;
  Double_t p_Z_pi_zero;
  Double_t p_nphe;
  Double_t p_x;
  Double_t p_y;
  Double_t p_z;
  Double_t p_chi2cc;
  Double_t p_nu;
  Double_t p_id;
  Double_t p_status;
  Double_t p_cc_status;
  Double_t p_ec_status;
  Double_t p_dc_status;
  Double_t p_charge;
  Double_t p_ec_X;
  Double_t p_ec_Y;
  Double_t p_ec_Z;
  Double_t p_etot;
  Double_t p_ein;
  Double_t p_eout;
  Double_t p_uvw;
  Bool_t p_mine_eccut;
  Bool_t p_ieccut;
  Int_t p_sector_alt;
  Int_t p_vertex_cut_elec;
  Bool_t p_vertex_cut_pion;
  Double_t p_m2;
  Double_t p_m3;
  Double_t p_m4;
  Float_t p_rf1;
  Float_t p_nevent;
  Int_t c_nphecut;
  Float_t p_fcg;
  Int_t c_fcgcut;
  Int_t c_deltabetacut;
  Double_t inv_mass;
  Double_t t_rho;
  Double_t rho_energy;
  Double_t Delta_E;
  Double_t zrho;
  Int_t c_cut_t_rho;
  Int_t c_cut_zrho;
  Double_t p_delta_t_pi;
  Int_t c_delta_t_pip;
  Int_t c_delta_t_pim;
  Int_t c_vertex_cut_mine;
  Int_t p_id_mc;
  Double_t p_lc_mc;	
  Double_t p_mom_rho_mc;
  Double_t p_phi_lep_had;
  Double_t p_theta_pip_mc;
  Double_t p_phi_pip_mc;
  Double_t p_mom_rho_ev;
  Double_t p_theta_pip_ev;
  Double_t p_phi_pip_ev;
  Int_t p_runnum;
  Int_t c_runnum;
  Double_t p_sc_X;
  Double_t p_sc_Y;
  Double_t p_sc_Z;
  Double_t p_sc_CX;
  Double_t p_sc_CY;
  Double_t p_sc_CZ;


  Int_t good;
  const Double_t Ebeam;
  const Double_t M_pi;


  TEVNTClass *evnt;
  TEVNTClass *evnt1;
  TEVNTClass *evnt2;
  TEVNTClass *evnt3;
  TCCPBClass *ccpb;
  TECPBClass *ecpb;
  TSCPBClass *scpb;
  TSCPBClass *scpb1;
  TDCPBClass *dcpb;
  TGSIMClass *gsim;
  TMCHDClass *mchd;
  Float_t header;
  //TVector3 V3p;

 public:
  const Int_t good1;

 public:
  TPart_ident_ct();
  Double_t betta( Int_t);
  Double_t betta_alt( Int_t);
  Double_t delta_betta( Int_t);
  Double_t px( Int_t);
  Double_t py( Int_t);
  Double_t pz( Int_t);
  Double_t moment( Int_t);
  Double_t mass2( Int_t);
  Double_t theta( Int_t);
  Double_t theta_virt();
  Double_t Q2();
  Double_t W( );
  Double_t pt2( Int_t);
  Double_t cos_theta_pq( Int_t);
  Double_t Z_pi( Int_t);
  Double_t Z_pi_zero( Int_t);
  Double_t nphe( Int_t);
  Double_t x( Int_t);
  Double_t y( Int_t);
  Double_t z(  Int_t);
  Double_t chi2cc( Int_t);
  Double_t nu();
  Double_t Get_lc(Int_t, Int_t );
  Double_t id( Int_t);
  Double_t status( Int_t);
  Double_t cc_status( Int_t);
  Double_t ec_status( Int_t);
  Double_t dc_status( Int_t);
  Double_t charge( Int_t);
  Int_t stat_cc( Int_t);
  Int_t stat_sc( Int_t);
  Int_t stat_dc( Int_t);
  Int_t stat_ec( Int_t);
  Double_t ec_X( Int_t);
  Double_t ec_Y( Int_t);
  Double_t ec_Z( Int_t);
  Double_t etot( Int_t);
  Double_t ein( Int_t);
  Double_t eout( Int_t);
  Double_t uvw( Int_t, Int_t);
  Bool_t pfid_ecinout( Int_t);
  Int_t sector_alt(  Int_t);
  Int_t vertex_cut_elec( );
  Int_t vertex_cut_pion( Int_t);
  Int_t vertex_cut_proton( Int_t);
  Double_t M2( Int_t);
  Double_t M3(  Int_t);
  Double_t M4(  Int_t);
  Double_t phi( Int_t);
  Double_t phi_virt();
  Double_t phi_cut( Int_t);
  Float_t rf1( );
  Float_t nevent();
  Int_t Good_evnt( Int_t);
  Int_t Good_ccpb( Int_t);
  Int_t Good_ecpb( Int_t);
  Bool_t nphecut(  Int_t);
  Bool_t nphecut_pi( Int_t);
  Float_t fcg_value();
  Int_t fcg_cut();
  Int_t deltabeta_cut(Int_t);
  Double_t invariant_mass(Int_t, Int_t );
  Double_t find_t_rho(Int_t  , Int_t  , Int_t );
  Double_t find_rho_energy(Int_t , Int_t );
  Double_t find_Delta_E(Int_t  , Int_t  , Int_t );
  Double_t find_zrho(Int_t , Int_t , Int_t );
  Int_t cut_t_rho(Int_t  , Int_t  , Int_t );
  Int_t cut_zrho(Int_t  , Int_t  , Int_t );
  Double_t delta_t_rhomass(Int_t, Int_t);

  //my cuts extra
  Bool_t mine_eccut( Int_t ); 
  Double_t delta_t_pi(Int_t );
  Double_t delta_t_proton(Int_t );
  Int_t vertex_cut_mine( Int_t , Int_t );
  Int_t vertex_cut_el_mine();
  Int_t delta_t_pip_cut(Int_t );
  Int_t delta_t_pim_cut(Int_t ); 
  Int_t delta_t_proton_cut(Int_t );

  //inline functions for FID_CUTS
  Double_t fid_theta( Int_t);
  Double_t fid_phi( Int_t);
  Int_t fid_sector( Int_t);

  //FOR ELECTRON
  Double_t fid_theta_min( );
  Double_t fid_func(  Int_t, Int_t);
  Double_t fid_phi_min( );
  Double_t fid_phi_max( );
  Bool_t fid_CheckCut( );

  //FOR PI+
  Double_t fid_theta_min_pip( Int_t);
  Double_t fid_func_pip(  Int_t, Int_t, Int_t);
  Double_t fid_phi_min_pip( Int_t);
  Double_t fid_phi_max_pip(  Int_t);
  Bool_t fid_CheckCut_pip(  Int_t);

  //Functions for Montecarlo generated data
  Double_t px_mc( Int_t);
  Double_t py_mc( Int_t);
  Double_t pz_mc( Int_t); 
  Double_t Q2_mc();
  Double_t moment_mc( Int_t);
  Double_t nu_mc();
  Double_t W_mc();
  Double_t t_mc();
  Double_t Get_lc_mc();
  Double_t find_rho_energy_mc();
  Double_t find_Delta_E_mc();
  Double_t find_zrho_mc();
  Double_t rho_mom_mc();
  Double_t theta_pip_mc();
  Double_t phi_pip_mc();
  Double_t phi_lep_had_mc();
  Double_t invariant_mass_mc();
  Int_t id_mc();
  Double_t theta_lam_mc();
  Double_t phi_lam_mc();


  // Extra Function for calculating the acceptance
  Double_t rho_mom_ev(Int_t , Int_t);
  Double_t theta_pip_ev(Int_t, Int_t, Int_t);
  Double_t phi_pip_ev(Int_t, Int_t, Int_t);
  Double_t phi_lep_had_ev(Int_t, Int_t, Int_t);
  Double_t theta_lam_ev(Int_t, Int_t);
  Double_t phi_lam_ev(Int_t, Int_t);
  
  
  //Extra Function for determining the CC Efficiency
  Int_t Run_Number();
  Double_t sc_X();
  Double_t sc_Y();
  Double_t sc_Z();
  Double_t sc_CX();
  Double_t sc_CY();
  Double_t sc_CZ();


};


#endif
