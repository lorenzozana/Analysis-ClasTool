#ifndef _TFidCut_
#define _TFidCut_


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include "TSystem.h"
#include "TVector3.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TString.h"
#include "/net/home/lzana/packages/ClasTool/include/THEADERClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TEVNTClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TECPBClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TCCPBClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TDCPBClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TSCPBClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TDSTReader.h"
Double_t fitf5(Double_t *y, Double_t *par2);




class TFidCut{


 private:


  TString fInFile;
  TF1* fcfun[7][2][4];
  TF1* fcfidc_fun[2];



 public:
  
  TFidCut(Char_t* FileName); 
  Int_t CheckCut(TVector3 Vector);

};
#endif
