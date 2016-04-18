#include <strstream>
//#include "/net/home/lzana/Eg2/Code/Clas/TPart_Carbon/TPart_id.h"
#include "/home/lzana/jlab_software/1.2/Linux_Ubuntu12.04-x86_64-gcc4.6/ClasTool/My_analysis/Acceptance/TPart_id.h"

TString MakeOutFileName(const char *infile){
  TString file(infile);
  //  cout << "Make out file from: " << file << endl;
  file.ReplaceAll("home/lzana/Eg2/Data/New_Cooking","data/pumpkin1/lzana/Carbon/New_Cooking");
  file.ReplaceAll("clas_","elec_");
  file.ReplaceAll("_*","");
  file.ReplaceAll(".pass2","");
  // cout << "Got: " << file << endl;
  return file;
}

void Filter(const char* file,const char* outfile){
  TStopwatch time;
  time.Start();
 TFile fo(outfile,"RECREATE","Filtered on electrons");
  if(fo.IsOpen()){
    cout << "Opened " << outfile << " for output.\n";
  }else{
    cout << "ERROR ***** Could not open " <<file << " for output.\n";
    gSystem->Exit(999);
  }
  TPart_id *t= new TPart_id();
  t->InitDSTReader();
  t->SetNoScalers();
  t->SetBeamEnergy(5.01483);
  cout << "Adding: " << file << endl;
  t->Add(file);
  cout << "Loaded " << t->GetNFiles() << " files from EG2" << endl;
//   TFile fo(outfile,"RECREATE","Filtered on electrons");
//   if(fo.IsOpen()){
//     cout << "Opened " << outfile << " for output.\n";
//   }else{
//     cout << "ERROR ***** Could not open " <<file << " for output.\n";
//     gSystem->Exit(999);
//   }

  t->Run_pknock(100000);
  t->Write();
  fo.Write();
  fo.Close();
  delete t;    // CLEANUP
  time.Stop();
  cout << "TPart_id.C has finished for: " << file << endl;
  cout << "Total running time: ";
  time.Print();
  cout << "--------------------------------------------------------------------" << endl;
}


FilterAll(Int_t run_low,Int_t run_high)
{
  ostringstream base_name;
  ostringstream inf_name;
  string lamiaa_root  ="/net/home/lzana/Eg2/Data/New_Cooking";
  Bool_t filefound;
  for(Int_t i=run_low;i<=run_high;i++){
    filefound=kFALSE;
    base_name.str("");
    //    base_name << taro_root;
    base_name << lamiaa_root;
    base_name << "/clas_";
    base_name << i << "_";
    inf_name.str("");
    inf_name<< base_name.str();
    inf_name << "00.pass2.root";
    // cout << "Trying " << inf_name.str().data() << endl;
    if(gSystem->AccessPathName(inf_name.str().data())==0){
      inf_name.str("");
      inf_name << base_name.str();
      inf_name << "*.root";
      filefound=kTRUE;
    }
    if(filefound){
      // cout << "File found: " << inf_name.str().data() << endl;
      TString outfile=MakeOutFileName(inf_name.str().data());
      if(gSystem->AccessPathName(outfile.Data())==0){
        cout << outfile.Data() << " already exists." << endl;
      }else{
        cout << "Filtering to: " << outfile.Data() << endl;
        Filter(inf_name.str().data(),outfile.Data());
      }
    }
  }
}



