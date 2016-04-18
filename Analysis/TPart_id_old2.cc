// derived from TFilterE.cc from Maurik , implemented with part_ident from Hyke 

#include "TPart_id.h"

ClassImp(TPart_id) // A class for checking the PID.
;  

TPart_id::TPart_id(){
  //
  // Initialize code.
  //

  // Add a signal handler so you can stop running with crtl-C
  Interrupt = new TInterrupt();
  gSystem->AddSignalHandler(Interrupt);  // Setup an intterupt handler.
  
  // Allow for timing the loop
  Time = new TStopwatch(); 
  BetaP=new TF1("BetaP2","x/TMath::Sqrt(x*x + [0]*[0])",0.,4.); // Store a curve.
  Hpid= new TObjArray();
  Hkin= new TObjArray();
  Hrho= new TObjArray();
  Acc_gen = new TObjArray();
  Acc_rec = new TObjArray();
  Acc_acc = new TObjArray();

  InitHistos();

  gFix_EC_Bank=1;
  }


void TPart_id::InitHistos(void){
  //
  // Initialize the Histograms and the Counters.
  //
  
  Hpid->Add(el_u = new TH1F("el_u","EC u ; cm",100,0,500));
  Hpid->Add(el_v = new TH1F("el_v","EC v ; cm",100,0,500));
  Hpid->Add(el_w = new TH1F("el_w","EC w ; cm",100,0,500));
  Hpid->Add(el_u_cut = new TH1F("el_u_cut","EC u cut ; cm",100,0,500));
  Hpid->Add(el_v_cut = new TH1F("el_v_cut","EC v cut ; cm",100,0,500));
  Hpid->Add(el_w_cut = new TH1F("el_w_cut","EC w cut ; cm",100,0,500));
  Hpid->Add(el_ECtot_p = new TH2F("el_ECtot_p","EC_{tot} / p vs p",100,0,5,100,0,0.6));
  Hpid->Add(el_Nphe_p = new TH2F("el_Nphe_p","Number of photo-el vs p",100,0,5,100,0,150));
  Hpid->Add(el_ECout_ECin = new TH2F("el_ECout_ECin","EC_{out} vs EC_{in}",100,0,0.4,100,0,0.4));
  Hpid->Add(el_ECtot_p_cut = new TH2F("el_ECtot_p_cut","EC_{tot} / p vs p cut",100,0,5,100,0,0.6));
  Hpid->Add(el_Nphe_p_cut = new TH2F("el_Nphe_p_cut","Number of photo-el vs p cut",100,0,5,100,0,150));
  Hpid->Add(el_ECout_ECin_cut = new TH2F("el_ECout_ECin_cut","EC_{out} vs EC_{in} cut",100,0,0.4,100,0,0.4));
  Hpid->Add(pip_charge = new TH1F("pip_charge","#pi^{+} charge",100,0,3.5));
  Hpid->Add(pip_mass = new TH1F("pip_mass","#pi^{+} mass",100,0,2));
  Hpid->Add(pip_deltabeta_p = new TH2F("pip_deltabeta_p","#pi^{+} #Delta #beta  vs p",100,0,5,100,0,1));
  Hpid->Add(pip_delta_t_p = new TH2F("pip_delta_t_p","#pi^{+} #Delta T vs p",100,0,5,100,-3,8));
  Hpid->Add(pip_charge_cut = new TH1F("pip_charge_cut","#pi^{+} charge cut",100,0,3.5));
  Hpid->Add(pip_mass_cut = new TH1F("pip_mass_cut","#pi^{+} mass cut",100,0,2));
  Hpid->Add(pip_deltabeta_p_cut = new TH2F("pip_deltabeta_p_cut","#pi^{+} #Delta #beta  vs p cut",100,0,5,100,0,1));
  Hpid->Add(pip_delta_t_p_cut = new TH2F("pip_delta_t_p_cut","#pi^{+} #Delta T  vs p cut",100,0,5,100,-3,8));
  Hpid->Add(pim_charge = new TH1F("pim_charge","#pi^{-} charge",100,-3.5,0));
  Hpid->Add(pim_mass = new TH1F("pim_mass","#pi^{-} mass",100,0,2));
  Hpid->Add(pim_deltabeta_p = new TH2F("pim_deltabeta_p","#pi^{-} #Delta #beta  vs p",100,0,5,100,0,1));
  Hpid->Add(pim_delta_t_p = new TH2F("pim_delta_t_p","#pi^{-} #Delta T  vs p",100,0,5,100,-4,2.5));
  Hpid->Add(pim_charge_cut = new TH1F("pim_charge_cut","#pi^{-} charge cut",100,-3.5,0));
  Hpid->Add(pim_mass_cut = new TH1F("pim_mass_cut","#pi^{-} mass cut",100,0,2));
  Hpid->Add(pim_deltabeta_p_cut = new TH2F("pim_deltabeta_p_cut","#pi^{-} #Delta #beta  vs p cut",100,0,5,100,0,1));
  Hpid->Add(pim_delta_t_p_cut = new TH2F("pim_delta_t_p_cut","#pi^{-} #Delta T  vs p cut",100,0,5,100,-4,2.5));

  Hrho->Add(Rho_invm_liq = new TH1F("Rho_invm_liq","Invariant mass #pi+, #pi- Liquid Target; GeV",100,0.2,1.8));
  Hrho->Add(Rho_invm_sol = new TH1F("Rho_invm_sol","Invariant mass #pi+, #pi- Liquid Target; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_liq = new TH1F("Rho_bin1_liq","Invariant mass #pi+, #pi- Liquid Target 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_liq = new TH1F("Rho_bin2_liq","Invariant mass #pi+, #pi- Liquid Target 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_liq = new TH1F("Rho_bin3_liq","Invariant mass #pi+, #pi- Liquid Target 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_sol = new TH1F("Rho_bin1_sol","Invariant mass #pi+, #pi- Solid Target 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_sol = new TH1F("Rho_bin2_sol","Invariant mass #pi+, #pi- Solid Target 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_sol = new TH1F("Rho_bin3_sol","Invariant mass #pi+, #pi- Solid Target 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_liq_id1 = new TH1F("Rho_bin1_liq_id1","Invariant mass #pi+, #pi- Liquid Target id = 1 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_liq_id1 = new TH1F("Rho_bin2_liq_id1","Invariant mass #pi+, #pi- Liquid Target id = 1 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_liq_id1 = new TH1F("Rho_bin3_liq_id1","Invariant mass #pi+, #pi- Liquid Target id = 1 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_sol_id1 = new TH1F("Rho_bin1_sol_id1","Invariant mass #pi+, #pi- Solid Target id = 1 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_sol_id1 = new TH1F("Rho_bin2_sol_id1","Invariant mass #pi+, #pi- Solid Target id = 1 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_sol_id1 = new TH1F("Rho_bin3_sol_id1","Invariant mass #pi+, #pi- Solid Target id = 1 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_liq_id2 = new TH1F("Rho_bin1_liq_id2","Invariant mass #pi+, #pi- Liquid Target id = 2 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_liq_id2 = new TH1F("Rho_bin2_liq_id2","Invariant mass #pi+, #pi- Liquid Target id = 2 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_liq_id2 = new TH1F("Rho_bin3_liq_id2","Invariant mass #pi+, #pi- Liquid Target id = 2 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_sol_id2 = new TH1F("Rho_bin1_sol_id2","Invariant mass #pi+, #pi- Solid Target id = 2 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_sol_id2 = new TH1F("Rho_bin2_sol_id2","Invariant mass #pi+, #pi- Solid Target id = 2 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_sol_id2 = new TH1F("Rho_bin3_sol_id2","Invariant mass #pi+, #pi- Solid Target id = 2 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_liq_id3 = new TH1F("Rho_bin1_liq_id3","Invariant mass #pi+, #pi- Liquid Target id = 3 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_liq_id3 = new TH1F("Rho_bin2_liq_id3","Invariant mass #pi+, #pi- Liquid Target id = 3 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_liq_id3 = new TH1F("Rho_bin3_liq_id3","Invariant mass #pi+, #pi- Liquid Target id = 3 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_sol_id3 = new TH1F("Rho_bin1_sol_id3","Invariant mass #pi+, #pi- Solid Target id = 3 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_sol_id3 = new TH1F("Rho_bin2_sol_id3","Invariant mass #pi+, #pi- Solid Target id = 3 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_sol_id3 = new TH1F("Rho_bin3_sol_id3","Invariant mass #pi+, #pi- Solid Target id = 3 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_liq_id4 = new TH1F("Rho_bin1_liq_id4","Invariant mass #pi+, #pi- Liquid Target id = 4 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_liq_id4 = new TH1F("Rho_bin2_liq_id4","Invariant mass #pi+, #pi- Liquid Target id = 4 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_liq_id4 = new TH1F("Rho_bin3_liq_id4","Invariant mass #pi+, #pi- Liquid Target id = 4 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_sol_id4 = new TH1F("Rho_bin1_sol_id4","Invariant mass #pi+, #pi- Solid Target id = 4 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_sol_id4 = new TH1F("Rho_bin2_sol_id4","Invariant mass #pi+, #pi- Solid Target id = 4 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_sol_id4 = new TH1F("Rho_bin3_sol_id4","Invariant mass #pi+, #pi- Solid Target id = 4 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_liq_idbg = new TH1F("Rho_bin1_liq_idbg","Invariant mass #pi+, #pi- Liquid Target Background  0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_liq_idbg = new TH1F("Rho_bin2_liq_idbg","Invariant mass #pi+, #pi- Liquid Target Background  1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_liq_idbg = new TH1F("Rho_bin3_liq_idbg","Invariant mass #pi+, #pi- Liquid Target Background  1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_sol_idbg = new TH1F("Rho_bin1_sol_idbg","Invariant mass #pi+, #pi- Solid Target Background  0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_sol_idbg = new TH1F("Rho_bin2_sol_idbg","Invariant mass #pi+, #pi- Solid Target Background  1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_sol_idbg = new TH1F("Rho_bin3_sol_idbg","Invariant mass #pi+, #pi- Solid Target Background  1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_liq_W18 = new TH1F("Rho_bin1_liq_W18","Invariant mass #pi+, #pi- Liquid Target W>1.8, 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_liq_W18 = new TH1F("Rho_bin2_liq_W18","Invariant mass #pi+, #pi- Liquid Target W>1.8, 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_liq_W18 = new TH1F("Rho_bin3_liq_W18","Invariant mass #pi+, #pi- Liquid Target W>1.8, 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_sol_W18 = new TH1F("Rho_bin1_sol_W18","Invariant mass #pi+, #pi- Solid Target W>1.8, 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_sol_W18 = new TH1F("Rho_bin2_sol_W18","Invariant mass #pi+, #pi- Solid Target W>1.8, 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_sol_W18 = new TH1F("Rho_bin3_sol_W18","Invariant mass #pi+, #pi- Solid Target W>1.8, 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_liq_W22 = new TH1F("Rho_bin1_liq_W22","Invariant mass #pi+, #pi- Liquid Target W>2.2, 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_liq_W22 = new TH1F("Rho_bin2_liq_W22","Invariant mass #pi+, #pi- Liquid Target W>2.2, 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_liq_W22 = new TH1F("Rho_bin3_liq_W22","Invariant mass #pi+, #pi- Liquid Target W>2.2, 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin1_sol_W22 = new TH1F("Rho_bin1_sol_W22","Invariant mass #pi+, #pi- Solid Target W>2.2, 0.7< Q^{2} <1.15; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin2_sol_W22 = new TH1F("Rho_bin2_sol_W22","Invariant mass #pi+, #pi- Solid Target W>2.2, 1.15< Q^{2} <1.4; GeV",100,0.2,1.8));
  Hrho->Add(Rho_bin3_sol_W22 = new TH1F("Rho_bin3_sol_W22","Invariant mass #pi+, #pi- Solid Target W>2.2, 1.4< Q^{2} <2.0; GeV",100,0.2,1.8));


  
  Hkin->Add(WH1_cut1_liq = new TH1F("WH1_cut1_liq","W when in the event there is a #pi+ and a #pi- for Liquid Target; GeV",200,0,3.5));
  Hkin->Add(WH1_cut1_sol = new TH1F("WH1_cut1_sol","W when in the event there is a #pi+ and a #pi- for Solid Target; GeV",200,0,3.5));
  Hkin->Add(WH1_cut2_liq = new TH1F("WH1_cut2_liq","W event with #pi+ + #pi- for Liquid target cuts W>2 , |#DeltaE| < 0.1 , 0 < t < 0.45 ; GeV",200,0,3.5));
  Hkin->Add(WH1_cut2_sol = new TH1F("WH1_cut2_sol","W event with #pi+ + #pi- for Solid target cuts W>2 , |#DeltaE| < 0.1 , 0 < t < 0.45 ; GeV",200,0,3.5));
  Hkin->Add(Q2H1_cut1_liq = new TH1F("Q2H1_cut1_liq","Q^{2} when in the event there is a #pi+ and a #pi- for Liquid Target; GeV^{2}",200,0,6.5));
  Hkin->Add(Q2H1_cut1_sol = new TH1F("Q2H1_cut1_sol","Q^{2} when in the event there is a #pi+ and a #pi- for Solid Target; GeV^{2}",200,0,6.5));
  Hkin->Add(Q2H1_cut2_liq = new TH1F("Q2H1_cut2_liq","Q^{2} event with #pi+ + #pi- for Liquid target cuts W>2 , |#DeltaE| < 0.1 , 0 < t < 0.45; GeV^{2}",200,0,6.5));
  Hkin->Add(Q2H1_cut2_sol = new TH1F("Q2H1_cut2_sol","Q^{2} event with #pi+ + #pi- for Solid target cuts W>2 , |#DeltaE| < 0.1 , 0 < t < 0.45; GeV^{2}",200,0,6.5));
  Hkin->Add(Nu_histo_liq = new TH1F("Nu_histo_liq","#nu (Beam_en - el_en) for Liquid target ; GeV",200,0,5));
  Hkin->Add(Nu_histo_sol = new TH1F("Nu_histo_sol","#nu (Beam_en - el_en) for Solid Target; GeV",200,0,5));
  Hkin->Add(Rho_t_histo_liq = new TH1F("Rho_t_histo_liq","t Liquid Target; GeV^{2}",100,-1,5));
  Hkin->Add(Rho_t_prime_histo_liq = new TH1F("Rho_t_prime_histo_liq","t' Liquid Target; GeV^{2}",200,-0.1,5));
  Hkin->Add(Delta_E_histo_liq = new TH1F("Delta_E_histo_liq","#DeltaE Liquid Target; GeV",200,-1,3));
  Hkin->Add(Rho_z_histo_liq = new TH1F("Rho_z_histo_liq","z Liquid Target",200,-0.1,1.3));
  Hkin->Add(Delta_E_histo_liq_bin1 = new TH1F("Delta_E_histo_liq_bin1","#DeltaE Liquid Target; GeV",200,-1,3));
  Hkin->Add(Rho_z_histo_liq_bin1 = new TH1F("Rho_z_histo_liq_bin1","z Liquid Target",200,-0.1,1.3));
  Hkin->Add(Delta_E_histo_liq_bin2 = new TH1F("Delta_E_histo_liq_bin2","#DeltaE Liquid Target; GeV",200,-1,3));
  Hkin->Add(Rho_z_histo_liq_bin2 = new TH1F("Rho_z_histo_liq_bin2","z Liquid Target",200,-0.1,1.3));
  Hkin->Add(Delta_E_histo_liq_bin3 = new TH1F("Delta_E_histo_liq_bin3","#DeltaE Liquid Target; GeV",200,-1,3));
  Hkin->Add(Rho_z_histo_liq_bin3 = new TH1F("Rho_z_histo_liq_bin3","z Liquid Target",200,-0.1,1.3));
  Hkin->Add(Rho_t_histo_sol = new TH1F("Rho_t_histo_sol","t Solid Target; GeV^{2}",100,-1,5));
  Hkin->Add(Rho_t_prime_histo_sol = new TH1F("Rho_t_prime_histo_sol","t' Solid Target; GeV^{2}",200,-0.1,5));
  Hkin->Add(Delta_E_histo_sol = new TH1F("Delta_E_histo_sol","#DeltaE Solid Target; GeV",200,-1,3));
  Hkin->Add(Rho_z_histo_sol = new TH1F("Rho_z_histo_sol","z Solid Target",200,-0.1,1.3));
  Hkin->Add(Delta_E_histo_sol_bin1 = new TH1F("Delta_E_histo_sol_bin1","#DeltaE Solid Target; GeV",200,-1,3));
  Hkin->Add(Rho_z_histo_sol_bin1 = new TH1F("Rho_z_histo_sol_bin1","z Solid Target",200,-0.1,1.3));
  Hkin->Add(Delta_E_histo_sol_bin2 = new TH1F("Delta_E_histo_sol_bin2","#DeltaE Solid Target; GeV",200,-1,3));
  Hkin->Add(Rho_z_histo_sol_bin2 = new TH1F("Rho_z_histo_sol_bin2","z Solid Target",200,-0.1,1.3));
  Hkin->Add(Delta_E_histo_sol_bin3 = new TH1F("Delta_E_histo_sol_bin3","#DeltaE Solid Target; GeV",200,-1,3));
  Hkin->Add(Rho_z_histo_sol_bin3 = new TH1F("Rho_z_histo_sol_bin3","z Solid Target",200,-0.1,1.3));



  Acc_gen->Add(Q2_gen = new TH1F("Q2_gen","Q^{2} generated event",100, 0, 3.5));
  Acc_gen->Add(W_gen = new TH1F("W_gen","W generated event",100, 0, 4));
  Acc_gen->Add(t_gen = new TH1F("t_gen","t generated event",100, 0, 3.5));
  Acc_gen->Add(rho_mom_gen = new TH1F("rho_mom_gen","#rho^{0} momentum generated event",100, 0, 6));
  Acc_gen->Add(theta_pip_gen = new TH1F("theta_pip_gen","#theta_{#pi +} generated event",100, 0, TMath::Pi()));
  Acc_gen->Add(phi_pip_gen = new TH1F("phi_pip_gen","#phi_{#pi +} generated event",100, 0, TMath::Pi() *2));
  Acc_gen->Add(phi_l_h_gen = new TH1F("phi_l_h_gen","#phi_{e-h} generated event",100, 0, TMath::Pi()));


  Acc_rec->Add(Q2_rec[0] = new TH1F("Q2_rec_liq","Q^{2} reconstructed event liquid",100, 0, 3.5));
  Acc_rec->Add(W_rec[0] = new TH1F("W_rec_liq","W reconstructed event liquid",100, 0, 4));
  Acc_rec->Add(t_rec[0] = new TH1F("t_rec_liq","t reconstructed event liquid",100, 0, 1.0));
  Acc_rec->Add(rho_mom_rec[0] = new TH1F("rho_mom_rec_liq","#rho^{0} momentum reconstructed event liquid",100, 0, 6));
  Acc_rec->Add(theta_pip_rec[0] = new TH1F("theta_pip_rec_liq","#theta_{#pi +} reconstructed event liquid",100, 0, TMath::Pi()));
  Acc_rec->Add(phi_pip_rec[0] = new TH1F("phi_pip_rec_liq","#phi_{#pi +} reconstructed event liquid",100, 0, TMath::Pi() *2));
  Acc_rec->Add(phi_l_h_rec[0] = new TH1F("phi_l_h_rec_liq","#phi_{e-h} reconstructed event liquid",100, 0, TMath::Pi()));
  Acc_rec->Add(Q2_rec[1] = new TH1F("Q2_rec_sol","Q^{2} reconstructed event solid",100, 0, 3.5));
  Acc_rec->Add(W_rec[1] = new TH1F("W_rec_sol","W reconstructed event solid",100, 0, 4));
  Acc_rec->Add(t_rec[1] = new TH1F("t_rec_sol","t reconstructed event solid",100, 0, 1.0));
  Acc_rec->Add(rho_mom_rec[1] = new TH1F("rho_mom_rec_sol","#rho^{0} momentum reconstructed event solid",100, 0, 6));
  Acc_rec->Add(theta_pip_rec[1] = new TH1F("theta_pip_rec_sol","#theta_{#pi +} reconstructed event solid",100, 0, TMath::Pi()));
  Acc_rec->Add(phi_pip_rec[1] = new TH1F("phi_pip_rec_sol","#phi_{#pi +} reconstructed event solid",100, 0, TMath::Pi() *2));
  Acc_rec->Add(phi_l_h_rec[1] = new TH1F("phi_l_h_rec_sol","#phi_{e-h} reconstructed event solid",100, 0, TMath::Pi()));

  Acc_acc->Add(reconstructed_evnt_bin[0] = new TH1F("reconstructed_evnt_bin_liq","Reconstructed Event binning liquid",432, 0, 432));
  Acc_acc->Add(reconstructed_evnt_bin[1] = new TH1F("reconstructed_evnt_bin_sol","Reconstructed Event binning solid",432, 0, 432));
  Acc_acc->Add(generated_evnt_bin = new TH1F("generated_evnt_bin","Generated Event binning",432, 0, 432));
  Acc_acc->Add(deforming_matrix_inv = new TH2F("deforming_matrix_inv","Inverse of bin migration of reconstructed Event",432,0,432,432,0,432));


  C_nopart      = Cuts.AddCounter("Event with no particles");
  C_el_status   = Cuts.AddCounter("Electron status ok");
  C_el_stat_cc  = Cuts.AddCounter("Electron cc stat > 0");
  C_el_stat_sc  = Cuts.AddCounter("Electron sc stat > 0");
  C_el_stat_dc  = Cuts.AddCounter("Electron dc stat > 0");
  C_el_stat_ec  = Cuts.AddCounter("Electron ec stat > 0");
  C_el_ecstatus = Cuts.AddCounter("Electron ec status ok");
  C_el_u        = Cuts.AddCounter("Electron u ok");
  C_el_v        = Cuts.AddCounter("Electron v ok");
  C_el_w        = Cuts.AddCounter("Electron w ok");
  C_el_FCG      = Cuts.AddCounter("Electron FCG > 0");
  C_el_EoEi     = Cuts.AddCounter("Electron Eout Ein cut ok");
  C_el_Nphe     = Cuts.AddCounter("Electron Number of photo-el ok");
  C_el_z        = Cuts.AddCounter("Electron Vertex z cut ok");
  C_el_charge   = Cuts.AddCounter("Electron charge cut ok");
  C_Good_e      = Cuts.AddCounter("Electron PID ok");

  C_second_el   = Cuts.AddCounter("Second Electron PID pass");

  C_pos_status   = Cuts.AddCounter("Positron status ok");
  C_pos_stat_cc  = Cuts.AddCounter("Positron cc stat > 0");
  C_pos_stat_sc  = Cuts.AddCounter("Positron sc stat > 0");
  C_pos_stat_dc  = Cuts.AddCounter("Positron dc stat > 0");
  C_pos_stat_ec  = Cuts.AddCounter("Positron ec stat > 0");
  C_pos_ecstatus = Cuts.AddCounter("Positron ec status ok");
  C_pos_u        = Cuts.AddCounter("Positron u ok");
  C_pos_v        = Cuts.AddCounter("Positron v ok");
  C_pos_w        = Cuts.AddCounter("Positron w ok");
  C_pos_FCG      = Cuts.AddCounter("Positron FCG > 0");
  C_pos_EoEi     = Cuts.AddCounter("Positron Eout Ein cut ok");
  C_pos_Nphe     = Cuts.AddCounter("Positron Number of photo-el ok");
  C_pos_z        = Cuts.AddCounter("Positron Vertex z cut ok");
  C_pos_charge   = Cuts.AddCounter("Positron charge cut ok");
  C_Good_pos      = Cuts.AddCounter("Positron PID ok");

  C_EC_error  = Cuts.AddCounter("ECPB link error");
  C_EC_err_fix1  = Cuts.AddCounter("ECPB link error Fixed 1");
  C_EC_err_fix2  = Cuts.AddCounter("ECPB link error Fixed 2");

  C_pip_status    = Cuts.AddCounter("#pi^{+} status ok");
  C_pip_stat_sc   = Cuts.AddCounter("#pi^{+} sc stat > 0");
  C_pip_stat_dc   = Cuts.AddCounter("#pi^{+} dc stat > 0");
  C_pip_charge    = Cuts.AddCounter("#pi^{+} charge ok");
  C_pip_no_elpos  = Cuts.AddCounter("#pi^{+} failed electron PID");
  C_pip_mass      = Cuts.AddCounter("#pi^{+} mass cut ok");
  C_pip_z         = Cuts.AddCounter("#pi^{+} vertex z cut ok");
  C_pip_deltabeta = Cuts.AddCounter("#pi^{+} Deltabeta(Lamia) DeltaT(Lorenzo)  cut ok");

  C_pim_status    = Cuts.AddCounter("#pi^{-} status ok");
  C_pim_stat_sc   = Cuts.AddCounter("#pi^{-} sc stat > 0");
  C_pim_stat_dc   = Cuts.AddCounter("#pi^{-} dc stat > 0");
  C_pim_charge    = Cuts.AddCounter("#pi^{-} charge ok");
  C_pim_no_elpos  = Cuts.AddCounter("#pi^{-} failed electron PID");
  C_pim_mass      = Cuts.AddCounter("#pi^{-} mass cut ok");
  C_pim_z         = Cuts.AddCounter("#pi^{-} vertex z cut ok");
  C_pim_deltabeta = Cuts.AddCounter("#pi^{-} Deltabeta(Lamia) DeltaT(Lorenzo)  cut ok");

  C_rho_W         = Cuts.AddCounter("#rho^{0} W>2 cut");
  C_rho_DeltaE    = Cuts.AddCounter("#rho^{0} |#Delta E| #leq 0.1 cut");
  C_rho_tcut      = Cuts.AddCounter("#rho^{0} t>0 t #leq 0.45 cut");
  C_rho_zcut      = Cuts.AddCounter("#rho^{0} z>0.9 t cut");

}

void TPart_id::DeleteHistos(void){
  //
  // Delete all histograms by calling H->Delete()
  //
  Hpid->Delete();
  Hkin->Delete();
  Hrho->Delete();
  Acc_gen->Delete();
  Acc_rec->Delete();
  Acc_acc->Delete();
}

void TPart_id::ClearHistos(void){
  //
  // Clear all histograms.
  //
  TIter piditer(Hpid);
  TH1 *hist;
  
  while(hist= (TH1 *)piditer.Next()){
    hist->Reset();
  }
 
  TIter kiniter(Hkin);
  //  TH1 *hist;
  
  while(hist= (TH1 *)kiniter.Next()){
    hist->Reset();
  }   
  TIter rhoiter(Hrho);
  //  TH1 *hist;
  
  while(hist= (TH1 *) rhoiter.Next()){
    hist->Reset();
  }
  TIter acciter1(Acc_gen);
  //  TH1 *hist;
  
  while(hist= (TH1 *) acciter1.Next()){
    hist->Reset();
  }
  TIter acciter2(Acc_rec);
  //  TH1 *hist;
  
  while(hist= (TH1 *) acciter2.Next()){
    hist->Reset();
  }
  TIter acciter3(Acc_acc);
  //  TH1 *hist;
  
  while(hist= (TH1 *) acciter3.Next()){
    hist->Reset();
  }
}

void TPart_id::Write(void){
  //
  // Write all histograms in H and
  // all counters in Cuts to the currently
  // open file.
  //

  Cuts.Write("Cuts",TObject::kSingleKey); // Write the cuts in a single key.

  TDirectory *dir1=new TDirectory("Histograms","Filter Histograms");
  dir1->cd();

  TDirectory *dir2=new TDirectory("PID","Particle ID");
  dir2->cd();
  TIter piditer(Hpid);
  TH1 *hist;
  while(hist= (TH1 *)piditer.Next()){
    hist->Write();
  }
  dir2->cd("..");

  TDirectory *dir3=new TDirectory("RHO","rho histogram");
  dir3->cd();
  TIter rhoiter(Hrho);
  while(hist= (TH1 *)rhoiter.Next()){
    hist->Write();
  }
  dir3->cd("..");

  TDirectory *dir4=new TDirectory("KINcut","Kinematical cuts");
  dir4->cd();
  TIter kiniter(Hkin);
  while(hist= (TH1 *)kiniter.Next()){
    hist->Write();
  }
  dir4->cd("..");

  TDirectory *dir5=new TDirectory("Accept","Acceptance arrays");
  dir5->cd();

  TDirectory *dir6=new TDirectory("Gen","Generated events before gsim");
  dir6->cd();
  TIter acciter1(Acc_gen);
  while(hist= (TH1 *)acciter1.Next()){
    hist->Write();
  }
  dir6->cd("..");

  TDirectory *dir7=new TDirectory("Rec","Reconstructed events after user_ana");
  dir7->cd();
  TIter acciter2(Acc_rec);
  while(hist= (TH1 *)acciter2.Next()){
    hist->Write();
  }
  dir7->cd("..");

  TDirectory *dir8=new TDirectory("Acc","Acceptance matrix");
  dir8->cd();
  TIter acciter3(Acc_acc);
  while(hist= (TH1 *)acciter3.Next()){
    hist->Write();
  }
  dir8->cd("..");
   
  dir5->cd("..");  
  


  dir1->cd("..");
}

Int_t TPart_id::Electron_id(Int_t k){
  electron_id_cut = 0;
  Int_t number= GetNRows("EVNT");
  Int_t number_cc= GetNRows("CCPB");
  Int_t number_dc= GetNRows("DCPB");
  Int_t number_sc= GetNRows("SCPB");
  Int_t number_ec= GetNRows("ECPB");
  if( number!=0 && number_cc!=0 && number_ec!=0 && number_sc!=0 && number_dc!=0 ) {
    
    if(Cuts.Test(status(k)>0 , C_el_status)  && Cuts.Test(stat_cc(k)>0, C_el_stat_cc) && Cuts.Test(stat_sc(k)>0, C_el_stat_sc) && Cuts.Test(stat_dc(k)>0, C_el_stat_dc) && Cuts.Test(stat_ec(k)>0, C_el_stat_ec) && Cuts.Test(fcg_cut()==1, C_el_FCG) && Cuts.Test(ec_status(k)>0,C_el_ecstatus)) {
      if (Cuts.Test(charge(k)==-1,C_el_charge)) { 
	Double_t u_value = uvw(k,1);
	Double_t v_value = uvw(k,2);
	Double_t w_value = uvw(k,3);
	el_u->Fill(u_value);
	el_v->Fill(v_value);	
	el_w->Fill(w_value);	
 	if (Cuts.Test(u_value>=40, C_el_u) && Cuts.Test(v_value<=360, C_el_v) &&  Cuts.Test(w_value<=395, C_el_w)) {
  	  el_u_cut->Fill(u_value);
  	  el_v_cut->Fill(v_value);	
  	  el_w_cut->Fill(w_value);
	  el_Nphe_p->Fill(moment(k),nphe(k));
	  if ( Cuts.Test(nphecut(k)==1, C_el_Nphe) ) {
	    el_Nphe_p_cut->Fill(moment(k),nphe(k));	
	    el_ECtot_p->Fill(moment(k),((etot(k))/moment(k)));
	    el_ECout_ECin->Fill(ein(k),eout(k));
	    if (Cuts.Test(pfid_ecinout(k)==1, C_el_EoEi)) {
	      el_ECtot_p_cut->Fill(moment(k),((etot(k))/moment(k)));
	      el_ECout_ECin_cut->Fill(ein(k),eout(k));
	      if (Cuts.Test(vertex_cut_elec()>0, C_el_z) ) {
		electron_id_cut = 1;
	      }
	    }
	  }
	}
      }
    }
      
  }
  return electron_id_cut;
}

Int_t TPart_id::Positron_id( Int_t k){
  positron_id_cut = 0;
  Int_t number= GetNRows("EVNT");
  Int_t number_cc= GetNRows("CCPB");
  Int_t number_dc= GetNRows("DCPB");
  Int_t number_sc= GetNRows("SCPB");
  Int_t number_ec= GetNRows("ECPB");
  if( number!=0 && number_cc!=0 && number_ec!=0 && number_sc!=0 && number_dc!=0 ) {
    if(Cuts.Test(status(k)>0 , C_pos_status) && Cuts.Test(stat_cc(k)>0, C_pos_stat_cc) && Cuts.Test(stat_sc(k)>0, C_pos_stat_sc) && Cuts.Test(stat_dc(k)>0, C_pos_stat_dc) && Cuts.Test(stat_ec(k)>0, C_pos_stat_ec)) {
      if(Cuts.Test(fcg_cut()==1, C_pos_FCG)  && Cuts.Test(ec_status(k)>0,C_pos_ecstatus)) {
	if (Cuts.Test(charge(k)==1,C_pos_charge) && Cuts.Test(uvw(k,1)>=40, C_pos_u) &&  Cuts.Test(uvw(k,2)<=360, C_pos_v) &&  Cuts.Test(uvw(k,3)<=395, C_pos_w) &&  Cuts.Test(nphecut(k)==1, C_pos_Nphe) &&  Cuts.Test(pfid_ecinout(k)==1, C_pos_EoEi) )  positron_id_cut = 1; 
      }
    }
  }
  return positron_id_cut;
}

Int_t TPart_id::Second_electron( Int_t k){
  second_electron_id_cut = 0;
  Int_t number= GetNRows("EVNT");
  Int_t number_cc= GetNRows("CCPB");
  Int_t number_dc= GetNRows("DCPB");
  Int_t number_sc= GetNRows("SCPB");
  Int_t number_ec= GetNRows("ECPB");
  if( number!=0 && number_cc!=0 && number_ec!=0 && number_sc!=0 && number_dc!=0 ) {
    if(status(k)>0 && stat_cc(k)>0 && stat_sc(k)>0 && stat_dc(k)>0 && stat_ec(k)>0 ) {
      if(fcg_cut()==1  && ec_status(k)>0) {
	if (charge(k)==-1 && uvw(k,1)>=40 && uvw(k,2)<=360 && uvw(k,3)<=395 && nphecut(k)==1 && pfid_ecinout(k)==1 )  second_electron_id_cut = 1; 
      }
    }
  }
  return second_electron_id_cut;
}

Int_t TPart_id::Pip_id( Int_t k){
  pip_id_cut = 0;
  Int_t number= GetNRows("EVNT");
  Int_t number_dc= GetNRows("DCPB");
  Int_t number_sc= GetNRows("SCPB");
  if( number!=0 && number_sc!=0 && number_dc!=0 ) {  
    if(Cuts.Test(status(k)>0 , C_pip_status) && Cuts.Test(stat_sc(k)>0, C_pip_stat_sc) && Cuts.Test(stat_dc(k)>0, C_pip_stat_dc)) {
      pip_charge->Fill(charge(k));
      if(Cuts.Test(charge(k) > 0,C_pip_charge)) {
	pip_charge_cut->Fill(charge(k));
	pip_deltabeta_p->Fill(moment(k),delta_betta(k));
	if(Cuts.Test(deltabeta_cut(k) == 1,C_pip_deltabeta)) {
	  pip_deltabeta_p_cut->Fill(moment(k),delta_betta(k));
	  pip_mass->Fill(sqrt(mass2(k)));
	  if(Cuts.Test(( mass2(k)<=0.2025 && mass2(k)>0.0001) , C_pip_mass)) {
	     pip_mass_cut->Fill(sqrt(mass2(k)));
	    if (Cuts.Test(Positron_id(k)==0, C_pip_no_elpos) && Cuts.Test(vertex_cut_pion(k)>0, C_pip_z)) pip_id_cut = 1;
	  }
	}
      }
    }
  
  }
  return pip_id_cut;
}

Int_t TPart_id::Pim_id( Int_t k){

  pim_id_cut = 0;
  Int_t number= GetNRows("EVNT");
  Int_t number_dc= GetNRows("DCPB");
  Int_t number_sc= GetNRows("SCPB");
  if( number!=0 && number_sc!=0 && number_dc!=0 ) {  
    if(Cuts.Test(status(k)>0 , C_pim_status) && Cuts.Test(stat_sc(k)>0, C_pim_stat_sc) && Cuts.Test(stat_dc(k)>0, C_pim_stat_dc) ) {
      pim_charge->Fill(charge(k));
      if(Cuts.Test(charge(k) < 0,C_pim_charge)) {
	pim_charge_cut->Fill(charge(k));
	pim_deltabeta_p->Fill(moment(k),delta_betta(k));
	if (Cuts.Test(deltabeta_cut(k) == 1,C_pim_deltabeta)) {
	  pim_deltabeta_p_cut->Fill(moment(k),delta_betta(k));
	  pim_mass->Fill(sqrt(mass2(k)));
	  if (Cuts.Test(( mass2(k)<=0.2025 && mass2(k)>0.0001) , C_pim_mass)) {
	    pim_mass_cut->Fill(sqrt(mass2(k)));
	    if(Cuts.Test(Second_electron(k)==0, C_pim_no_elpos) && Cuts.Test(vertex_cut_pion(k)>0, C_pim_z)) pim_id_cut = 1;
	  }
	}
      }
    }
  }
  return pim_id_cut; 
}


Int_t TPart_id::Electron_id2(Int_t k){
  electron_id_cut = 0;
  Int_t number= GetNRows("EVNT");
  Int_t number_cc= GetNRows("CCPB");
  Int_t number_dc= GetNRows("DCPB");
  Int_t number_sc= GetNRows("SCPB");
  Int_t number_ec= GetNRows("ECPB");
  if( number!=0 && number_cc!=0 && number_ec!=0 && number_sc!=0 && number_dc!=0 ) {
    
    if(Cuts.Test(status(k)>0 , C_el_status)  && Cuts.Test(stat_cc(k)>0, C_el_stat_cc) && Cuts.Test(stat_sc(k)>0, C_el_stat_sc) && Cuts.Test(stat_dc(k)>0, C_el_stat_dc) && Cuts.Test(stat_ec(k)>0, C_el_stat_ec) && Cuts.Test(fcg_cut()==1, C_el_FCG) && Cuts.Test(ec_status(k)>0,C_el_ecstatus)) {
      if (Cuts.Test(charge(k)==-1,C_el_charge)) { 
	Double_t u_value = uvw(k,1);
	Double_t v_value = uvw(k,2);
	Double_t w_value = uvw(k,3);
	el_u->Fill(u_value);
	el_v->Fill(v_value);	
	el_w->Fill(w_value);	
 	if (Cuts.Test(u_value>=40, C_el_u) && Cuts.Test(v_value<=360, C_el_v) &&  Cuts.Test(w_value<=395, C_el_w)) {
  	  el_u_cut->Fill(u_value);
  	  el_v_cut->Fill(v_value);	
  	  el_w_cut->Fill(w_value);
	  el_Nphe_p->Fill(moment(k),nphe(k));
	  if ( Cuts.Test(nphecut(k)==1, C_el_Nphe) ) {
	    el_Nphe_p_cut->Fill(moment(k),nphe(k));	
	    el_ECtot_p->Fill(moment(k),((etot(k))/moment(k)));
	    el_ECout_ECin->Fill(ein(k),eout(k));
	    if (Cuts.Test(mine_eccut(k)==1, C_el_EoEi)) {
	      el_ECtot_p_cut->Fill(moment(k),((etot(k))/moment(k))); 
	      el_ECout_ECin_cut->Fill(ein(k),eout(k));
	      if (Cuts.Test(vertex_cut_el_mine()>0, C_el_z) ) {
		electron_id_cut = 1;
	      }
	    }
	  }
	}
      }
    }
      
  }
  return electron_id_cut;
}

Int_t TPart_id::Positron_id2( Int_t k){
  positron_id_cut = 0;
  Int_t number= GetNRows("EVNT");
  Int_t number_cc= GetNRows("CCPB");
  Int_t number_dc= GetNRows("DCPB");
  Int_t number_sc= GetNRows("SCPB");
  Int_t number_ec= GetNRows("ECPB");
  if( number!=0 && number_cc!=0 && number_ec!=0 && number_sc!=0 && number_dc!=0 ) {
    if(Cuts.Test(status(k)>0 , C_pos_status) && Cuts.Test(stat_cc(k)>0, C_pos_stat_cc) && Cuts.Test(stat_sc(k)>0, C_pos_stat_sc) && Cuts.Test(stat_dc(k)>0, C_pos_stat_dc) && Cuts.Test(stat_ec(k)>0, C_pos_stat_ec)) {
      if(Cuts.Test(fcg_cut()==1, C_pos_FCG)  && Cuts.Test(ec_status(k)>0,C_pos_ecstatus)) {
	if (Cuts.Test(charge(k)==1,C_pos_charge) && Cuts.Test(uvw(k,1)>=40, C_pos_u) &&  Cuts.Test(uvw(k,2)<=360, C_pos_v) &&  Cuts.Test(uvw(k,3)<=395, C_pos_w) &&  Cuts.Test(nphecut(k)==1, C_pos_Nphe) &&  Cuts.Test(mine_eccut(k)==1, C_pos_EoEi) )  positron_id_cut = 1; 
      }
    }
  }
  return positron_id_cut;
}

Int_t TPart_id::Second_electron2( Int_t k){
  second_electron_id_cut = 0;
  Int_t number= GetNRows("EVNT");
  Int_t number_cc= GetNRows("CCPB");
  Int_t number_dc= GetNRows("DCPB");
  Int_t number_sc= GetNRows("SCPB");
  Int_t number_ec= GetNRows("ECPB");
  if( number!=0 && number_cc!=0 && number_ec!=0 && number_sc!=0 && number_dc!=0 ) {
    if(status(k)>0 && stat_cc(k)>0 && stat_sc(k)>0 && stat_dc(k)>0 && stat_ec(k)>0 ) {
      if(fcg_cut()==1  && ec_status(k)>0) {
	if (charge(k)==-1 && uvw(k,1)>=40 && uvw(k,2)<=360 && uvw(k,3)<=395 && nphecut(k)==1 && mine_eccut(k)==1 )  second_electron_id_cut = 1; 
      }
    }
  }
  return second_electron_id_cut;
}

Int_t TPart_id::Pip_id2( Int_t k){
  pip_id_cut = 0;
  Int_t number= GetNRows("EVNT");
  Int_t number_dc= GetNRows("DCPB");
  Int_t number_sc= GetNRows("SCPB");
  if( number!=0 && number_sc!=0 && number_dc!=0 ) {  
    if(Cuts.Test(status(k)>0 , C_pip_status) && Cuts.Test(stat_sc(k)>0, C_pip_stat_sc) && Cuts.Test(stat_dc(k)>0, C_pip_stat_dc)) {
      pip_charge->Fill(charge(k));
      if(Cuts.Test(charge(k) > 0,C_pip_charge)) {
	pip_charge_cut->Fill(charge(k));
	pip_deltabeta_p->Fill(moment(k),delta_betta(k));
	pip_delta_t_p->Fill(moment(k),delta_t_pi(k));
	if(Cuts.Test(delta_t_pip_cut(k) == 1,C_pip_deltabeta)) {
	  pip_deltabeta_p_cut->Fill(moment(k),delta_betta(k));
	  pip_delta_t_p_cut->Fill(moment(k),delta_t_pi(k));
	  pip_mass->Fill(sqrt(mass2(k)));
	  if(Cuts.Test(( mass2(k)<=0.2025 && mass2(k)>0.0001) , C_pip_mass)) {
	     pip_mass_cut->Fill(sqrt(mass2(k)));
	    if (Cuts.Test(Positron_id2(k)==0, C_pip_no_elpos)) pip_id_cut = 1;
	  }
	}
      }
    }
  
  }
  return pip_id_cut;
}

Int_t TPart_id::Pim_id2( Int_t k){

  pim_id_cut = 0;
  Int_t number= GetNRows("EVNT");
  Int_t number_dc= GetNRows("DCPB");
  Int_t number_sc= GetNRows("SCPB");
  if( number!=0 && number_sc!=0 && number_dc!=0 ) {  
    if(Cuts.Test(status(k)>0 , C_pim_status) && Cuts.Test(stat_sc(k)>0, C_pim_stat_sc) && Cuts.Test(stat_dc(k)>0, C_pim_stat_dc) ) {
      pim_charge->Fill(charge(k));
      if(Cuts.Test(charge(k) < 0,C_pim_charge)) {
	pim_charge_cut->Fill(charge(k));
	pim_deltabeta_p->Fill(moment(k),delta_betta(k));
	pim_delta_t_p->Fill(moment(k),delta_t_pi(k));
	if (Cuts.Test(delta_t_pim_cut(k) == 1,C_pim_deltabeta)) {
	  pim_deltabeta_p_cut->Fill(moment(k),delta_betta(k));
	  pim_delta_t_p_cut->Fill(moment(k),delta_t_pi(k));
	  pim_mass->Fill(sqrt(mass2(k)));
	  if (Cuts.Test(( mass2(k)<=0.2025 && mass2(k)>0.0001) , C_pim_mass)) {
	    pim_mass_cut->Fill(sqrt(mass2(k)));
	    if(Cuts.Test(Second_electron2(k)==0, C_pim_no_elpos)) pim_id_cut = 1;
	  }
	}
      }
    }
  }
  return pim_id_cut; 
}

Int_t TPart_id::Get_bin_acc(Int_t i1, Int_t i2, Int_t i3, Int_t i4, Int_t i5){
  
  //  Int_t bin_Q        = 3;
  Int_t bin_W        = 3;
  Int_t bin_t        = 2;
  Int_t bin_rhomom   = 4;
  Int_t bin_thetapip = 6;
  


  Int_t iBin = ( i1) * ( bin_W * bin_t * bin_rhomom * bin_thetapip) +
               ( i2) * (         bin_t * bin_rhomom * bin_thetapip) +
               ( i3) * (                 bin_rhomom * bin_thetapip) +
               ( i4) * (                              bin_thetapip) +
               ( i5) ;

  return iBin;



}


Int_t TPart_id::Acceptance_data(Int_t i){
  // This will fill with the generator data

  Int_t bin_acc=0;
  Double_t Q2_v, W_v, t_v, rho_mom_v, theta_pip_v, phi_pip_v, phi_lep_had_v, Delta_E_v;
  
  Q2_v = Q2_mc();
  W_v = W_mc();
  Delta_E_v = find_Delta_E_mc();
  t_v = t_mc();
  rho_mom_v = rho_mom_mc();
  theta_pip_v = theta_pip_mc();
  phi_pip_v= phi_pip_mc();
  phi_lep_had_v= phi_lep_had_mc();

  if (W_v > 2 && Delta_E_v <= 0.1 && t_v > 0 && t_v < 0.45) { 


    if (i == 1) {
      Q2_gen->Fill(Q2_v);
      W_gen->Fill(W_v);
      t_gen->Fill(t_v);
      rho_mom_gen->Fill(rho_mom_v);
      theta_pip_gen->Fill(theta_pip_v);
      phi_pip_gen->Fill(phi_pip_v);
      phi_l_h_gen->Fill(phi_lep_had_v);
    }

    bin_acc = int((Q2_v-0.5)/2*432);  // 432 bins between 0.5 and 2.5
    // here I will fill the Acceptance array
    if (i==1) {
      generated_evnt_bin->Fill(bin_acc+0.5);
    }
  }
  return bin_acc;
}


void TPart_id::Acceptance_rec(Int_t i, Int_t j, Int_t k){
  // This will fill with the reconstructed  data i=pi-  j=pi+ 
  // k=which_target (0=liq, 1=sol)

  Int_t bin_rec=0;
  Int_t bin_gen=0;

  Double_t Q2_v, W_v, t_v, rho_mom_v, theta_pip_v, phi_pip_v, phi_lep_had_v, Delta_E_v;
  Q2_v = Q2();
  W_v = W();
  t_v = find_t_rho(0,i,j);
  Delta_E_v = find_Delta_E(0,i,j);
  rho_mom_v = rho_mom_ev(i,j);
  theta_pip_v = theta_pip_ev(0,i,j);
  phi_pip_v= phi_pip_ev(0,i,j);
  phi_lep_had_v= phi_lep_had_ev(0,i,j);

  if (W_v > 2 && Delta_E_v <= 0.1 && t_v > 0 && t_v < 0.45) { 

    Q2_rec[k]->Fill(Q2_v);
    W_rec[k]->Fill(W_v);
    t_rec[k]->Fill(t_v);
    rho_mom_rec[k]->Fill(rho_mom_v);
    theta_pip_rec[k]->Fill(theta_pip_v);
    phi_pip_rec[k]->Fill(phi_pip_v);
    phi_l_h_rec[k]->Fill(phi_lep_had_v);

    // here I will fill the Acceptance array
    bin_rec= int((Q2_v-0.5)/2*432);  // 432 bins between 0.5 and 2.5
    bin_gen=Acceptance_data(0);
    reconstructed_evnt_bin[k]->Fill(bin_rec+0.5);
    deforming_matrix_inv->Fill(bin_gen+0.5,bin_rec+0.5);

  }
  
}


Int_t TPart_id::Run(Int_t Max_evt){

  // Run with Lamiaa Particle ID


  Int_t iEvent;

  
 

  Next(); // Loads the first event.


  TChain *chain=GetTree();  // This is a new method.
  TTree *filevt=(TTree *)chain->CloneTree(0); // This copies the TChain
  filevt->SetMaxTreeSize(21474836480ULL); // Allow 20 Gbyte files.
  filevt->SetAutoSave(1024*1024*512);  // This is not needed but good idea

  Int_t ntree = chain->GetTreeNumber(); // Remember which chain we are on.

  cout << "Running ...." << endl;

  Time->Start(kTRUE);

  for(iEvent=0;iEvent<GetEntries() && Next()==0; iEvent++){

    if(iEvent % 100000 == 0 ){
      printf("Analyzed %09d events, now at %09d , with %09d good electrons.\n",iEvent,GetHEADER()->GetNEvent(),((TCounter *)Cuts[C_Good_e])->GetTrues());
    }
    
    // Check if we are still on the same tree in the chain.
    // If we are onto the next tree, now we need to reset the branches!!
    if(ntree != chain->GetTreeNumber()){
      ntree = chain->GetTreeNumber();               
      TIter next(chain->GetListOfBranches()); 
      TBranch *branch;
      while ((branch = (TBranch*)next())) {
	void *add = branch->GetAddress();
	if (add) filevt->SetBranchAddress(branch->GetName(),add);
	else{
	  cerr<<"ERROR- Can not reset the branches of scaler tree !\n";
	}
      }
    }
    
    if(Cuts.Test( (GetNPart()==0),C_nopart)) continue; // Skip events without particles. 
    mass_rho = 0;
    rho_mass = 0;
    which_target = 0;
    which_pip = 0;
    which_pim = 0;
    electron_id_pass = 0;
    pip_id_pass = 0;
    pim_id_pass = 0;
    positron_id_pass = 0;
    second_electron_id_pass = 0;
    good_event_towrite = 0;
    for(Int_t ipart=0;ipart<GetNPart();ipart++){	
      if(ipart==0 && Electron_id(ipart)==1) {
	electron_id_pos = ipart;
	electron_id_pass++;
      }
      if(Pip_id(ipart)==1) {
	pip_id_pos[pip_id_pass] = ipart;
	pip_id_pass++;
      }
      if(Pim_id(ipart)==1) {
	pim_id_pos[pim_id_pass] = ipart;
	pim_id_pass++;
      }
      if(Positron_id(ipart)==	1) positron_id_pass++;
      if(Second_electron(ipart)==1 && ipart>0) second_electron_id_pass++;
    }   
    if (Cuts.Test(electron_id_pass == 1,C_Good_e) && pip_id_pass > 0 && pim_id_pass > 0 && positron_id_pass == 0 && Cuts.Test(second_electron_id_pass == 0,C_second_el)) {
      good_event_towrite = 1;      
      for (Int_t pip_iter= 0 ; pip_iter < pip_id_pass ; pip_iter++) {
	for (Int_t pim_iter= 0 ; pim_iter < pim_id_pass ; pim_iter++) {
	  if (vertex_cut_pion(pim_id_pos[pim_iter]) == vertex_cut_pion(pip_id_pos[pip_iter])) {
	    //vertex_cut_pion have the information also of the vertex of the electron
	    rho_mass = invariant_mass(pim_id_pos[pim_iter],pip_id_pos[pip_iter]) ;
	    Double_t term1 = fabs(rho_mass -0.77) ;
	    Double_t term2 = fabs(mass_rho -0.77) ;
	    if (term1 < term2) {
	      mass_rho = rho_mass;
	      which_pip = pip_id_pos[pip_iter];
	      which_pim = pim_id_pos[pim_iter];
	      which_target = vertex_cut_elec();
	      //	      printf("%d",which_target);
	    }
	  }
	}
      }
      if (mass_rho > 0) {
	//Fill histogram before kinematical cuts
	if (which_target == 1) {
	  //fill liquid target
	  WH1_cut1_liq->Fill(W());
	  Q2H1_cut1_liq->Fill(Q2());
	  Rho_t_histo_liq->Fill(find_t_rho(electron_id_pos,which_pim,which_pip));
	  Delta_E_histo_liq->Fill(find_Delta_E(electron_id_pos,which_pim,which_pip));
	}
	if (which_target == 2) {
	  //fill solid target
	  WH1_cut1_sol->Fill(W());
	  Q2H1_cut1_sol->Fill(Q2());
	  Rho_t_histo_sol->Fill(find_t_rho(electron_id_pos,which_pim,which_pip));
	  Delta_E_histo_sol->Fill(find_Delta_E(electron_id_pos,which_pim,which_pip));
	}
	  
	// I could put the fabs() into the formula for Delta_E and t_rho

	if (Cuts.Test(W()>2,C_rho_W) && Cuts.Test(find_Delta_E(electron_id_pos,which_pim,which_pip)<=0.1,C_rho_DeltaE) && Cuts.Test(cut_t_rho(electron_id_pos,which_pim,which_pip)==1,C_rho_tcut)) {
	  // Fill histogram after kinematical cuts
	  if (which_target == 1) {

	    //fill liquid target
	    Double_t Q2_value = Q2();
	    WH1_cut2_liq->Fill(W());
	    Rho_invm_liq->Fill(mass_rho);
	    Q2H1_cut2_liq->Fill(Q2_value);
	    if (Q2_value >= 0.7 && Q2_value <1.15) {
	      Rho_bin1_liq->Fill(mass_rho);
	    }
	    if (Q2_value >= 1.15 && Q2_value <1.4) {
	      Rho_bin2_liq->Fill(mass_rho);
	    }     
	    if (Q2_value >= 1.4 && Q2_value <2) {
	      Rho_bin3_liq->Fill(mass_rho);
	    }
	  }
	  if (which_target == 2) {
	    Double_t Q2_value = Q2();
	    //fill solid target
	    WH1_cut2_sol->Fill(W());
	    Rho_invm_sol->Fill(mass_rho);
	    Q2H1_cut2_sol->Fill(Q2_value);
	    if (Q2_value >= 0.7 && Q2_value <1.15) {
	      Rho_bin1_sol->Fill(mass_rho);
	    }
	    if (Q2_value >= 1.15 && Q2_value <1.4) {
	      Rho_bin2_sol->Fill(mass_rho);
	    }     
	    if (Q2_value >= 1.4 && Q2_value <2) {
	      Rho_bin3_sol->Fill(mass_rho);
	    }
	  }
	}

      }
	
    }

	   
    if(Interrupt->IsInterrupted()){
      break;
    }
    if (good_event_towrite == 1) {
      filevt->Fill();  // Fill the output chain.
    }
    //    Next();
  } // END EVENT LOOP.

  Time->Stop();

  printf("Processed %d events in %6.2f sec, %6.2f CPU sec. \n",iEvent,Time->RealTime(),Time->CpuTime());
  printf("Rate is %7.1f events/sec, %7.1f events/CPUsec \n",iEvent/Time->RealTime(),iEvent/Time->CpuTime());
  

  return(1);
}

Int_t TPart_id::Run2(Int_t Max_evt){

  //Run with Lorenzo Particle ID

  Int_t iEvent;
  Int_t bin_calculated;

  //  Test_bin();
  
 

  Next(); // Loads the first event.


  TChain *chain=GetTree();  // This is a new method.
  TTree *filevt=(TTree *)chain->CloneTree(0); // This copies the TChain
  filevt->SetMaxTreeSize(21474836480ULL); // Allow 20 Gbyte files.
  filevt->SetAutoSave(1024*1024*512);  // This is not needed but good idea

  Int_t ntree = chain->GetTreeNumber(); // Remember which chain we are on.

  cout << "Running ...." << endl;

  Time->Start(kTRUE);



  for(iEvent=0;iEvent<GetEntries() && Next()==0; iEvent++){

    bin_calculated = Acceptance_data(1);  // filling the acceptance array histogram

    if(iEvent % 100000 == 0 ){
      printf("Analyzed %09d events, now at %09d , with %09d good electrons.\n",iEvent,GetHEADER()->GetNEvent(),((TCounter *)Cuts[C_Good_e])->GetTrues());
    }
    
    // Check if we are still on the same tree in the chain.
    // If we are onto the next tree, now we need to reset the branches!!
    if(ntree != chain->GetTreeNumber()){
      ntree = chain->GetTreeNumber();               
      TIter next(chain->GetListOfBranches()); 
      TBranch *branch;
      while ((branch = (TBranch*)next())) {
	void *add = branch->GetAddress();
	if (add) filevt->SetBranchAddress(branch->GetName(),add);
	else{
	  cerr<<"ERROR- Can not reset the branches of scaler tree !\n";
	}
      }
    }
    
    if(Cuts.Test( (GetNPart()==0),C_nopart)) continue; // Skip events without particles. 
    mass_rho = 0;
    rho_mass = 0;
    which_target = 0;
    which_pip = 0;
    which_pim = 0;
    electron_id_pass = 0;
    pip_id_pass = 0;
    pim_id_pass = 0;
    positron_id_pass = 0;
    second_electron_id_pass = 0;
    good_event_towrite = 0;
    for(Int_t ipart=0;ipart<GetNPart();ipart++){	
      if(ipart==0 && Electron_id2(ipart)==1) {
	electron_id_pos = ipart;
	electron_id_pass++;
      }
      if(Pip_id2(ipart)==1) {
	pip_id_pos[pip_id_pass] = ipart;
	pip_id_pass++;
      }
      if(Pim_id2(ipart)==1) {
	pim_id_pos[pim_id_pass] = ipart;
	pim_id_pass++;
      }
      if(Positron_id2(ipart)==	1) positron_id_pass++;
      if(Second_electron2(ipart)==1 && ipart>0) second_electron_id_pass++;
    }   ;
    if (Cuts.Test(electron_id_pass == 1,C_Good_e) && pip_id_pass > 0 && pim_id_pass > 0 && positron_id_pass == 0 && Cuts.Test(second_electron_id_pass == 0,C_second_el)) {
      good_event_towrite = 1;      
      for (Int_t pip_iter= 0 ; pip_iter < pip_id_pass ; pip_iter++) {
	for (Int_t pim_iter= 0 ; pim_iter < pim_id_pass ; pim_iter++) {
	  if (vertex_cut_mine(pim_id_pos[pim_iter] , pip_id_pos[pip_iter]) == 1 || vertex_cut_mine(pim_id_pos[pim_iter] , pip_id_pos[pip_iter]) == 2) {
	    //vertex_cut_mine is 1 for Liquid Target , 2 for Solid Target , 0 if fails. It is also checking the electron treated as the first particle in the EVNT bank
	    rho_mass = invariant_mass(pim_id_pos[pim_iter],pip_id_pos[pip_iter]) ;
	    Double_t term1 = fabs(rho_mass -0.77) ;
	    Double_t term2 = fabs(mass_rho -0.77) ;
	    if (term1 < term2) {
	      mass_rho = rho_mass;
	      which_pip = pip_id_pos[pip_iter];
	      which_pim = pim_id_pos[pim_iter];
	      which_target = vertex_cut_mine(pim_id_pos[pim_iter] , pip_id_pos[pip_iter]) ;
	      //	      printf("%d",which_target);
	    }
	  }
	}
      }
      if (mass_rho > 0) {
	//Fill histogram before kinematical cuts

	Double_t Q2_value = Q2();

	if (which_target == 1) {
	  //fill liquid target

	  Acceptance_rec(which_pim,which_pip,0);  // filling the
	  // acceptance array histogram
	  WH1_cut1_liq->Fill(W());
	  Q2H1_cut1_liq->Fill(Q2());
	  Rho_t_histo_liq->Fill(find_t_rho(electron_id_pos,which_pim,which_pip));
	  Delta_E_histo_liq->Fill(find_Delta_E(electron_id_pos,which_pim,which_pip));
	  Rho_z_histo_liq->Fill(find_zrho(electron_id_pos,which_pim,which_pip));
	  if (W()>2 && cut_t_rho(electron_id_pos,which_pim,which_pip)==1) {
	    if (Q2_value >= 0.7 && Q2_value <1.15) {
	      Rho_z_histo_liq_bin1->Fill(find_zrho(electron_id_pos,which_pim,which_pip));
	      Delta_E_histo_liq_bin1->Fill(find_Delta_E(electron_id_pos,which_pim,which_pip));
	    }
	    if (Q2_value >= 1.15 && Q2_value <1.4) {
	      Rho_z_histo_liq_bin2->Fill(find_zrho(electron_id_pos,which_pim,which_pip));
	      Delta_E_histo_liq_bin2->Fill(find_Delta_E(electron_id_pos,which_pim,which_pip));
	    }
	    if (Q2_value >= 1.4 && Q2_value <2) {
	      Rho_z_histo_liq_bin3->Fill(find_zrho(electron_id_pos,which_pim,which_pip));
	      Delta_E_histo_liq_bin3->Fill(find_Delta_E(electron_id_pos,which_pim,which_pip));
	    }

	  }
	}
	if (which_target == 2) {
	  //fill solid target

	  Acceptance_rec(which_pim,which_pip,1);  // filling the
	  // acceptance array histogram
	  WH1_cut1_sol->Fill(W());
	  Q2H1_cut1_sol->Fill(Q2());
	  Rho_t_histo_sol->Fill(find_t_rho(electron_id_pos,which_pim,which_pip));
	  Delta_E_histo_sol->Fill(find_Delta_E(electron_id_pos,which_pim,which_pip));
	  Rho_z_histo_sol->Fill(find_zrho(electron_id_pos,which_pim,which_pip));
	  if (W()>2 && cut_t_rho(electron_id_pos,which_pim,which_pip)==1) {
	    if (Q2_value >= 0.7 && Q2_value <1.15) {
	      Rho_z_histo_sol_bin1->Fill(find_zrho(electron_id_pos,which_pim,which_pip));
	      Delta_E_histo_sol_bin1->Fill(find_Delta_E(electron_id_pos,which_pim,which_pip));
	    }
	    if (Q2_value >= 1.15 && Q2_value <1.4) {
	      Rho_z_histo_sol_bin2->Fill(find_zrho(electron_id_pos,which_pim,which_pip));
	    Delta_E_histo_sol_bin2->Fill(find_Delta_E(electron_id_pos,which_pim,which_pip));
	    }
	    if (Q2_value >= 1.4 && Q2_value <2) {
	      Rho_z_histo_sol_bin3->Fill(find_zrho(electron_id_pos,which_pim,which_pip));
	      Delta_E_histo_sol_bin3->Fill(find_Delta_E(electron_id_pos,which_pim,which_pip));
	    }
	  }
	}
	   
	// I could put the fabs() into the formula for Delta_E and t_rho
	if (Cuts.Test(W()>1.8,C_rho_W) && Cuts.Test(find_Delta_E(electron_id_pos,which_pim,which_pip)<=0.1,C_rho_DeltaE) && Cuts.Test(cut_t_rho(electron_id_pos,which_pim,which_pip)==1,C_rho_tcut)) {   // DELTA E CUT
	//	if (Cuts.Test(W()>1.8,C_rho_W) &&
	//	Cuts.Test(find_zrho(electron_id_pos,which_pim,which_pip)>0.9,C_rho_zcut)
	//	&&
	//	Cuts.Test(cut_t_rho(electron_id_pos,which_pim,which_pip)==1,C_rho_tcut))
	//	{                             // Z RHO CUT


	  // Fill histogram after kinematical cuts
	  if (which_target == 1) {
	    //fill liquid target
	    WH1_cut2_liq->Fill(W());
	    Rho_invm_liq->Fill(mass_rho);
	    Q2H1_cut2_liq->Fill(Q2_value);
	    if (Q2_value >= 0.7 && Q2_value <1.15) {
	      Rho_bin1_liq_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin1_liq->Fill(mass_rho);
 		if (id_mc() == 1) {
		  //		  cout << "id = 1" << endl;
		  Rho_bin1_liq_id1->Fill(mass_rho);
  		}
		if (id_mc() == 2) {
		 Rho_bin1_liq_id2->Fill(mass_rho);
		}
		if (id_mc() == 3) {
		 Rho_bin1_liq_id3->Fill(mass_rho);
		}
		if (id_mc() == 4) {
		 Rho_bin1_liq_id4->Fill(mass_rho);
		}
		if ( id_mc() == 2 || id_mc() == 3 || id_mc() == 4 ) {
		 Rho_bin1_liq_idbg->Fill(mass_rho);
		}
	      }
	      if (W()>2.2) {
		Rho_bin1_liq_W22->Fill(mass_rho);
	      }
	    }
	    if (Q2_value >= 1.15 && Q2_value <1.4) {
	      Rho_bin2_liq_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin2_liq->Fill(mass_rho);
		if (id_mc() == 1) {
		 Rho_bin2_liq_id1->Fill(mass_rho);
		}
		if (id_mc() == 2) {
		  Rho_bin2_liq_id2->Fill(mass_rho); 
		}
		if (id_mc() == 3) {
		 Rho_bin2_liq_id3->Fill(mass_rho);
		}
		if (id_mc() == 4) {
		 Rho_bin2_liq_id4->Fill(mass_rho);
		}
		if ( id_mc() == 2 || id_mc() == 3 || id_mc() == 4 ) {
		 Rho_bin2_liq_idbg->Fill(mass_rho);
		}
	      }
	      if (W()>2.2) {
		Rho_bin2_liq_W22->Fill(mass_rho);
	      }
	    }     
	    if (Q2_value >= 1.4 && Q2_value <2) {
	      Rho_bin3_liq_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin3_liq->Fill(mass_rho);
		if (id_mc() == 1) {
		 Rho_bin3_liq_id1->Fill(mass_rho);
		}
		if (id_mc() == 2) {
		 Rho_bin3_liq_id2->Fill(mass_rho);
		}
		if (id_mc() == 3) {
		 Rho_bin3_liq_id3->Fill(mass_rho);
		}
		if (id_mc() == 4) {
		 Rho_bin3_liq_id4->Fill(mass_rho);
		}
		if ( id_mc() == 2 || id_mc() == 3 || id_mc() == 4 ) {
		 Rho_bin3_liq_idbg->Fill(mass_rho);
		}
	      }
	      if (W()>2.2) {
		Rho_bin3_liq_W22->Fill(mass_rho);
	      }
	    }
	  }
	  if (which_target == 2) {
	    Double_t Q2_value = Q2();
	    //fill solid target
	    WH1_cut2_sol->Fill(W());
	    Rho_invm_sol->Fill(mass_rho);
	    Q2H1_cut2_sol->Fill(Q2_value);
	    if (Q2_value >= 0.7 && Q2_value <1.15) {
	      Rho_bin1_sol_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin1_sol->Fill(mass_rho);
 		if (id_mc() == 1) {
		  //		  cout << "id = 1" << endl;
		  Rho_bin1_sol_id1->Fill(mass_rho);
 		}
		if (id_mc() == 2) {
		 Rho_bin1_sol_id2->Fill(mass_rho);
		}
		if (id_mc() == 3) {
		 Rho_bin1_sol_id3->Fill(mass_rho);
		}
		if (id_mc() == 4) {
		 Rho_bin1_sol_id4->Fill(mass_rho);
		}
		if ( id_mc() == 2 || id_mc() == 3 || id_mc() == 4 ) {
		 Rho_bin1_sol_idbg->Fill(mass_rho);
		}
	      }
	      if (W()>2.2) {
		Rho_bin1_sol_W22->Fill(mass_rho);
	      }
	    }
	    if (Q2_value >= 1.15 && Q2_value <1.4) {
	      Rho_bin2_sol_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin2_sol->Fill(mass_rho);
		if (id_mc() == 1) {
		 Rho_bin2_sol_id1->Fill(mass_rho);
		}
		if (id_mc() == 2) {
		 Rho_bin2_sol_id2->Fill(mass_rho);
		}
		if (id_mc() == 3) {
		 Rho_bin2_sol_id3->Fill(mass_rho);
		}
		if (id_mc() == 4) {
		 Rho_bin2_sol_id4->Fill(mass_rho);
		}
		if ( id_mc() == 2 || id_mc() == 3 || id_mc() == 4 ) {
		 Rho_bin2_sol_idbg->Fill(mass_rho);
		}
	      }
	      if (W()>2.2) {
		Rho_bin2_sol_W22->Fill(mass_rho);
	      }
	    }     
	    if (Q2_value >= 1.4 && Q2_value <2) {
	      Rho_bin3_sol_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin3_sol->Fill(mass_rho);
		if (id_mc() == 1) {
		 Rho_bin3_sol_id1->Fill(mass_rho);
		}
		if (id_mc() == 2) {
		 Rho_bin3_sol_id2->Fill(mass_rho);
		}
		if (id_mc() == 3) {
		 Rho_bin3_sol_id3->Fill(mass_rho);
		}
		if (id_mc() == 4) {
		 Rho_bin3_sol_id4->Fill(mass_rho);
		}
		if ( id_mc() == 2 || id_mc() == 3 || id_mc() == 4 ) {
		 Rho_bin3_sol_idbg->Fill(mass_rho);
		}
	      }
	      if (W()>2.2) {
		Rho_bin3_sol_W22->Fill(mass_rho);
	      }
	    }
	  }
	}

      }
	
    }

	   
    if(Interrupt->IsInterrupted()){
      break;
    }
    if (good_event_towrite == 1) {
      filevt->Fill();  // Fill the output chain.
    }
    //    Next();
  } // END EVENT LOOP.

  Time->Stop();

  printf("Processed %d events in %6.2f sec, %6.2f CPU sec. \n",iEvent,Time->RealTime(),Time->CpuTime());
  printf("Rate is %7.1f events/sec, %7.1f events/CPUsec \n",iEvent/Time->RealTime(),iEvent/Time->CpuTime());
  

  return(1);
}

void  TPart_id::Test_bin(void){
  
  Int_t bin_out = 0;
  for(Int_t v1 =0 ; v1<3 ; v1++) {
    for(Int_t v2 = 0 ; v2 < 3 ; v2++) {
      for(Int_t v3 = 0 ; v3 < 2 ; v3++) {
	for(Int_t v4 = 0 ; v4 < 4 ; v4++) {
	  for(Int_t v5 = 0 ; v5 < 6 ; v5++) {
	    bin_out = Get_bin_acc(v1,v2,v3,v4,v5);

	    printf("bin %d ,%d ,%d ,%d ,%d : Bin matrix =  %d \n",v1,v2,v3,v4,v5,bin_out);

	  }
	}
      }
    }
  }

}



