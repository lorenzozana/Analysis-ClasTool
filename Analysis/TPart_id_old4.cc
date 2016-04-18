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
  Hpid->Add(pip_deltabeta_p = new TH2F("pip_deltabeta_p","#pi^{+} #Delta #beta  vs p",200,0,5,200,-1,1));
  Hpid->Add(pip_nphe_p = new TH2F("pip_nphe_p","#pi^{+} N_{phe}  vs p cut",200,0,5,151,0,150));
  Hpid->Add(pip_delta_t_p = new TH2F("pip_delta_t_p","#pi^{+} #Delta T vs p",100,0,5,100,-3,8));
  Hpid->Add(pip_charge_cut = new TH1F("pip_charge_cut","#pi^{+} charge cut",100,0,3.5));
  Hpid->Add(pip_mass_cut = new TH1F("pip_mass_cut","#pi^{+} mass cut",100,0,2));
  Hpid->Add(pip_deltabeta_p_cut = new TH2F("pip_deltabeta_p_cut","#pi^{+} #Delta #beta  vs p cut",200,0,5,200,-1,1));
  Hpid->Add(pip_deltabeta_p_cut2 = new TH2F("pip_deltabeta_p_cut2","#pi^{+} #Delta #beta  vs p cut",200,0,5,200,-1,1));
  Hpid->Add(pip_nphe_p_cut = new TH2F("pip_nphe_p_cut","#pi^{+} N_{phe}  vs p cut",200,0,5,151,0,150));
  Hpid->Add(pip_delta_t_p_cut = new TH2F("pip_delta_t_p_cut","#pi^{+} #Delta T  vs p cut",100,0,5,100,-3,8));
  Hpid->Add(proton_charge = new TH1F("proton_charge","proton charge",100,0,3.5));
  Hpid->Add(proton_mass = new TH1F("proton_mass","proton mass",100,0,2));
  Hpid->Add(proton_delta_t_p = new TH2F("proton_delta_t_p","proton #Delta T vs p",100,0,5,100,-3,8));
  Hpid->Add(proton_charge_cut = new TH1F("proton_charge_cut","proton charge cut",100,0,3.5));
  Hpid->Add(proton_mass_cut = new TH1F("proton_mass_cut","proton mass cut",100,0,2));
  Hpid->Add(proton_delta_t_p_cut = new TH2F("proton_delta_t_p_cut","proton #Delta T  vs p cut",100,0,5,100,-3,8));
  Hpid->Add(pim_charge = new TH1F("pim_charge","#pi^{-} charge",100,-3.5,0));
  Hpid->Add(pim_mass = new TH1F("pim_mass","#pi^{-} mass",100,0,2));
  Hpid->Add(pim_deltabeta_p = new TH2F("pim_deltabeta_p","#pi^{-} #Delta #beta  vs p",200,0,5,200,-1,1));
  Hpid->Add(pim_nphe_p = new TH2F("pim_nphe_p","#pi^{-} N_{phe}  vs p",200,0,5,151,0,150));
  Hpid->Add(pim_delta_t_p = new TH2F("pim_delta_t_p","#pi^{-} #Delta T  vs p",100,0,5,100,-4,2.5));
  Hpid->Add(pim_charge_cut = new TH1F("pim_charge_cut","#pi^{-} charge cut",100,-3.5,0));
  Hpid->Add(pim_mass_cut = new TH1F("pim_mass_cut","#pi^{-} mass cut",100,0,2));
  Hpid->Add(pim_deltabeta_p_cut = new TH2F("pim_deltabeta_p_cut","#pi^{-} #Delta #beta  vs p cut",200,0,5,200,-1,1));
  Hpid->Add(pim_deltabeta_p_cut2 = new TH2F("pim_deltabeta_p_cut2","#pi^{-} #Delta #beta  vs p cut",200,0,5,200,-1,1));
  Hpid->Add(pim_nphe_p_cut = new TH2F("pim_nphe_p_cut","#pi^{-} N_{phe}  vs p cut",200,0,5,151,0,150));
  Hpid->Add(pim_delta_t_p_cut = new TH2F("pim_delta_t_p_cut","#pi^{-} #Delta T  vs p cut",100,0,5,100,-4,2.5));
  Hpid->Add(diff_el_ghost = new TH2F("diff_el_ghost","Difference Z vs momentum for 2 e-;#Delta Z (cm); #Delta P (GeV)",100,-20,20,100,-0.5,0.5));
  Hpid->Add(diff_el_ghost_rho = new TH2F("diff_el_ghost_rho","Difference Z vs momentum for 2 e-;#Delta Z (cm); #Delta P (GeV)",100,-20,20,100,-0.5,0.5));
  Hpid->Add(zpim_zpip_liq = new TH2F("zpim_zpip_liq","Z pim Z pip liquid;z #pi^{-} (cm);z #pi^{+} (cm) ",100,-38,-15,100,-38,-15));
  Hpid->Add(zpim_zpip_sol = new TH2F("zpim_zpip_sol","Z pim Z pip solid;z #pi^{-} (cm);z #pi^{+} (cm) ",100,-38,-15,100,-38,-15));

  Hrho->Add(Rho_invm_liq = new TH2F("Rho_invm_liq","Invariant mass #pi+, #pi- Liquid Target;  #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
  Hrho->Add(Rho_invm_sol = new TH2F("Rho_invm_sol","Invariant mass #pi+, #pi- Solid Target;  #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
  Hrho->Add(Rho_invm_liq_id1 = new TH2F("Rho_invm_liq_id1","Invariant mass #pi+, #pi- Liquid Target id = 1; #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
  Hrho->Add(Rho_invm_sol_id1 = new TH2F("Rho_invm_sol_id1","Invariant mass #pi+, #pi- Solid Target id = 1; #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
  Hrho->Add(Rho_invm_liq_id2 = new TH2F("Rho_invm_liq_id2","Invariant mass #pi+, #pi- Liquid Target id = 2; #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
  Hrho->Add(Rho_invm_sol_id2 = new TH2F("Rho_invm_sol_id2","Invariant mass #pi+, #pi- Solid Target id = 2; #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
  Hrho->Add(Rho_invm_liq_id3 = new TH2F("Rho_invm_liq_id3","Invariant mass #pi+, #pi- Liquid Target id = 3; #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
  Hrho->Add(Rho_invm_sol_id3 = new TH2F("Rho_invm_sol_id3","Invariant mass #pi+, #pi- Solid Target id = 3; #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
  Hrho->Add(Rho_invm_liq_id4 = new TH2F("Rho_invm_liq_id4","Invariant mass #pi+, #pi- Liquid Target id = 4; #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
  Hrho->Add(Rho_invm_sol_id4 = new TH2F("Rho_invm_sol_id4","Invariant mass #pi+, #pi- Solid Target id = 4; #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
  Hrho->Add(Rho_invm_liq_idbg = new TH2F("Rho_invm_liq_idbg","Invariant mass #pi+, #pi- Liquid Target background; #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
  Hrho->Add(Rho_invm_sol_idbg = new TH2F("Rho_invm_sol_idbg","Invariant mass #pi+, #pi- Solid Target background; #rho^{0} (GeV) ; Q^{2} (GeV)",100,0.2,1.8,1000,0.5,2.5));
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
  Hkin->Add(H3_cc_eff = new TH3D("H3_cc_eff","Efficiency plot for CC;#theta_{e}(deg);#phi_{e}(deg);p",300,0,60,500,0,360,100,0,5));
  Hkin->Add(H3_cc_eff_ct = new TH3D("H3_cc_eff_ct","Counts plot for CC;#theta_{e}(deg);#phi_{e}(deg);p",300,0,60,500,0,360,100,0,5));


  Acc_gen->Add(Q2_gen = new TH1F("Q2_gen","Q^{2} generated event",100, 0, 3.5));
  Acc_gen->Add(W_gen = new TH1F("W_gen","W generated event",100, 0, 4));
  Acc_gen->Add(t_gen = new TH1F("t_gen","t generated event",100, 0, 3.5));
  Acc_gen->Add(rho_mom_gen = new TH1F("rho_mom_gen","#rho^{0} momentum generated event",100, 0, 6));
  Acc_gen->Add(theta_pip_gen = new TH1F("theta_pip_gen","#theta_{#pi +} generated event",100, 0, TMath::Pi()));
  Acc_gen->Add(phi_pip_gen = new TH1F("phi_pip_gen","#phi_{#pi +} generated event",100, 0, TMath::Pi() *2));
  Acc_gen->Add(phi_l_h_gen = new TH1F("phi_l_h_gen","#phi_{e-h} generated event",100, 0, TMath::Pi()));
  Acc_gen->Add(delta_E_gen = new TH1F("delta_E_gen","#Delta E generated event",100, 0,1));


  Acc_rec->Add(Q2_rec[0] = new TH1F("Q2_rec_liq","Q^{2} reconstructed event liquid",100, 0, 3.5));
  Acc_rec->Add(W_rec[0] = new TH1F("W_rec_liq","W reconstructed event liquid",100, 0, 4));
  Acc_rec->Add(t_rec[0] = new TH1F("t_rec_liq","t reconstructed event liquid",100, 0, 1.0));
  Acc_rec->Add(rho_mom_rec[0] = new TH1F("rho_mom_rec_liq","#rho^{0} momentum reconstructed event liquid",100, 0, 6));
  Acc_rec->Add(theta_pip_rec[0] = new TH1F("theta_pip_rec_liq","#theta_{#pi +} reconstructed event liquid",100, 0, TMath::Pi()));
  Acc_rec->Add(phi_pip_rec[0] = new TH1F("phi_pip_rec_liq","#phi_{#pi +} reconstructed event liquid",100, 0, TMath::Pi() *2));
  Acc_rec->Add(phi_l_h_rec[0] = new TH1F("phi_l_h_rec_liq","#phi_{e-h} reconstructed event liquid",100, 0, TMath::Pi()));
  Acc_rec->Add(delta_E_rec[0] = new TH1F("delta_E_rec_liq","#Delta E reconstructed event liquid",100, 0,1));
  Acc_rec->Add(Q2_rec[1] = new TH1F("Q2_rec_sol","Q^{2} reconstructed event solid",100, 0, 3.5));
  Acc_rec->Add(W_rec[1] = new TH1F("W_rec_sol","W reconstructed event solid",100, 0, 4));
  Acc_rec->Add(t_rec[1] = new TH1F("t_rec_sol","t reconstructed event solid",100, 0, 1.0));
  Acc_rec->Add(rho_mom_rec[1] = new TH1F("rho_mom_rec_sol","#rho^{0} momentum reconstructed event solid",100, 0, 6));
  Acc_rec->Add(theta_pip_rec[1] = new TH1F("theta_pip_rec_sol","#theta_{#pi +} reconstructed event solid",100, 0, TMath::Pi()));
  Acc_rec->Add(phi_pip_rec[1] = new TH1F("phi_pip_rec_sol","#phi_{#pi +} reconstructed event solid",100, 0, TMath::Pi() *2));
  Acc_rec->Add(phi_l_h_rec[1] = new TH1F("phi_l_h_rec_sol","#phi_{e-h} reconstructed event solid",100, 0, TMath::Pi()));
  Acc_rec->Add(delta_E_rec[1] = new TH1F("delta_E_rec_sol","#Delta E reconstructed event solid",100, 0,1));

  Acc_acc->Add(reconstructed_evnt_bin[0] = new TH1F("reconstructed_evnt_bin_liq","Reconstructed Event binning liquid",12960, 0, 12960));
  Acc_acc->Add(reconstructed_evnt_bin[1] = new TH1F("reconstructed_evnt_bin_sol","Reconstructed Event binning solid",12960, 0, 12960));
  Acc_acc->Add(generated_evnt_bin = new TH1F("generated_evnt_bin","Generated Event binning",12960, 0, 12960));
  Acc_acc->Add(deforming_matrix_inv = new TH2F("deforming_matrix_inv","Inverse of bin migration of reconstructed Event",12960,0,12960,12960,0,12960));

  tree_gen = new TTree("Acceptance_tree_gen","Acceptance bins with Mass of the rho GENERATED EVENTS");
  tree_gen->Branch("Acc_Q2_g",&Acc_Q2_g,"Acc_Q2_g/I");
  tree_gen->Branch("Acc_W_g",&Acc_W_g,"Acc_W_g/I");
  tree_gen->Branch("Acc_t_g",&Acc_t_g,"Acc_t_g/I");
  tree_gen->Branch("Acc_deltaE_g",&Acc_deltaE_g,"Acc_deltaE_g/I");
  tree_gen->Branch("Acc_z_g",&Acc_z_g,"Acc_z_g/I");
  tree_gen->Branch("Acc_thetapip_g",&Acc_thetapip_g,"Acc_thetapip_g/I");
  tree_gen->Branch("Acc_id_g",&Acc_id_g,"Acc_id_g/I");
  tree_gen->Branch("Acc_massrho_g",&Acc_massrho_g,"Acc_massrho_g/D");
  tree_gen->Branch("Acc_lc_g_v",&Acc_lc_g_v,"Acc_lc_g_v/D");
  tree_gen->Branch("Acc_Q2_g_v",&Acc_Q2_g_v,"Acc_Q2_g_v/D");
  tree_gen->Branch("Acc_W_g_v",&Acc_W_g_v,"Acc_W_g_v/D");
  tree_gen->Branch("Acc_t_g_v",&Acc_t_g_v,"Acc_t_g_v/D");
  tree_gen->Branch("Acc_deltaE_g_v",&Acc_deltaE_g_v,"Acc_deltaE_g_v/D");
  tree_gen->Branch("Acc_rhomom_g_v",&Acc_rhomom_g_v,"Acc_rhomom_g_v/D");
  tree_gen->Branch("Acc_z_g_v",&Acc_z_g_v,"Acc_z_g_v/D");
  tree_gen->Branch("Acc_thetapip_g_v",&Acc_thetapip_g_v,"Acc_thetapip_g_v/D");
  
  tree_rec = new TTree("Acceptance_tree_rec","Acceptance bins with Mass of the rho RECONSTRUCTED EVENTS");
  tree_rec->Branch("Acc_Q2_r",&Acc_Q2_r,"Acc_Q2_r/I");
  tree_rec->Branch("Acc_W_r",&Acc_W_r,"Acc_W_r/I");
  tree_rec->Branch("Acc_t_r",&Acc_t_r,"Acc_t_r/I");
  tree_rec->Branch("Acc_deltaE_r",&Acc_deltaE_r,"Acc_deltaE_r/I");
  tree_rec->Branch("Acc_z_r",&Acc_z_r,"Acc_z_r/I");
  tree_rec->Branch("Acc_thetapip_r",&Acc_thetapip_r,"Acc_thetapip_r/I");
  tree_rec->Branch("Acc_id_r",&Acc_id_r,"Acc_id_r/I");
  tree_rec->Branch("Acc_massrho_r",&Acc_massrho_r,"Acc_massrho_r/D");
  tree_rec->Branch("Acc_tg_r",&Acc_tg_r,"Acc_tg_r/I");
  tree_rec->Branch("Acc_Q2_r_v",&Acc_Q2_r_v,"Acc_Q2_r_v/D");
  tree_rec->Branch("Acc_lc_r_v",&Acc_lc_r_v,"Acc_lc_r_v/D");
  tree_rec->Branch("Acc_W_r_v",&Acc_W_r_v,"Acc_W_r_v/D");
  tree_rec->Branch("Acc_t_r_v",&Acc_t_r_v,"Acc_t_r_v/D");
  tree_rec->Branch("Acc_deltaE_r_v",&Acc_deltaE_r_v,"Acc_deltaE_r_v/D");
  tree_rec->Branch("Acc_rhomom_r_v",&Acc_rhomom_r_v,"Acc_rhomom_r_v/D");
  tree_rec->Branch("Acc_z_r_v",&Acc_z_r_v,"Acc_z_r_v/D");
  tree_rec->Branch("Acc_thetapip_r_v",&Acc_thetapip_r_v,"Acc_thetapip_r_v/D");

  tree_def = new TTree("Acceptance_tree_def","Acceptance bins with Mass of the rho DEF MATRIX");
  tree_def->Branch("Acc_Q2_r",&Acc_Q2_r,"Acc_Q2_r/I");
  tree_def->Branch("Acc_W_r",&Acc_W_r,"Acc_W_r/I");
  tree_def->Branch("Acc_t_r",&Acc_t_r,"Acc_t_r/I");
  tree_def->Branch("Acc_deltaE_r",&Acc_deltaE_r,"Acc_deltaE_r/I");
  tree_def->Branch("Acc_z_r",&Acc_z_r,"Acc_z_r/I");
  tree_def->Branch("Acc_thetapip_r",&Acc_thetapip_r,"Acc_thetapip_r/I");
  tree_def->Branch("Acc_massrho_r",&Acc_massrho_r,"Acc_massrho_r/D");
  tree_def->Branch("Acc_Q2_g",&Acc_Q2_g,"Acc_Q2_g/I");
  tree_def->Branch("Acc_W_g",&Acc_W_g,"Acc_W_g/I");
  tree_def->Branch("Acc_t_g",&Acc_t_g,"Acc_t_g/I");
  tree_def->Branch("Acc_deltaE_g",&Acc_deltaE_g,"Acc_deltaE_g/I");
  tree_def->Branch("Acc_z_g",&Acc_z_g,"Acc_z_g/I");
  tree_def->Branch("Acc_thetapip_g",&Acc_thetapip_g,"Acc_thetapip_g/I");
  tree_def->Branch("Acc_id_g",&Acc_id_g,"Acc_id_g/I");
  tree_def->Branch("Acc_massrho_g",&Acc_massrho_g,"Acc_massrho_g/D");
  tree_def->Branch("Acc_Q2_g_v",&Acc_Q2_g_v,"Acc_Q2_g_v/D");
  tree_def->Branch("Acc_lc_g_v",&Acc_lc_g_v,"Acc_lc_g_v/D");
  tree_def->Branch("Acc_W_g_v",&Acc_W_g_v,"Acc_W_g_v/D");
  tree_def->Branch("Acc_t_g_v",&Acc_t_g_v,"Acc_t_g_v/D");
  tree_def->Branch("Acc_deltaE_g_v",&Acc_deltaE_g_v,"Acc_deltaE_g_v/D");
  tree_def->Branch("Acc_rhomom_g_v",&Acc_rhomom_g_v,"Acc_rhomom_g_v/D");
  tree_def->Branch("Acc_z_g_v",&Acc_z_g_v,"Acc_z_g_v/D");
  tree_def->Branch("Acc_thetapip_g_v",&Acc_thetapip_g_v,"Acc_thetapip_g_v/D");
  tree_def->Branch("Acc_Q2_r_v",&Acc_Q2_r_v,"Acc_Q2_r_v/D");
  tree_def->Branch("Acc_lc_r_v",&Acc_lc_r_v,"Acc_lc_r_v/D");
  tree_def->Branch("Acc_W_r_v",&Acc_W_r_v,"Acc_W_r_v/D");
  tree_def->Branch("Acc_t_r_v",&Acc_t_r_v,"Acc_t_r_v/D");
  tree_def->Branch("Acc_deltaE_r_v",&Acc_deltaE_r_v,"Acc_deltaE_r_v/D");
  tree_def->Branch("Acc_rhomom_r_v",&Acc_rhomom_r_v,"Acc_rhomom_r_v/D");
  tree_def->Branch("Acc_z_r_v",&Acc_z_r_v,"Acc_z_r_v/D");
  tree_def->Branch("Acc_thetapip_r_v",&Acc_thetapip_r_v,"Acc_thetapip_r_v/D");


  tree_cc = new TTree("Efficiency_cc_tree","Efficiency determined using the Vlassov function");
  tree_cc->Branch("CC_theta_ev",&CC_theta_ev,"CC_theta_ev/D");
  tree_cc->Branch("CC_phi_ev",&CC_phi_ev,"CC_phi_ev/D");
  tree_cc->Branch("CC_mom_ev",&CC_mom_ev,"CC_mom_ev/D");
  tree_cc->Branch("CC_eff_ev",&CC_eff_ev,"CC_eff_ev/D");

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
  C_Good_pim    = Cuts.AddCounter("Pi- PID ok for >0 particle");
  C_Good_pip    = Cuts.AddCounter("Pi+ PID ok for >0 particle");
//  C_Good_pip2   = Cuts.AddCounter("Pi+ PID ok for >0 particle and 1e- and >0 Pi-);
//  C_Good_pos2   = Cuts.AddCounter("Positron PID ok 
 C_Good_kin     = Cuts.AddCounter("Pass kinetic cut");	
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
  C_Good_pos     = Cuts.AddCounter("Positron PID ok (=0)");

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
  C_pip_nphe      = Cuts.AddCounter("#pi^{+} CC Number of photoelectron cut");

  C_proton_status    = Cuts.AddCounter("Proton status ok");
  C_proton_stat_sc   = Cuts.AddCounter("Proton sc stat > 0");
  C_proton_stat_dc   = Cuts.AddCounter("Proton dc stat > 0");
  C_proton_charge    = Cuts.AddCounter("Proton charge ok");
  C_proton_no_pion  = Cuts.AddCounter("Proton failed Pion PID");
  C_proton_mass      = Cuts.AddCounter("Proton mass cut ok");
  C_proton_z         = Cuts.AddCounter("Electron vertex z from solid tg cut ok");
  C_proton_deltat = Cuts.AddCounter("Proton DeltaT(Lorenzo)  cut ok");

  C_pim_status    = Cuts.AddCounter("#pi^{-} status ok");
  C_pim_stat_sc   = Cuts.AddCounter("#pi^{-} sc stat > 0");
  C_pim_stat_dc   = Cuts.AddCounter("#pi^{-} dc stat > 0");
  C_pim_charge    = Cuts.AddCounter("#pi^{-} charge ok");
  C_pim_no_elpos  = Cuts.AddCounter("#pi^{-} failed electron PID");
  C_pim_mass      = Cuts.AddCounter("#pi^{-} mass cut ok");
  C_pim_z         = Cuts.AddCounter("#pi^{-} vertex z cut ok");
  C_pim_deltabeta = Cuts.AddCounter("#pi^{-} Deltabeta(Lamia) DeltaT(Lorenzo)  cut ok");
  C_pim_nphe      = Cuts.AddCounter("#pi^{-} CC Number of photoelectron cut");

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
  tree_gen->Delete();
  tree_rec->Delete();
  tree_def->Delete();
  tree_cc->Delete();
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
  
  tree_gen->Reset();
  tree_rec->Reset();
  tree_def->Reset();
  tree_cc->Reset();
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
  while ( hist= ( (TH1 *)piditer.Next() ) ) {
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

  tree_gen->Write();
  tree_rec->Write();
  tree_def->Write();
  tree_cc->Write();

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
	pip_deltabeta_p->Fill(moment(k),delta_betta(k));
	if(Cuts.Test(deltabeta_cut(k) == 1,C_pip_deltabeta)) {
	  pip_nphe_p->Fill(moment(k),nphe(k));
	  if(Cuts.Test( nphecut_pi(k)==1, C_pip_nphe)) {
	    if (Cuts.Test(Positron_id(k)==0, C_pip_no_elpos) && Cuts.Test(vertex_cut_pion(k)>0, C_pip_z)) {
	      pip_id_cut = 1;
	      pip_deltabeta_p_cut->Fill(moment(k),delta_betta(k));
	      pip_nphe_p_cut->Fill(moment(k),nphe(k));
	      pip_charge_cut->Fill(charge(k));
	    }
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
	pim_deltabeta_p->Fill(moment(k),delta_betta(k));
	if (Cuts.Test(deltabeta_cut(k) == 1,C_pim_deltabeta)) {
	  pim_nphe_p->Fill(moment(k),nphe(k));
	  if(Cuts.Test( nphecut_pi(k)==1, C_pim_nphe)) {
	    if(Cuts.Test(Second_electron(k)==0, C_pim_no_elpos) && Cuts.Test(vertex_cut_pion(k)>0, C_pim_z)) {
	      pim_id_cut = 1;
	      pim_charge_cut->Fill(charge(k));
	      pim_deltabeta_p_cut->Fill(moment(k),delta_betta(k));
	      pim_nphe_p_cut->Fill(moment(k),nphe(k));
	    }
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
//	  pip_deltabeta_p_cut->Fill(moment(k),delta_betta(k));/
//	  pip_delta_t_p_cut->Fill(moment(k),delta_t_pi(k));
	  pip_mass->Fill(sqrt(mass2(k)));
	  if(Cuts.Test(( mass2(k)<=0.2025 && mass2(k)>0.0001) , C_pip_mass)) {
	     pip_mass_cut->Fill(sqrt(mass2(k)));
	    if (Cuts.Test(Positron_id2(k)==0, C_pip_no_elpos)) { 
	      pip_id_cut = 1;
	      pip_deltabeta_p_cut->Fill(moment(k),delta_betta(k));
	      pip_delta_t_p_cut->Fill(moment(k),delta_t_pi(k));
	    }
	  }
	}
      }
    }
  
  }
  return pip_id_cut;
}

Int_t TPart_id::Proton_id2( Int_t k){
  proton_id_cut = 0;
  Int_t number= GetNRows("EVNT");
  Int_t number_dc= GetNRows("DCPB");
  Int_t number_sc= GetNRows("SCPB");
  if( number!=0 && number_sc!=0 && number_dc!=0 ) {  
    if(Cuts.Test(status(k)>0 , C_proton_status) && Cuts.Test(stat_sc(k)>0, C_proton_stat_sc) && Cuts.Test(stat_dc(k)>0, C_proton_stat_dc)) {
      proton_charge->Fill(charge(k));
      if(Cuts.Test(charge(k) > 0,C_proton_charge)) {
	proton_charge_cut->Fill(charge(k));
	proton_delta_t_p->Fill(moment(k),delta_t_pi(k));
	if(Cuts.Test(delta_t_proton_cut(k) == 1,C_proton_deltat)) {
//	  proton_deltabeta_p_cut->Fill(moment(k),delta_betta(k));/
//	  proton_delta_t_p_cut->Fill(moment(k),delta_t_pi(k));
	  proton_mass->Fill(sqrt(mass2(k)));
	  if(Cuts.Test(( mass2(k)<=1.338 && mass2(k)>0.538) , C_proton_mass)) {
	     proton_mass_cut->Fill(sqrt(mass2(k)));
	    if (Cuts.Test(Pip_id2(k)==0, C_proton_no_pion)) { 
	      proton_id_cut = 1;
	      proton_delta_t_p_cut->Fill(moment(k),delta_t_proton(k));
	    }
	  }
	}
      }
    }
  
  }
  return proton_id_cut;
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
  Int_t bin_W        = 2;
  Int_t bin_t        = 6;
  Int_t bin_delta_E  = 2;
  Int_t bin_thetapip = 12;
  


  Int_t iBin = ( i1) * ( bin_W * bin_t * bin_delta_E * bin_thetapip) +
               ( i2) * (         bin_t * bin_delta_E * bin_thetapip) +
               ( i3) * (                 bin_delta_E * bin_thetapip) +
               ( i4) * (                               bin_thetapip) +
               ( i5) ;

  return iBin;



}

Int_t TPart_id::Get_which_bin(Int_t i, Int_t bin){
  
  Int_t bin_W        = 2;
  Int_t bin_t        = 6;
  Int_t bin_delta_E  = 2;
  Int_t bin_thetapip = 12;

  Int_t bin_val[5];

  bin_val[0] = int(bin/(bin_W * bin_t * bin_delta_E * bin_thetapip));
  bin_val[1] = int(bin/(bin_t * bin_delta_E * bin_thetapip)) - bin_val[0] * bin_W;
  bin_val[2] = int(bin/(bin_delta_E * bin_thetapip)) - bin_val[0] * bin_W * bin_t - bin_val[1] * bin_t;
  bin_val[3] = int(bin/(bin_thetapip)) -  bin_val[0] * bin_W * bin_t * bin_delta_E - bin_val[1] * bin_t * bin_delta_E - bin_val[2]  * bin_delta_E ;
  bin_val[4] = bin- bin_val[0] * bin_W * bin_t * bin_delta_E * bin_thetapip - bin_val[1] * bin_t * bin_delta_E * bin_thetapip - bin_val[2]  * bin_delta_E * bin_thetapip - bin_val[3] * bin_thetapip ;

  return bin_val[i];

}

Int_t TPart_id::Acceptance_data(Int_t i){
  // This will fill with the generator data


  Int_t ox=0;
  Int_t oy=0;
  Int_t oz=0;
  Int_t ot=0;
  Int_t oi=0;
  Int_t ou=0;
  Int_t bin_acc=0;
  Int_t id_v;
  Double_t Q2_v, W_v, t_v, rho_mom_v, theta_pip_v, phi_pip_v, phi_lep_had_v , delta_E_v, mass_rho_v, z_v, lc_v;
  Q2_v = Q2_mc();
  W_v = W_mc();
  t_v = t_mc();
  lc_v = Get_lc_mc();
  delta_E_v = find_Delta_E_mc();
  z_v = find_zrho_mc();
  rho_mom_v = rho_mom_mc();
  theta_pip_v = theta_lam_mc();
  phi_pip_v= phi_lam_mc();
  phi_lep_had_v= phi_lep_had_mc();
  mass_rho_v = invariant_mass_mc();
  // id_v = id_mctk();


  //  printf("generated evnt with Q2= %f ,W= %f , t= %f , rho_mom= %f , theta_pip= %f , phi_pip= %f , phi_l_h= %f \n",Q2_v,W_v,t_v,rho_mom_v,theta_pip_v,phi_pip_v,phi_lep_had_v);

  if (Q2_v >0.7 && Q2_v <2.5 && W_v>1.8 && W_v<3 && t_v>0.05 && t_v<1.00 && theta_pip_v>0 &&  theta_pip_v< (TMath::Pi())) {

    if (i == 1) {
      Q2_gen->Fill(Q2_v);
      W_gen->Fill(W_v);
      t_gen->Fill(t_v);
      rho_mom_gen->Fill(rho_mom_v);
      theta_pip_gen->Fill(theta_pip_v);
      phi_pip_gen->Fill(phi_pip_v);
      phi_l_h_gen->Fill(phi_lep_had_v);
      delta_E_gen->Fill(delta_E_v);
    }


    if(Q2_v >0.7 && Q2_v <(0.7 + double(2)/30)) ox=0; //deciding the binning
    if(Q2_v >(0.7 + double(2)/30) && Q2_v < (0.7 + double(2*2)/30)) ox=1;
    if(Q2_v >(0.7 + double(2*2)/30) && Q2_v < (0.7 + double(2*3)/30)) ox=2;
    if(Q2_v >(0.7 + double(2*3)/30) && Q2_v < (0.7 + double(2*4)/30)) ox=3;
    if(Q2_v >(0.7 + double(2*4)/30) && Q2_v < (0.7 + double(2*5)/30)) ox=4;
    if(Q2_v >(0.7 + double(2*5)/30) && Q2_v < (0.7 + double(2*6)/30)) ox=5;
    if(Q2_v >(0.7 + double(2*6)/30) && Q2_v < (0.7 + double(2*7)/30)) ox=6;
    if(Q2_v >(0.7 + double(2*7)/30) && Q2_v < (0.7 + double(2*8)/30)) ox=7;
    if(Q2_v >(0.7 + double(2*8)/30) && Q2_v < (0.7 + double(2*9)/30)) ox=8;
    if(Q2_v >(0.7 + double(2*9)/30) && Q2_v < (0.7 + double(2*10)/30)) ox=9;
    if(Q2_v >(0.7 + double(2*10)/30) && Q2_v < (0.7 + double(2*11)/30)) ox=10;
    if(Q2_v >(0.7 + double(2*11)/30) && Q2_v < (0.7 + double(2*12)/30)) ox=11;
    if(Q2_v >(0.7 + double(2*12)/30) && Q2_v < (0.7 + double(2*13)/30)) ox=12;
    if(Q2_v >(0.7 + double(2*13)/30) && Q2_v < (0.7 + double(2*14)/30)) ox=13;
    if(Q2_v >(0.7 + double(2*14)/30) && Q2_v < (0.7 + double(2*15)/30)) ox=14;
    if(Q2_v >(0.7 + double(2*15)/30) && Q2_v < (0.7 + double(2*16)/30)) ox=15;
    if(Q2_v >(0.7 + double(2*16)/30) && Q2_v < (0.7 + double(2*17)/30)) ox=16;
    if(Q2_v >(0.7 + double(2*17)/30) && Q2_v < (0.7 + double(2*18)/30)) ox=17;
    if(Q2_v >(0.7 + double(2*18)/30) && Q2_v < (0.7 + double(2*19)/30)) ox=18;
    if(Q2_v >(0.7 + double(2*19)/30) && Q2_v < (0.7 + double(2*20)/30)) ox=19;
    if(Q2_v >(0.7 + double(2*20)/30) && Q2_v < (0.7 + double(2*21)/30)) ox=20;
    if(Q2_v >(0.7 + double(2*21)/30) && Q2_v < (0.7 + double(2*22)/30)) ox=21;
    if(Q2_v >(0.7 + double(2*22)/30) && Q2_v < (0.7 + double(2*23)/30)) ox=22;
    if(Q2_v >(0.7 + double(2*23)/30) && Q2_v < (0.7 + double(2*24)/30)) ox=23;
    if(Q2_v >(0.7 + double(2*24)/30) && Q2_v < (0.7 + double(2*25)/30)) ox=24;
    if(Q2_v >(0.7 + double(2*25)/30) && Q2_v < (0.7 + double(2*26)/30)) ox=25;
    if(Q2_v >(0.7 + double(2*26)/30) && Q2_v < (0.7 + double(2*27)/30)) ox=26;
    if(Q2_v >(0.7 + double(2*27)/30) && Q2_v < (0.7 + double(2*28)/30)) ox=27;
    if(Q2_v >(0.7 + double(2*28)/30) && Q2_v < (0.7 + double(2*29)/30)) ox=28;
    if(Q2_v >(0.7 + double(2*29)/30) && Q2_v < (0.7 + double(2*30)/30)) ox=29;

    if( W_v>1.8 && W_v<2) oy=0;
    if( W_v>2) oy=1;


    if(t_v>0.05 && t_v<=0.1) oz=0;
    if(t_v>0.1 && t_v<=0.18) oz=1;
    if(t_v>0.18 && t_v<=0.26) oz=2;
    if(t_v>0.26 && t_v<=0.33) oz=3;
    if(t_v>0.33 && t_v<0.4) oz=4;
    if(t_v>0.4 && t_v<1) oz=5;

    if(delta_E_v<0.05)   ot=0;
    if(delta_E_v>0.05 && delta_E_v<0.1)   ot=1;
    if(delta_E_v>0.1)   ot=2;
    
    if(z_v <=0.9) ou=0;
    if(z_v >0.9) ou=1;

    if(theta_pip_v>0 &&  theta_pip_v< (TMath::Pi() /12) )                          oi=0;
    if(theta_pip_v> (TMath::Pi() /12) &&  theta_pip_v< (TMath::Pi() /12 *2) )      oi=1;
    if(theta_pip_v> (TMath::Pi() /12 *2) &&  theta_pip_v< (TMath::Pi() /12 *3) )   oi=2;
    if(theta_pip_v> (TMath::Pi() /12 *3) &&  theta_pip_v< (TMath::Pi() /12 *4) )   oi=3;
    if(theta_pip_v> (TMath::Pi() /12 *4) &&  theta_pip_v< (TMath::Pi() /12 *5) )   oi=4;
    if(theta_pip_v> (TMath::Pi() /12 *5) &&  theta_pip_v< (TMath::Pi() /12 *6) )   oi=5; 
    if(theta_pip_v> (TMath::Pi() /12 *6) &&  theta_pip_v< (TMath::Pi() /12 *7) )   oi=6;
    if(theta_pip_v> (TMath::Pi() /12 *7) &&  theta_pip_v< (TMath::Pi() /12 *8) )   oi=7;
    if(theta_pip_v> (TMath::Pi() /12 *8) &&  theta_pip_v< (TMath::Pi() /12 *9) )   oi=8;
    if(theta_pip_v> (TMath::Pi() /12 *9) &&  theta_pip_v< (TMath::Pi() /12 *10) )  oi=9;
    if(theta_pip_v> (TMath::Pi() /12 *10) &&  theta_pip_v< (TMath::Pi() /12 *11) ) oi=10;
    if(theta_pip_v> (TMath::Pi() /12 *11) &&  theta_pip_v< (TMath::Pi() /12 *12) ) oi=11;  

    Acc_Q2_g = ox;
    Acc_W_g = oy;
    Acc_t_g = oz;
    Acc_deltaE_g = ot;
    Acc_z_g = ou;
    Acc_thetapip_g = oi;
    Acc_massrho_g = mass_rho_v;
    Acc_id_g= id_v;
    Acc_Q2_g_v = Q2_v;
    Acc_lc_g_v = lc_v;
    Acc_W_g_v = W_v;
    Acc_t_g_v = t_v;
    Acc_deltaE_g_v = delta_E_v;
    Acc_rhomom_g_v = rho_mom_v;
    Acc_z_g_v = z_v;
    Acc_thetapip_g_v = theta_pip_v;
    


    
    //    printf("generated evnt in the bin %d ,%d ,%d ,%d ,%d ,%d ,%d \n",ox,oy,oz,ot,oi,oj,ok);
    //
    //    mc_gen[ox][oy][oz][ot][oi][oj][ok]->Fill(Q2_v);

    bin_acc = Get_bin_acc(ox,oy,oz,ot,oi);
    // here I will fill the Acceptance array
    if (i==1) {
      generated_evnt_bin->Fill(bin_acc+0.5);
      tree_gen->Fill();	  
    }
  }
  return bin_acc;
}


void TPart_id::Acceptance_rec(Int_t i, Int_t j, Int_t k){
  // This will fill with the reconstructed  data i=pi-  j=pi+ 
  // k=which_target (0=liq, 1=sol)

  Int_t ox=0;
  Int_t oy=0;
  Int_t oz=0;
  Int_t ot=0;
  Int_t oi=0;
  Int_t ou=0;
  Int_t bin_rec=0;
  Int_t bin_gen=0;
  Int_t id_v;
  Double_t Q2_v, W_v, t_v, rho_mom_v, theta_pip_v, phi_pip_v, phi_lep_had_v, delta_E_v, mass_rho_v, z_v, lc_v;
  Q2_v = Q2();
  W_v = W();
  t_v = find_t_rho(0,i,j);
  delta_E_v = find_Delta_E(0,i,j);
  z_v = find_zrho(0,i,j);
  rho_mom_v = rho_mom_ev(i,j);
  theta_pip_v = theta_lam_ev(i,j); // theta_pip_ev(0,i,j)
  phi_pip_v= phi_lam_ev(i,j); // phi_pip_ev(0,i,j)
  phi_lep_had_v= phi_lep_had_ev(0,i,j);
  mass_rho_v = invariant_mass(i,j);
  lc_v = Get_lc(i,j);
  // id_v = id_mctk();

//   Q2_rec->Fill(Q2_v);
//   W_rec->Fill(W_v);
//   t_rec->Fill(t_v);
//   rho_mom_rec->Fill(rho_mom_v);
//   theta_pip_rec->Fill(theta_pip_v);
//   phi_pip_rec->Fill(phi_pip_v);
//   phi_l_h_rec->Fill(phi_lep_had_v);
  Int_t t_kin_v=0;
  //  printf("reconstructed evnt with Q2= %f ,W= %f , t= %f , rho_mom= %f , theta_pip= %f , phi_pip= %f , phi_l_h= %f \n",Q2_v,W_v,t_v,rho_mom_v,theta_pip_v,phi_pip_v,phi_lep_had_v);
  if (Q2_v >0.7 && Q2_v <2.5 && W_v>1.8 && W_v<3 && t_v>0 && t_v<1.00 && theta_pip_v>0 &&  theta_pip_v< (TMath::Pi())) {
    
    if (W_v>2 && z_v>0.9 && t_v>0.1 && t_v <0.4) t_kin_v=1;
    Cuts.Test(t_kin_v==1,C_Good_kin);
    Q2_rec[k]->Fill(Q2_v);
    W_rec[k]->Fill(W_v);
    t_rec[k]->Fill(t_v);
    rho_mom_rec[k]->Fill(rho_mom_v);
    theta_pip_rec[k]->Fill(theta_pip_v);
    phi_pip_rec[k]->Fill(phi_pip_v);
    phi_l_h_rec[k]->Fill(phi_lep_had_v);
    delta_E_rec[k]->Fill(delta_E_v);


    if(Q2_v >0.7 && Q2_v <(0.7 + double(2)/30)) ox=0; //deciding the binning
    if(Q2_v >(0.7 + double(2)/30) && Q2_v < (0.7 + double(2*2)/30)) ox=1;
    if(Q2_v >(0.7 + double(2*2)/30) && Q2_v < (0.7 + double(2*3)/30)) ox=2;
    if(Q2_v >(0.7 + double(2*3)/30) && Q2_v < (0.7 + double(2*4)/30)) ox=3;
    if(Q2_v >(0.7 + double(2*4)/30) && Q2_v < (0.7 + double(2*5)/30)) ox=4;
    if(Q2_v >(0.7 + double(2*5)/30) && Q2_v < (0.7 + double(2*6)/30)) ox=5;
    if(Q2_v >(0.7 + double(2*6)/30) && Q2_v < (0.7 + double(2*7)/30)) ox=6;
    if(Q2_v >(0.7 + double(2*7)/30) && Q2_v < (0.7 + double(2*8)/30)) ox=7;
    if(Q2_v >(0.7 + double(2*8)/30) && Q2_v < (0.7 + double(2*9)/30)) ox=8;
    if(Q2_v >(0.7 + double(2*9)/30) && Q2_v < (0.7 + double(2*10)/30)) ox=9;
    if(Q2_v >(0.7 + double(2*10)/30) && Q2_v < (0.7 + double(2*11)/30)) ox=10;
    if(Q2_v >(0.7 + double(2*11)/30) && Q2_v < (0.7 + double(2*12)/30)) ox=11;
    if(Q2_v >(0.7 + double(2*12)/30) && Q2_v < (0.7 + double(2*13)/30)) ox=12;
    if(Q2_v >(0.7 + double(2*13)/30) && Q2_v < (0.7 + double(2*14)/30)) ox=13;
    if(Q2_v >(0.7 + double(2*14)/30) && Q2_v < (0.7 + double(2*15)/30)) ox=14;
    if(Q2_v >(0.7 + double(2*15)/30) && Q2_v < (0.7 + double(2*16)/30)) ox=15;
    if(Q2_v >(0.7 + double(2*16)/30) && Q2_v < (0.7 + double(2*17)/30)) ox=16;
    if(Q2_v >(0.7 + double(2*17)/30) && Q2_v < (0.7 + double(2*18)/30)) ox=17;
    if(Q2_v >(0.7 + double(2*18)/30) && Q2_v < (0.7 + double(2*19)/30)) ox=18;
    if(Q2_v >(0.7 + double(2*19)/30) && Q2_v < (0.7 + double(2*20)/30)) ox=19;
    if(Q2_v >(0.7 + double(2*20)/30) && Q2_v < (0.7 + double(2*21)/30)) ox=20;
    if(Q2_v >(0.7 + double(2*21)/30) && Q2_v < (0.7 + double(2*22)/30)) ox=21;
    if(Q2_v >(0.7 + double(2*22)/30) && Q2_v < (0.7 + double(2*23)/30)) ox=22;
    if(Q2_v >(0.7 + double(2*23)/30) && Q2_v < (0.7 + double(2*24)/30)) ox=23;
    if(Q2_v >(0.7 + double(2*24)/30) && Q2_v < (0.7 + double(2*25)/30)) ox=24;
    if(Q2_v >(0.7 + double(2*25)/30) && Q2_v < (0.7 + double(2*26)/30)) ox=25;
    if(Q2_v >(0.7 + double(2*26)/30) && Q2_v < (0.7 + double(2*27)/30)) ox=26;
    if(Q2_v >(0.7 + double(2*27)/30) && Q2_v < (0.7 + double(2*28)/30)) ox=27;
    if(Q2_v >(0.7 + double(2*28)/30) && Q2_v < (0.7 + double(2*29)/30)) ox=28;
    if(Q2_v >(0.7 + double(2*29)/30) && Q2_v < (0.7 + double(2*30)/30)) ox=29;


    if( W_v>1.8 && W_v<2) oy=0;
    if( W_v>2) oy=1;


    if(t_v>0.0 && t_v<=0.1) oz=0;
    if(t_v>0.10 && t_v<=0.18) oz=1;
    if(t_v>0.18 && t_v<=0.26) oz=2;
    if(t_v>0.26 && t_v<=0.33) oz=3;
    if(t_v>0.33 && t_v<=0.4) oz=4;
    if(t_v>0.4 && t_v<1) oz=5;


    if(delta_E_v<0.05)   ot=0;
    if(delta_E_v>0.05 && delta_E_v<0.1)   ot=1;
    if(delta_E_v>0.1)   ot=2;
    
    if(z_v <=0.9) ou=0;
    if(z_v >0.9) ou=1;


    if(theta_pip_v>0 &&  theta_pip_v< (TMath::Pi() /12) )                          oi=0;
    if(theta_pip_v> (TMath::Pi() /12) &&  theta_pip_v< (TMath::Pi() /12 *2) )      oi=1;
    if(theta_pip_v> (TMath::Pi() /12 *2) &&  theta_pip_v< (TMath::Pi() /12 *3) )   oi=2;
    if(theta_pip_v> (TMath::Pi() /12 *3) &&  theta_pip_v< (TMath::Pi() /12 *4) )   oi=3;
    if(theta_pip_v> (TMath::Pi() /12 *4) &&  theta_pip_v< (TMath::Pi() /12 *5) )   oi=4;
    if(theta_pip_v> (TMath::Pi() /12 *5) &&  theta_pip_v< (TMath::Pi() /12 *6) )   oi=5; 
    if(theta_pip_v> (TMath::Pi() /12 *6) &&  theta_pip_v< (TMath::Pi() /12 *7) )   oi=6;
    if(theta_pip_v> (TMath::Pi() /12 *7) &&  theta_pip_v< (TMath::Pi() /12 *8) )   oi=7;
    if(theta_pip_v> (TMath::Pi() /12 *8) &&  theta_pip_v< (TMath::Pi() /12 *9) )   oi=8;
    if(theta_pip_v> (TMath::Pi() /12 *9) &&  theta_pip_v< (TMath::Pi() /12 *10) )  oi=9;
    if(theta_pip_v> (TMath::Pi() /12 *10) &&  theta_pip_v< (TMath::Pi() /12 *11) ) oi=10;
    if(theta_pip_v> (TMath::Pi() /12 *11) &&  theta_pip_v< (TMath::Pi() /12 *12) ) oi=11;  
     
   
    //    printf("reconstructed evnt in the bin %d ,%d ,%d ,%d ,%d ,%d ,%d \n",ox,oy,oz,ot,oi,oj,ok);
    //
    //    mc_rec[ox][oy][oz][ot][oi][oj][ok]->Fill(Q2_v);

    // here I will fill the Acceptance array

    bin_rec=Get_bin_acc(ox,oy,oz,ot,oi);
    bin_gen=Acceptance_data(0);
    reconstructed_evnt_bin[k]->Fill(bin_rec+0.5);
    deforming_matrix_inv->Fill(bin_gen+0.5,bin_rec+0.5);

    Acc_Q2_r = ox;
    Acc_W_r = oy;
    Acc_t_r = oz;
    Acc_deltaE_r = ot;
    Acc_z_r = ou;
    Acc_thetapip_r = oi;
    Acc_massrho_r = mass_rho_v;
    Acc_id_r= id_v;
    Acc_tg_r= k;
    Acc_Q2_r_v = Q2_v;
    Acc_lc_r_v = lc_v;
    Acc_W_r_v = W_v;
    Acc_t_r_v = t_v;
    Acc_deltaE_r_v = delta_E_v;
    Acc_rhomom_r_v = rho_mom_v;
    Acc_z_r_v = z_v;
    Acc_thetapip_r_v = theta_pip_v;

    Acc_Q2_g = Get_which_bin(0,bin_gen);
    Acc_W_g = Get_which_bin(1,bin_gen);
    Acc_t_g = Get_which_bin(2,bin_gen);
    Acc_deltaE_g = Get_which_bin(3,bin_gen);
    Acc_thetapip_g = Get_which_bin(4,bin_gen);
    Acc_massrho_g = invariant_mass_mc();
    Acc_id_g = id_v;
    Acc_Q2_g_v = Q2_mc();
    Acc_lc_g_v = Get_lc_mc();
    Acc_W_g_v = W_mc();
    Acc_t_g_v = t_mc();
    Acc_deltaE_g_v = find_Delta_E_mc();
    Acc_rhomom_g_v = rho_mom_mc();
    Acc_z_g_v = find_zrho_mc();
    Acc_thetapip_g_v = theta_lam_mc();


    tree_rec->Fill();
    tree_def->Fill();

  }
  
}


Int_t TPart_id::Run(Int_t Max_evt){

  // Run with Lamiaa Particle ID


  Int_t iEvent;
  Int_t bin_calculated;
  
 

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
      if(Second_electron(ipart)==1 && ipart>0) { 
	second_electron_id_pass++;
	ghost_z = z(0)-z(ipart);
	ghost_p = moment(0) - moment(ipart);
	diff_el_ghost->Fill(ghost_z,ghost_p);
      }
    }  
    if (electron_id_pass == 1 && pip_id_pass > 0 && pim_id_pass > 0 && positron_id_pass ==0 && second_electron_id_pass > 0) diff_el_ghost_rho->Fill(ghost_z,ghost_p);
 
    if (Cuts.Test(electron_id_pass == 1,C_Good_e) && Cuts.Test(pip_id_pass > 0 ,C_Good_pip) && Cuts.Test(pim_id_pass > 0,C_Good_pim) && Cuts.Test(positron_id_pass == 0,C_Good_pos) && Cuts.Test(second_electron_id_pass == 0,C_second_el)) {
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
	pim_deltabeta_p_cut2->Fill(moment(which_pim),delta_betta(which_pim));
	pip_deltabeta_p_cut2->Fill(moment(which_pip),delta_betta(which_pip));
	if (which_target == 1) {
	  //fill liquid target
	  
	  Acceptance_rec(which_pim,which_pip,0);  // filling the
	  // acceptance array histogram
	  zpim_zpip_liq->Fill(z(which_pim),z(which_pip));
	  WH1_cut1_liq->Fill(W());
	  Q2H1_cut1_liq->Fill(Q2());
	  Rho_t_histo_liq->Fill(find_t_rho(electron_id_pos,which_pim,which_pip));
	  Delta_E_histo_liq->Fill(find_Delta_E(electron_id_pos,which_pim,which_pip));
	}
	if (which_target == 2) {
	  //fill solid target
	  
	  Acceptance_rec(which_pim,which_pip,1);  // filling the
	  // acceptance array histogram
	  zpim_zpip_sol->Fill(z(which_pim),z(which_pip));
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
	    Rho_invm_liq->Fill(mass_rho,Q2_value);
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
	    Rho_invm_sol->Fill(mass_rho,Q2_value);
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
      if(Second_electron2(ipart)==1 && ipart>0) {
	second_electron_id_pass++;
	ghost_z = z(0)-z(ipart);
	ghost_p = moment(0) - moment(ipart);
	diff_el_ghost->Fill(ghost_z,ghost_p);
      }
    }	
    if (electron_id_pass == 1 && pip_id_pass > 0 && pim_id_pass > 0 && positron_id_pass ==0 && second_electron_id_pass > 0) diff_el_ghost_rho->Fill(ghost_z,ghost_p);
    if (Cuts.Test(electron_id_pass == 1,C_Good_e) && Cuts.Test(pim_id_pass > 0,C_Good_pim) && Cuts.Test(pip_id_pass > 0,C_Good_pip) && Cuts.Test(positron_id_pass == 0,C_Good_pos) && Cuts.Test(second_electron_id_pass == 0,C_second_el)) {
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
	    if(W()>2) {
	      Rho_invm_liq->Fill(mass_rho,Q2_value);
	      Q2H1_cut2_liq->Fill(Q2_value);
	      // if (id_mctk() == 1) {
	      // 	Rho_invm_liq_id1->Fill(mass_rho,Q2_value);
	      // }
	      // if (id_mctk() == 2) {
	      // 	Rho_invm_liq_id2->Fill(mass_rho,Q2_value);
	      // }
	      // if (id_mctk() == 3) {
	      // 	Rho_invm_liq_id3->Fill(mass_rho,Q2_value);
	      // }
	      // if (id_mctk() == 4) {
	      // 	Rho_invm_liq_id4->Fill(mass_rho,Q2_value);
	      // }
	      // if ( id_mctk() == 2 || id_mctk() == 3 || id_mctk() == 4) {
	      // 	Rho_invm_liq_idbg->Fill(mass_rho,Q2_value);
	      // }
	    }
	    if (Q2_value >= 0.7 && Q2_value <1.15) {
	      Rho_bin1_liq_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin1_liq->Fill(mass_rho);
 		// if (id_mctk() == 1) {
		//   //		  cout << "id = 1" << endl;
		//   Rho_bin1_liq_id1->Fill(mass_rho);
  		// }
		// if (id_mctk() == 2) {
		//  Rho_bin1_liq_id2->Fill(mass_rho);
		// }
		// if (id_mctk() == 3) {
		//  Rho_bin1_liq_id3->Fill(mass_rho);
		// }
		// if (id_mctk() == 4) {
		//  Rho_bin1_liq_id4->Fill(mass_rho);
		// }
		// if ( id_mctk() == 2 || id_mctk() == 3 || id_mctk() == 4 ) {
		//  Rho_bin1_liq_idbg->Fill(mass_rho);
		// }
	      }
	      if (W()>2.2) {
		Rho_bin1_liq_W22->Fill(mass_rho);
	      }
	    }
	    if (Q2_value >= 1.15 && Q2_value <1.4) {
	      Rho_bin2_liq_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin2_liq->Fill(mass_rho);
		// if (id_mctk() == 1) {
		//  Rho_bin2_liq_id1->Fill(mass_rho);
		// }
		// if (id_mctk() == 2) {
		//   Rho_bin2_liq_id2->Fill(mass_rho); 
		// }
		// if (id_mctk() == 3) {
		//  Rho_bin2_liq_id3->Fill(mass_rho);
		// }
		// if (id_mctk() == 4) {
		//  Rho_bin2_liq_id4->Fill(mass_rho);
		// }
		// if ( id_mctk() == 2 || id_mctk() == 3 || id_mctk() == 4 ) {
		//  Rho_bin2_liq_idbg->Fill(mass_rho);
		// }
	      }
	      if (W()>2.2) {
		Rho_bin2_liq_W22->Fill(mass_rho);
	      }
	    }     
	    if (Q2_value >= 1.4 && Q2_value <2) {
	      Rho_bin3_liq_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin3_liq->Fill(mass_rho);
		// if (id_mctk() == 1) {
		//  Rho_bin3_liq_id1->Fill(mass_rho);
		// }
		// if (id_mctk() == 2) {
		//  Rho_bin3_liq_id2->Fill(mass_rho);
		// }
		// if (id_mctk() == 3) {
		//  Rho_bin3_liq_id3->Fill(mass_rho);
		// }
		// if (id_mctk() == 4) {
		//  Rho_bin3_liq_id4->Fill(mass_rho);
		// }
		// if ( id_mctk() == 2 || id_mctk() == 3 || id_mctk() == 4 ) {
		//  Rho_bin3_liq_idbg->Fill(mass_rho);
		// }
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
	    if(W()>2) {
	      Rho_invm_sol->Fill(mass_rho,Q2_value);
	      Q2H1_cut2_sol->Fill(Q2_value);
	      // if (id_mctk() == 1) {
	      // 	Rho_invm_sol_id1->Fill(mass_rho,Q2_value);
	      // }
	      // if (id_mctk() == 2) {
	      // 	Rho_invm_sol_id2->Fill(mass_rho,Q2_value);
	      // }
	      // if (id_mctk() == 3) {
	      // 	Rho_invm_sol_id3->Fill(mass_rho,Q2_value);
	      // }
	      // if (id_mctk() == 4) {
	      // 	Rho_invm_sol_id4->Fill(mass_rho,Q2_value);
	      // }
	      // if ( id_mctk() == 2 || id_mctk() == 3 || id_mctk() == 4) {
	      // 	Rho_invm_sol_idbg->Fill(mass_rho,Q2_value);
	      // }
	    }
	    if (Q2_value >= 0.7 && Q2_value <1.15) {
	      Rho_bin1_sol_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin1_sol->Fill(mass_rho);
 		// if (id_mctk() == 1) {
		//   //		  cout << "id = 1" << endl;
		//   Rho_bin1_sol_id1->Fill(mass_rho);
 		// }
		// if (id_mctk() == 2) {
		//  Rho_bin1_sol_id2->Fill(mass_rho);
		// }
		// if (id_mctk() == 3) {
		//  Rho_bin1_sol_id3->Fill(mass_rho);
		// }
		// if (id_mctk() == 4) {
		//  Rho_bin1_sol_id4->Fill(mass_rho);
		// }
		// if ( id_mctk() == 2 || id_mctk() == 3 || id_mctk() == 4 ) {
		//  Rho_bin1_sol_idbg->Fill(mass_rho);
		// }
	      }
	      if (W()>2.2) {
		Rho_bin1_sol_W22->Fill(mass_rho);
	      }
	    }
	    if (Q2_value >= 1.15 && Q2_value <1.4) {
	      Rho_bin2_sol_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin2_sol->Fill(mass_rho);
		// if (id_mctk() == 1) {
		//  Rho_bin2_sol_id1->Fill(mass_rho);
		// }
		// if (id_mctk() == 2) {
		//  Rho_bin2_sol_id2->Fill(mass_rho);
		// }
		// if (id_mctk() == 3) {
		//  Rho_bin2_sol_id3->Fill(mass_rho);
		// }
		// if (id_mctk() == 4) {
		//  Rho_bin2_sol_id4->Fill(mass_rho);
		// }
		// if ( id_mctk() == 2 || id_mctk() == 3 || id_mctk() == 4 ) {
		//  Rho_bin2_sol_idbg->Fill(mass_rho);
		// }
	      }
	      if (W()>2.2) {
		Rho_bin2_sol_W22->Fill(mass_rho);
	      }
	    }     
	    if (Q2_value >= 1.4 && Q2_value <2) {
	      Rho_bin3_sol_W18->Fill(mass_rho);
	      if (W()>2) {
		Rho_bin3_sol->Fill(mass_rho);
		// if (id_mctk() == 1) {
		//  Rho_bin3_sol_id1->Fill(mass_rho);
		// }
		// if (id_mctk() == 2) {
		//  Rho_bin3_sol_id2->Fill(mass_rho);
		// }
		// if (id_mctk() == 3) {
		//  Rho_bin3_sol_id3->Fill(mass_rho);
		// }
		// if (id_mctk() == 4) {
		//  Rho_bin3_sol_id4->Fill(mass_rho);
		// }
		// if ( id_mctk() == 2 || id_mctk() == 3 || id_mctk() == 4 ) {
		//  Rho_bin3_sol_idbg->Fill(mass_rho);
		// }
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

Int_t TPart_id::Run_pknock(Int_t Max_evt){

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
    which_target = 0;
    electron_id_pass = 0;
    proton_id_pass = 0;
    good_event_towrite = 0;
    for(Int_t ipart=0;ipart<GetNPart();ipart++){	
      if(ipart==0 && Electron_id2(ipart)==1) {
	electron_id_pos = ipart;
	electron_id_pass++;
      }
      if(Proton_id2(ipart)==1) {
	proton_id_pos[proton_id_pass] = ipart;
	proton_id_pass++;
      }
    }	
    if (Cuts.Test(electron_id_pass == 1,C_Good_e) && Cuts.Test(proton_id_pass > 0,C_Good_proton) ) {
      which_target = vertex_cut_elec();
      if (Cuts.Test(which_target==2,C_proton_z)) {
	good_event_towrite = 1;     
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








  
  
