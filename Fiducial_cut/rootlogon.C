{
gSystem->Load("libTree.so");
gSystem->Load("libPhysics.so");
gSystem->Load("/net/home/lzana/packages/ClasTool/slib/Linux64RHEL5/libClasBanks.so");
gSystem->Load("/net/home/lzana/packages/ClasTool/slib/Linux64RHEL5/libClasTool.so");
gSystem->Load("libEG.so");
gSystem->Load("/net/home/lzana/Eg2/Code/Clas_5.20/Fiducial_cut/Tools_fidc_C.so");
gSystem->Load("/net/home/lzana/packages/ClasTool/slib/Linux64RHEL5/libFidCut.so");
gSystem->Load("/net/home/lzana/packages/ClasTool/slib/Linux64RHEL5/libAccept_ct.so");
gSystem->Load("/net/home/lzana/packages/ClasTool/slib/Linux64RHEL5/libAcc_id.so");

//..BABAR style from RooLogon.C in workdir
TStyle *babarStyle= new TStyle("BABAR","BaBar approved plots style");

// use plain black on white colors
babarStyle->SetFrameBorderMode(0);
babarStyle->SetCanvasBorderMode(0);
babarStyle->SetPadBorderMode(0);
babarStyle->SetPadColor(0);
babarStyle->SetCanvasColor(0);
babarStyle->SetStatColor(0);
babarStyle->SetFillColor(1);
babarStyle->SetPalette(1);

// set the paper & margin sizes
babarStyle->SetPaperSize(20,26);
babarStyle->SetPadTopMargin(0.05);
babarStyle->SetPadRightMargin(0.15);
babarStyle->SetPadBottomMargin(0.16);
babarStyle->SetPadLeftMargin(0.12);
babarStyle->SetCanvasDefX(12);
babarStyle->SetCanvasDefY(16);
babarStyle->SetCanvasDefW(695);

// use large Times-Roman fonts
babarStyle->SetTextFont(132);
babarStyle->SetTextSize(0.08);
babarStyle->SetLabelOffset(0.02,"x");
babarStyle->SetLabelOffset(0.02,"y");
babarStyle->SetLabelFont(132,"x");
babarStyle->SetLabelFont(132,"y");
babarStyle->SetLabelFont(132,"z");
babarStyle->SetLabelSize(0.05,"x");
babarStyle->SetTitleSize(0.06,"x");
babarStyle->SetLabelSize(0.05,"y");
babarStyle->SetTitleSize(0.06,"y");
babarStyle->SetLabelSize(0.05,"z");
babarStyle->SetTitleSize(0.06,"z");

// use bold lines and markers
//babarStyle->SetMarkerStyle(20);
babarStyle->SetHistLineWidth(1.85);
babarStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

// get rid of X error bars and y error bar caps
babarStyle->SetErrorX(0.001);

// do not display any of the standard histogram decorations
babarStyle->SetOptTitle(0);
babarStyle->SetOptStat(0);
babarStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
babarStyle->SetPadTickX(1);
babarStyle->SetPadTickY(1);




}
