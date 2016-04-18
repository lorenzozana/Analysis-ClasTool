
#include "TF1.h"
/*
#include "/net/home/lzana/packages/ClasTool/include/THEADERClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TEVNTClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TECPBClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TCCPBClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TDCPBClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TSCPBClass.h"
#include "/net/home/lzana/packages/ClasTool/include/TDSTReader.h"*/




Double_t fitf5(Double_t *y, Double_t *par2)
{
  // par2[4] is 1 for the upper part (p1) and -1 for the lower (p0)
  // par2[5] is the sector number

  
  Double_t arg = 0., fitval = 0.;
  arg = y[0];
  if(arg <= par2[2] || arg >= par2[3]) fitval = 60.*(par2[5] - 1); 
  else fitval = 60.*(par2[5] - 1) + par2[4]*par2[0]*(1. - 1./((arg - par2[2])/(par2[1]) + 1.));
 
  return fitval;
}
