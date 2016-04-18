//////////////////////////////////////////////////////////////////////
// 
// TPart_id.h
//
//////////////////////////////////////////////////////////////////////

#ifndef __TPart_id__
#define __TPart_id__

#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TClasTool.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TCounterCol.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/include/TInterrupt.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TStopwatch.h"
#include "TCollection.h"
#include "TTree.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/My_analysis/Part_ident_clas2/TPart_ident_ct.h"

class TPart_id: public TPart_ident_ct{

 public:

  Int_t gFix_EC_Bank;

  TCounterCol Cuts;  // Keep track of stuff.

  TInterrupt *Interrupt;
  TStopwatch *Time;
  TObjArray  *Hpid; //Stores histogram objects for operations on all histos.
  TObjArray  *Hkin;
  TObjArray  *Hrho;  
  TObjArray  *Acc_gen; 
  TObjArray  *Acc_rec;
  TObjArray  *Acc_acc; 

  Char_t Title1[60];
  Char_t Title2[60];


  //flag for kinematical analysys
  Double_t mass_rho;
  Double_t rho_mass;
  Double_t ghost_z;
  Double_t ghost_p;
  Int_t which_target;
  Int_t which_pip;
  Int_t which_pim;
  Int_t electron_id_pass;
  Int_t pip_id_pass;
  Int_t pim_id_pass;
  Int_t proton_id_pass;
  Int_t positron_id_pass;
  Int_t second_electron_id_pass;
  Int_t npart_pass;

  // flag for id cuts
  Int_t electron_id_cut;
  Int_t positron_id_cut;
  Int_t second_electron_id_cut;
  Int_t pip_id_cut;
  Int_t pim_id_cut;
  Int_t proton_id_cut;
  Int_t electron_id_pos;
  Int_t pip_id_pos[6];
  Int_t pim_id_pos[6];
  Int_t proton_id_pos[20];
  Int_t good_event_towrite;

  // Acceptance Arrays

  Int_t Acc_Q2_g;
  Int_t Acc_W_g;
  Int_t Acc_t_g;
  Int_t Acc_deltaE_g;
  Int_t Acc_z_g;
  Int_t Acc_thetapip_g;
  Int_t Acc_id_g;
  Int_t Acc_tg_g;
  Double_t Acc_massrho_g;
  Double_t Acc_Q2_g_v;
  Double_t Acc_W_g_v;
  Double_t Acc_t_g_v;
  Double_t Acc_deltaE_g_v;
  Double_t Acc_rhomom_g_v;
  Double_t Acc_z_g_v;
  Double_t Acc_thetapip_g_v;  
  Double_t Acc_lc_g_v;
  
  Int_t Acc_Q2_r;
  Int_t Acc_W_r;
  Int_t Acc_t_r;
  Int_t Acc_deltaE_r;
  Int_t Acc_z_r;
  Int_t Acc_thetapip_r;
  Int_t Acc_id_r;
  Int_t Acc_tg_r;
  Double_t Acc_massrho_r;
  Double_t Acc_Q2_r_v;
  Double_t Acc_W_r_v;
  Double_t Acc_t_r_v;
  Double_t Acc_deltaE_r_v;
  Double_t Acc_rhomom_r_v;
  Double_t Acc_z_r_v;
  Double_t Acc_thetapip_r_v;
  Double_t Acc_lc_r_v;


  Double_t rec_pim_E;
  Double_t rec_pim_px;
  Double_t rec_pim_py;
  Double_t rec_pim_pz;
  Double_t rec_el_E;
  Double_t rec_el_px;
  Double_t rec_el_py;
  Double_t rec_el_pz;
  Double_t rec_pr_E;
  Double_t rec_pr_px;
  Double_t rec_pr_py;
  Double_t rec_pr_pz;


  
  // CC Efficiency Arrays
  Double_t CC_theta_ev;
  Double_t CC_phi_ev;
  Double_t CC_mom_ev;
  Double_t CC_eff_ev;

/*   TH1F  *mc_gen[3][3][2][4][6][6][3];  // binning for the mc generated */
/*   TH1F  *mc_rec[3][3][2][4][6][6][3];  // binning for the reconstructed	       *\/ */
/*   TH1F  *mc_acc[3][3][2][4][6][6][3];  // binning for the reconstructed   *\/ */
/*   TH1F  *mc_temp_ar[3][3][2][4][6][6][3];  // temporary array *\/ */



/*   TArray_7 *mc_gen;  // binning for the mc generated */
/*   TArray_7 *mc_rec;  // binning for the reconstructed	       */
/*   TArray_7 *mc_acc;  // binning for the reconstructed   */
/*   TArray_7 *mc_temp_ar;  // temporary array */

  // Store indexes for the counters.
  Int_t C_nopart;
  Int_t C_el_status;
  Int_t C_el_stat_cc;
  Int_t C_el_stat_sc;
  Int_t C_el_stat_dc;
  Int_t C_el_stat_ec;
  Int_t C_el_ecstatus;
  Int_t C_el_u;
  Int_t C_el_v;
  Int_t C_el_w;
  Int_t C_el_FCG;
  Int_t C_el_EoEi;
  Int_t C_el_Nphe;
  Int_t C_el_charge;
  Int_t C_el_z;
  Int_t C_Goodpart;
  Int_t C_Good_e;
  Int_t C_Good_pim;
  Int_t C_Good_pip;
  Int_t C_Good_proton;
  Int_t C_Good_kin;

  Int_t C_second_el;

  Int_t C_pos_status;
  Int_t C_pos_stat_cc;
  Int_t C_pos_stat_sc;
  Int_t C_pos_stat_dc;
  Int_t C_pos_stat_ec;
  Int_t C_pos_ecstatus;
  Int_t C_pos_u;
  Int_t C_pos_v;
  Int_t C_pos_w;
  Int_t C_pos_FCG;
  Int_t C_pos_EoEi;
  Int_t C_pos_Nphe;
  Int_t C_pos_charge;
  Int_t C_pos_z;
  Int_t C_Good_pos;

  Int_t C_EC_error;
  Int_t C_EC_err_fix1;
  Int_t C_EC_err_fix2;

  Int_t C_pip_status;
  Int_t C_pip_stat_sc;
  Int_t C_pip_stat_dc;
  Int_t C_pip_charge;
  Int_t C_pip_no_elpos;
  Int_t C_pip_mass;
  Int_t C_pip_deltabeta;
  Int_t C_pip_z;
  Int_t C_pip_nphe;

  Int_t C_proton_status;
  Int_t C_proton_stat_sc;
  Int_t C_proton_stat_dc;
  Int_t C_proton_charge;
  Int_t C_proton_no_pion;
  Int_t C_proton_mass;
  Int_t C_proton_deltat;
  Int_t C_proton_z;

  Int_t C_pim_status;
  Int_t C_pim_stat_sc;
  Int_t C_pim_stat_dc;
  Int_t C_pim_charge;
  Int_t C_pim_no_elpos;
  Int_t C_pim_mass;
  Int_t C_pim_deltabeta;
  Int_t C_pim_z;
  Int_t C_pim_nphe;

  Int_t C_rho_W;
  Int_t C_rho_DeltaE;
  Int_t C_rho_tcut;
  Int_t C_rho_zcut;

  //Variables for Proton Knockout
  TLorentzVector v4_p;
  TLorentzVector v4;
  TLorentzVector v4_beam;
  TLorentzVector v4_tg;
  TLorentzVector v4_e;
  TLorentzVector v4_t;
  TLorentzVector v4_pim;

  // Pointers for the histograms. Also stored in the H object array.
  // This is for easy access to the histogram objects.
  
  // Histograms for the Electron ID.

  TH1F *el_u;
  TH1F *el_v;
  TH1F *el_w;
  TH2F *el_ECtot_p;
  TH2F *el_Nphe_p;
  TH2F *el_ECout_ECin;
  TH1F *el_u_cut;
  TH1F *el_v_cut;
  TH1F *el_w_cut;
  TH2F *el_ECtot_p_cut;
  TH2F *el_Nphe_p_cut;
  TH2F *el_ECout_ECin_cut;
  TH2F *diff_el_ghost;  // Histogram for checking for ghost track for second e-
  TH2F *diff_el_ghost_rho;
  
  // Histogram fro pi+ ID.

  TH1F *pip_charge;
  TH1F *pip_mass;
  TH2F *pip_deltabeta_p;
  TH2F *pip_nphe_p;
  TH2F *pip_delta_t_p;
  TH1F *pip_charge_cut;
  TH1F *pip_mass_cut;
  TH2F *pip_deltabeta_p_cut;
  TH2F *pip_deltabeta_p_cut2;
  TH2F *pip_nphe_p_cut;
  TH2F *pip_delta_t_p_cut;

  // Histogram fro proton ID.

  TH1F *proton_charge;
  TH1F *proton_mass;
  TH2F *proton_deltabeta_p;
  TH2F *proton_nphe_p;
  TH2F *proton_delta_t_p;
  TH1F *proton_charge_cut;
  TH1F *proton_mass_cut;
  TH2F *proton_delta_t_p_cut;

  TH1F *miss_mass_1;
  TH1F *miss_mass_2;
  TH1F *miss_mass_3;
  TH1F *miss_mass_4;
  TH1F *miss_mass_5;
  TH1F *miss_mass_6;
  TH1F *miss_mass_7;
  TH1F *miss_mass_8;
  TH1F *miss_mass_9;
  TH1F *miss_mass_10;
  TH1F *proton_angle;
  TH1F *pim_angle;
  TH2F *missmom_vs_missen;
  TH1F *proton_vx;
  TH1F *proton_vy;
  TH1F *proton_vz;

  // Histogram fro pi- ID.

  TH1F *pim_charge;
  TH1F *pim_mass;
  TH2F *pim_deltabeta_p; 
  TH2F *pim_nphe_p;
  TH2F *pim_delta_t_p;
  TH1F *pim_charge_cut;
  TH1F *pim_mass_cut;
  TH2F *pim_deltabeta_p_cut;
  TH2F *pim_deltabeta_p_cut2;
  TH2F *pim_nphe_p_cut;
  TH2F *pim_delta_t_p_cut; 
  TH2F *zpim_zpip_liq;
  TH2F *zpim_zpip_sol;
  

  // Histogram rho distribution

  TH2F* Rho_invm_liq ;
  TH2F* Rho_invm_sol ;
  TH2F* Rho_invm_liq_id1 ;
  TH2F* Rho_invm_sol_id1 ;
  TH2F* Rho_invm_liq_id2 ;
  TH2F* Rho_invm_sol_id2 ;
  TH2F* Rho_invm_liq_id3 ;
  TH2F* Rho_invm_sol_id3 ;
  TH2F* Rho_invm_liq_id4 ;
  TH2F* Rho_invm_sol_id4 ;
  TH2F* Rho_invm_liq_idbg ;
  TH2F* Rho_invm_sol_idbg ;
  TH1F* Rho_bin1_liq ;
  TH1F* Rho_bin2_liq ;
  TH1F* Rho_bin3_liq ;
  TH1F* Rho_bin1_sol ;
  TH1F* Rho_bin2_sol ;
  TH1F* Rho_bin3_sol ;
  TH1F* Rho_bin1_liq_id1 ; // id1 = rho0 
  TH1F* Rho_bin2_liq_id1 ;
  TH1F* Rho_bin3_liq_id1 ;
  TH1F* Rho_bin1_sol_id1 ;
  TH1F* Rho_bin2_sol_id1 ;
  TH1F* Rho_bin3_sol_id1 ;
  TH1F* Rho_bin1_liq_id2 ; // id2 = Delta++
  TH1F* Rho_bin2_liq_id2 ;
  TH1F* Rho_bin3_liq_id2 ;
  TH1F* Rho_bin1_sol_id2 ;
  TH1F* Rho_bin2_sol_id2 ;
  TH1F* Rho_bin3_sol_id2 ;
  TH1F* Rho_bin1_liq_id3 ;
  TH1F* Rho_bin2_liq_id3 ; // id3 =  Delta-0
  TH1F* Rho_bin3_liq_id3 ;
  TH1F* Rho_bin1_sol_id3 ;
  TH1F* Rho_bin2_sol_id3 ;
  TH1F* Rho_bin3_sol_id3 ;
  TH1F* Rho_bin1_liq_id4 ; // id4 =  PS
  TH1F* Rho_bin2_liq_id4 ;
  TH1F* Rho_bin3_liq_id4 ;
  TH1F* Rho_bin1_sol_id4 ;
  TH1F* Rho_bin2_sol_id4 ;
  TH1F* Rho_bin3_sol_id4 ;
  TH1F* Rho_bin1_liq_idbg ; // idbg =  id2+id3+id4
  TH1F* Rho_bin2_liq_idbg ;
  TH1F* Rho_bin3_liq_idbg ;
  TH1F* Rho_bin1_sol_idbg ;
  TH1F* Rho_bin2_sol_idbg ;
  TH1F* Rho_bin3_sol_idbg ;
  TH1F* Rho_bin1_liq_W18 ;
  TH1F* Rho_bin2_liq_W18 ;
  TH1F* Rho_bin3_liq_W18 ;
  TH1F* Rho_bin1_sol_W18 ;
  TH1F* Rho_bin2_sol_W18 ;
  TH1F* Rho_bin3_sol_W18 ;
  TH1F* Rho_bin1_liq_W22 ;
  TH1F* Rho_bin2_liq_W22 ;
  TH1F* Rho_bin3_liq_W22 ;
  TH1F* Rho_bin1_sol_W22 ;
  TH1F* Rho_bin2_sol_W22 ;
  TH1F* Rho_bin3_sol_W22 ;



  
  // Histogram kinematical cut

  TH1F* WH1_cut1_liq  ;
  TH1F* WH1_cut1_sol  ;
  TH1F* WH1_cut2_liq  ;
  TH1F* WH1_cut2_sol  ;
  TH1F* Q2H1_cut1_liq ;
  TH1F* Q2H1_cut1_sol ;
  TH1F* Q2H1_cut2_liq ;
  TH1F* Q2H1_cut2_sol ;
  TH1F* Nu_histo_liq  ;
  TH1F* Nu_histo_sol  ;
  TH1F* Rho_t_histo_liq;
  TH1F* Rho_t_prime_histo_liq ;
  TH1F* Delta_E_histo_liq ;
  TH1F* Rho_z_histo_liq ;
  TH1F* Delta_E_histo_liq_bin1 ;
  TH1F* Rho_z_histo_liq_bin1 ;
  TH1F* Delta_E_histo_liq_bin2 ;
  TH1F* Rho_z_histo_liq_bin2 ;
  TH1F* Delta_E_histo_liq_bin3 ;
  TH1F* Rho_z_histo_liq_bin3 ;
  TH1F* Rho_t_histo_sol ;
  TH1F* Rho_t_prime_histo_sol ;
  TH1F* Delta_E_histo_sol ;
  TH1F* Rho_z_histo_sol ;
  TH1F* Delta_E_histo_sol_bin1 ;
  TH1F* Rho_z_histo_sol_bin1 ;
  TH1F* Delta_E_histo_sol_bin2 ;
  TH1F* Rho_z_histo_sol_bin2 ;
  TH1F* Delta_E_histo_sol_bin3 ;
  TH1F* Rho_z_histo_sol_bin3 ;


  // Histograms for Accceptance

  TH1F* Q2_gen;
  TH1F* W_gen;
  TH1F* t_gen;
  TH1F* rho_mom_gen;
  TH1F* theta_pip_gen;
  TH1F* phi_pip_gen;
  TH1F* phi_l_h_gen;
  TH1F* delta_E_gen; 
  TH1F* Q2_rec[2];
  TH1F* W_rec[2];
  TH1F* t_rec[2];
  TH1F* rho_mom_rec[2];
  TH1F* theta_pip_rec[2];
  TH1F* phi_pip_rec[2];
  TH1F* phi_l_h_rec[2];
  TH1F* delta_E_rec[2];
  TH1F* generated_evnt_bin;
  TH1F* reconstructed_evnt_bin[2];
  TH2F* deforming_matrix_inv;
  
  // Histogram for CC efficiency
  TH3D* H3_cc_eff;
  TH3D* H3_cc_eff_ct;

  // Tree for the acceptance
  TTree *tree_gen ;
  TTree *tree_rec ;
  TTree *tree_def ;
  TTree *tree_momcorr ;
  TTree *tree_cc;

  // Handy Function. TF1 *BetaP=new TF1("BetaP2","x/TMath::Sqrt(x*x + [0]*[0])",0.,4.)
  TF1 *BetaP;

 public:
  TPart_id(); // Initialize code
  ~TPart_id(){
    //
    // Cleanup to avoid memory leakage.
    //
    delete Time;
    delete BetaP;
    DeleteHistos();
    Cuts.Delete();
  }
  Int_t Run(Int_t Nevt=2147483647);
  Int_t Run2(Int_t Nevt=2147483647);
  Int_t Run_pknock(Int_t Nevt=2147483647);
  Int_t Run_momcorr(Int_t Nevt=2147483647);

  //  Int_t Relink_ECPB_bank(TEVNTClass *e);
  Int_t Electron_id(Int_t k); //Lamiaa ID
  Int_t Positron_id(Int_t k); 
  Int_t Second_electron(Int_t k);
  Int_t Pip_id(Int_t k);
  Int_t Pim_id(Int_t k);
  Int_t Electron_id2(Int_t k); //Lorenzo ID
  Int_t Positron_id2(Int_t k); 
  Int_t Second_electron2(Int_t k);
  Int_t Pip_id2(Int_t k);
  Int_t Pim_id2(Int_t k);
  Int_t Proton_id2(Int_t k);
  Int_t Acceptance_data(Int_t i);
  void Acceptance_rec( Int_t i, Int_t j, Int_t k);
  Int_t Get_bin_acc(Int_t i1, Int_t i2, Int_t i3, Int_t i4, Int_t i5);
  Int_t Get_which_bin(Int_t i, Int_t bin);
  void  InitHistos(void);
  void  DeleteHistos(void);
  void  ClearHistos(void);
  void  Write(void);
  void  Test_bin(void);


  ClassDef(TPart_id,1) // A Class for checking the PID.
    ;
};

#endif
