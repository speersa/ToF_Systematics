////////////////////////////////////////////////////////////
//
//  Author: Ciro Riccio
//  email: riccioc<at>na.infn.it
//
//  usage: root 'ToFGaussianFit.C()'
//  
//
////////////////////////////////////////////////////////////

void dofit(TH1F *h_tof_magnet, TH1F *h_tof_data, TCanvas* c, TString varname, TString Xlabel);

int mc_color = 4; //Plot colour for whatever is loaded as "run4air_mc"
int data_color = 3; //Plot colour for whatever is loaded as "run4air_data"

const char * legend_entry_1 = "P7 MC"; //Legend entry for whatever is loaded as "run4air_mc"
const char * legend_entry_2 = "P7 Data"; //Legend entry for whatever is loaded as "run4air_data"

const char * pdf_title = "P7 run6 MC Data";

void Root_ToFGaussianFit(){

  //=== Inizialize DrawingTools                                                                         
  DrawingTools draw("/home/t2k/aspeers/PROD7_validation/testing/MultiPiAnalysis_TEST.root");//option 3 for T2KStyle = publication/paper
  //draw.SetStackFillStyle(3254);

  gROOT->SetBatch();
  //gStyle->SetOptTitle(0);
  gStyle->SetPadLeftMargin(0.10);
  gStyle->SetPadRightMargin(0.23); 
  TCanvas* canvas = new TCanvas("canvas", "canvas"); //Dummy canvas to make gPad initialisation work in the next line
  //gPad->Print(Form("%s.pdf[", pdf_title));

  //=== Inizialize Experiment     
  Experiment exp("nd280");

  //=== MC samples 
  DataSample* run4air_mc     = new DataSample("/data/aspeers/ToF_Systematics/P7_V12_FHC_run6_MC_default_settings_OFFICIAL.root");
 
  //=== Data samples 

  DataSample* run4air_data   = new DataSample("/data/aspeers/ToF_Systematics/P7_V13_FHC_run6_Data_default_settings_OFFICIAL.root");
  
 // DataSample* run4water_data = new DataSample("/lustrehome/riccioc/hl2_output/ToFSyst/FGD/data/run4water/ToFSyst_run4waterdata.root");
 // DataSample* run5c_data     = new DataSample("/lustrehome/riccioc/hl2_output/ToFSyst/FGD/data/run5c/ToFSyst_run5cdata.root");
 // DataSample* run6_data      = new DataSample("/lustrehome/riccioc/hl2_output/ToFSyst/FGD/data/run6/ToFSyst_run6data.root");
 // DataSample* run7b_data     = new DataSample("/lustrehome/riccioc/hl2_output/ToFSyst/FGD/data/run7b/ToFSyst_run7bdata.root");
 // DataSample* run8water_data     = new DataSample("/data/aspeers/ToF_Systematics/P7_V13_FHC_run8water_Data_default_settings_OFFICIAL.root");

  //=== Inizialize sample group                                                                        

  SampleGroup run4air("run4air");
  run4air.AddDataSample(run4air_data);
  run4air.AddMCSample("magnet", run4air_mc);

  exp.AddSampleGroup( "run4air",   run4air    );
 
 TFile *fm = TFile::Open("/home/t2k/aspeers/ToF_Systematics/Gaussian_Plots_and_Macros/Gaussian_MC.root","RECREATE");
 fm->Close();
 
 TFile *fd = TFile::Open("/home/t2k/aspeers/ToF_Systematics/Gaussian_Plots_and_Macros/Gaussian_Data.root","RECREATE");
 fd->Close();

  TString Fgd1Fwdvar[] = {
    "Fgd1Fwd_ToF_FGD1_FGD2",
    "Fgd1Fwd_ToF_ECal_FGD1_track",
    "Fgd1Fwd_ToF_ECal_FGD1_shower",
    "Fgd1Fwd_ToF_DSECal_FGD1_track",
    "Fgd1Fwd_ToF_DSECal_FGD1_shower"
  };
  
  Int_t tmp0 = sizeof(Fgd1Fwdvar)/sizeof(TString);
  const Int_t NFgd1Fwdvar = tmp0;

  TString Fgd1FwdYaxisLabel[] = {
    "ToF FGD1-FGD2",
    "ToF BrECal-FGD1",
    "ToF BrECal-FGD1",
    "ToF DSECal-FGD1",
    "ToF DSECal-FGD1"
  };

  TCanvas* canvasFgd1Fwd[NFgd1Fwdvar];
  for(int ivar=0; ivar<NFgd1Fwdvar; ivar++){
    canvasFgd1Fwd[ivar] = new TCanvas(Form("%s",Fgd1Fwdvar[ivar].Data()),Form("%s",Fgd1Fwdvar[ivar].Data()),1);
    canvasFgd1Fwd[ivar]->Draw();
    if(ivar==0) draw.SetLegendPos("r");
    else draw.SetLegendPos("l");
    draw.SetOptStat("");
	draw.SetTitle(Form("%s",Fgd1Fwdvar[ivar].Data()));
	//draw.SetTitle("TEST");
    draw.SetTitleY("Events");
    draw.SetTitleX(Form("%s",Fgd1FwdYaxisLabel[ivar].Data()));     

    draw.Draw(exp,"all","magnet",Form("%s[0]",Fgd1Fwdvar[ivar].Data()),80,-20,20,"all","NFgd1Fwd>0","","NODATA");
    TH1F* hmagnet = (TH1F*)draw.GetLastStackTotal();
 
   // draw.Draw(exp,"all","sandmuon",Form("%s[0]",Fgd1Fwdvar[ivar].Data()),80,-20,20,"all","NFgd1Fwd>0","","NODATA");
   // TH1F* hsand = (TH1F*)draw.GetLastStackTotal();

    draw.Draw(exp,Form("%s[0]",Fgd1Fwdvar[ivar].Data()),80,-20,20,"all","NFgd1Fwd>0","","NOMC");
    TH1F* hdata = (TH1F*)draw.GetLastHisto();

    dofit(hmagnet, hdata, canvasFgd1Fwd[ivar], Fgd1Fwdvar[ivar], Fgd1FwdYaxisLabel[ivar]);

  } 

 TString Fgd1Bwdvar[] = {
    "Fgd1Bwd_ToF_P0D_FGD1_track",
    "Fgd1Bwd_ToF_P0D_FGD1_shower",
    "Fgd1Bwd_ToF_ECal_FGD1_track",
    "Fgd1Bwd_ToF_ECal_FGD1_shower" 
  };
  Int_t tmp1 = sizeof(Fgd1Bwdvar)/sizeof(TString);
  const Int_t NFgd1Bwdvar = tmp1;

  TString Fgd1BwdYaxisLabel[] = {
    "ToF P0D-FGD1",
    "ToF P0D-FGD1",
    "ToF BrECal-FGD1",
    "ToF BrECal-FGD1"
  };
  
  TCanvas* canvasFgd1Bwd[NFgd1Bwdvar];
  for(int ivar=0; ivar<NFgd1Bwdvar; ivar++){
    canvasFgd1Bwd[ivar] = new TCanvas(Form("%s_vs_%s",Fgd1Bwdvar[ivar].Data()),Form("%s_vs_%s",Fgd1Bwdvar[ivar].Data()),1);
    canvasFgd1Bwd[ivar]->Draw();
    draw.SetLegendPos("r");
    draw.SetOptStat("");
	draw.SetTitle(Form("%s",Fgd1Bwdvar[ivar].Data()));
    draw.SetTitleY("Events");
    draw.SetTitleX(Form("%s",Fgd1BwdYaxisLabel[ivar].Data()));     
  
    if(ivar<2){
      draw.Draw(exp,"all","magnet",Form("%s[0]",Fgd1Bwdvar[ivar].Data()),80,-20,20,"all","NFgd1Bwd>0","","NODATA");
      TH1F* hmagnet = (TH1F*)draw.GetLastStackTotal();

    //  draw.Draw(exp,"all","sandmuon",Form("%s[0]",Fgd1Bwdvar[ivar].Data()),80,-20,20,"all","NFgd1Bwd>0","","NODATA");
    //  TH1F* hsand = (TH1F*)draw.GetLastStackTotal();

      draw.Draw(exp,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),80,-20,20,"all","NFgd1Bwd>0","","NOMC");
      TH1F* hdata = (TH1F*)draw.GetLastHisto();
    }
    else{
      draw.Draw(exp,"all","magnet",Form("%s[0]",Fgd1Bwdvar[ivar].Data()),80,-20,20,"all","NFgd1Bwd>0 && Fgd1Bwd_isECAL!=-1","","NODATA");
      TH1F* hmagnet = (TH1F*)draw.GetLastStackTotal();

      draw.Draw(exp,"all","sandmuon",Form("%s[0]",Fgd1Bwdvar[ivar].Data()),80,-20,20,"all","NFgd1Bwd>0 && Fgd1Bwd_isECAL!=-1","","NODATA");
      TH1F* hsand = (TH1F*)draw.GetLastStackTotal();

      draw.Draw(exp,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),80,-20,20,"all","NFgd1Bwd>0 && Fgd1Bwd_isECAL!=-1","","NOMC");
      TH1F* hdata = (TH1F*)draw.GetLastHisto();      
    }

    dofit(hmagnet, hdata, canvasFgd1Bwd[ivar], Fgd1Bwdvar[ivar], Fgd1BwdYaxisLabel[ivar]);

  }  

  TString Fgd1HAFwdvar[] = {
    "Fgd1HAFwd_ToF_ECal_FGD1_track",
    "Fgd1HAFwd_ToF_ECal_FGD1_shower"
  };
  Int_t tmp2 = sizeof(Fgd1HAFwdvar)/sizeof(TString);
  const Int_t NFgd1HAFwdvar = tmp2;
   
  TString Fgd1HAFwdYaxisLabel[] = {
    "ToF BrECal-FGD1",
    "ToF BrECal-FGD1"
  };

  TCanvas* canvasFgd1HAFwd[NFgd1HAFwdvar];
  for(int ivar=0; ivar<NFgd1HAFwdvar; ivar++){
    canvasFgd1HAFwd[ivar] = new TCanvas(Form("%s",Fgd1HAFwdvar[ivar].Data()),Form("%s",Fgd1HAFwdvar[ivar].Data()),1);
    canvasFgd1HAFwd[ivar]->Draw();
    draw.SetLegendPos("r");
    draw.SetOptStat("");
	draw.SetTitle(Form("%s",Fgd1HAFwdvar[ivar].Data()));
    draw.SetTitleY("Events");
    draw.SetTitleX(Form("%s",Fgd1HAFwdYaxisLabel[ivar].Data()));     

    draw.Draw(exp,"all","magnet",Form("%s[0]",Fgd1HAFwdvar[ivar].Data()),80,-20,20,"all","NFgd1HAFwd>0","","NODATA");
    TH1F* hmagnet = (TH1F*)draw.GetLastStackTotal();

   // draw.Draw(exp,"all","sandmuon",Form("%s[0]",Fgd1HAFwdvar[ivar].Data()),80,-20,20,"all","NFgd1HAFwd>0","","NODATA");
   // TH1F* hsand = (TH1F*)draw.GetLastStackTotal();

    draw.Draw(exp,Form("%s[0]",Fgd1HAFwdvar[ivar].Data()),80,-20,20,"all","NFgd1HAFwd>0","","NOMC");
    TH1F* hdata = (TH1F*)draw.GetLastHisto();

    dofit(hmagnet, hdata, canvasFgd1HAFwd[ivar], Fgd1HAFwdvar[ivar], Fgd1HAFwdYaxisLabel[ivar]);

  }  
  
 
  TString Fgd1HABwdvar[] = {
    "Fgd1HABwd_ToF_ECal_FGD1_track",
    "Fgd1HABwd_ToF_ECal_FGD1_shower" 
  };
  Int_t   tmp3 = sizeof(Fgd1HABwdvar)/sizeof(TString);
  const Int_t NFgd1HABwdvar = tmp3;

  TString Fgd1HABwdYaxisLabel[] = {
    "ToF BrECal-FGD1",
    "ToF BrECal-FGD1"
  };

  TCanvas* canvasFgd1HABwd[NFgd1HABwdvar];
  for(int ivar=0; ivar<NFgd1HABwdvar; ivar++){
    canvasFgd1HABwd[ivar] = new TCanvas(Form("%s_vs_%s",Fgd1HABwdvar[ivar].Data()),Form("%s_vs_%s",Fgd1HABwdvar[ivar].Data()),1);
    canvasFgd1HABwd[ivar]->Draw();
    draw.SetLegendPos("r");
    draw.SetOptStat("");
	draw.SetTitle(Form("%s",Fgd1HABwdvar[ivar].Data()));
    draw.SetTitleY("Events");
    draw.SetTitleX(Form("%s",Fgd1HABwdYaxisLabel[ivar].Data()));     
    
    draw.Draw(exp,"all","magnet",Form("%s[0]",Fgd1HABwdvar[ivar].Data()),80,-20,20,"all","NFgd1HABwd>0","","NODATA");
    TH1F* hmagnet = (TH1F*)draw.GetLastStackTotal();

    //draw.Draw(exp,"all","sandmuon",Form("%s[0]",Fgd1HABwdvar[ivar].Data()),80,-20,20,"all","NFgd1HABwd>0","","NODATA");
   // TH1F* hsand = (TH1F*)draw.GetLastStackTotal();

    draw.Draw(exp,Form("%s[0]",Fgd1HABwdvar[ivar].Data()),80,-20,20,"all","NFgd1HABwd>0","","NOMC");
    TH1F* hdata = (TH1F*)draw.GetLastHisto();

    dofit(hmagnet, hdata, canvasFgd1HABwd[ivar], Fgd1HABwdvar[ivar], Fgd1HABwdYaxisLabel[ivar]);
 
  } 

  TString Fgd2Fwdvar[] = {
    "Fgd2Fwd_ToF_ECal_FGD2_track",
    "Fgd2Fwd_ToF_ECal_FGD2_shower",
    "Fgd2Fwd_ToF_DSECal_FGD2_track",
    "Fgd2Fwd_ToF_DSECal_FGD2_shower"
  };
  
  Int_t tmp4 = sizeof(Fgd2Fwdvar)/sizeof(TString);
  const Int_t NFgd2Fwdvar = tmp4;

  TString Fgd2FwdYaxisLabel[] = {
    "ToF BrECal-FGD2",
    "ToF BrECal-FGD2",
    "ToF DSECal-FGD2",
    "ToF DSECal-FGD2"
  };

  TCanvas* canvasFgd2Fwd[NFgd2Fwdvar];
  for(int ivar=0; ivar<NFgd2Fwdvar; ivar++){
    canvasFgd2Fwd[ivar] = new TCanvas(Form("%s",Fgd2Fwdvar[ivar].Data()),Form("%s",Fgd2Fwdvar[ivar].Data()),1);
    canvasFgd2Fwd[ivar]->Draw();
    if(ivar==0) draw.SetLegendPos("r");
    else draw.SetLegendPos("l");
    draw.SetOptStat("");
	draw.SetTitle(Form("%s",Fgd2Fwdvar[ivar].Data()));
    draw.SetTitleY("Events");
    draw.SetTitleX(Form("%s",Fgd2FwdYaxisLabel[ivar].Data()));     
    
    draw.Draw(exp,"all","magnet",Form("%s[0]",Fgd2Fwdvar[ivar].Data()),80,-20,20,"all","NFgd2Fwd>0","","NODATA");
    TH1F* hmagnet = (TH1F*)draw.GetLastStackTotal();

    //draw.Draw(exp,"all","sandmuon",Form("%s[0]",Fgd2Fwdvar[ivar].Data()),80,-20,20,"all","NFgd2Fwd>0","","NODATA");
    //TH1F* hsand = (TH1F*)draw.GetLastStackTotal();

    draw.Draw(exp,Form("%s[0]",Fgd2Fwdvar[ivar].Data()),80,-20,20,"all","NFgd2Fwd>0","","NOMC");
    TH1F* hdata = (TH1F*)draw.GetLastHisto();

    dofit(hmagnet, hdata, canvasFgd2Fwd[ivar], Fgd2Fwdvar[ivar], Fgd2FwdYaxisLabel[ivar]);
  } 

  TString Fgd2Bwdvar[] = {
    "Fgd2Bwd_ToF_FGD1_FGD2",
    "Fgd2Bwd_ToF_ECal_FGD2_track",
    "Fgd2Bwd_ToF_ECal_FGD2_shower" 
  };
  Int_t tmp5 = sizeof(Fgd2Bwdvar)/sizeof(TString);
  const Int_t NFgd2Bwdvar = tmp5;

  TString Fgd2BwdYaxisLabel[] = {
    "ToF FGD1-FGD2",
    "ToF BrECal-FGD2",
    "ToF BrECal-FGD2"
  };
    
  TCanvas* canvasFgd2Bwd[NFgd2Bwdvar];
  for(int ivar=0; ivar<NFgd2Bwdvar; ivar++){
    canvasFgd2Bwd[ivar] = new TCanvas(Form("%s_vs_%s",Fgd2Bwdvar[ivar].Data()),Form("%s_vs_%s",Fgd2Bwdvar[ivar].Data()),1);
    canvasFgd2Bwd[ivar]->Draw();
    draw.SetLegendPos("r");
    draw.SetOptStat("");
	draw.SetTitle(Form("%s",Fgd2Bwdvar[ivar].Data()));
    draw.SetTitleY("Events");
    draw.SetTitleX(Form("%s",Fgd2BwdYaxisLabel[ivar].Data()));     
    
    if(ivar==0){
      draw.Draw(exp,"all","magnet",Form("%s[0]",Fgd2Bwdvar[ivar].Data()),80,-20,20,"all","NFgd2Bwd>0","","NODATA");
      TH1F* hmagnet = (TH1F*)draw.GetLastStackTotal();

      //draw.Draw(exp,"all","sandmuon",Form("%s[0]",Fgd2Bwdvar[ivar].Data()),80,-20,20,"all","NFgd2Bwd>0","","NODATA");
      //TH1F* hsand = (TH1F*)draw.GetLastStackTotal();

      draw.Draw(exp,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),80,-20,20,"all","NFgd2Bwd>0","","NOMC");
      TH1F* hdata = (TH1F*)draw.GetLastHisto();
    }
    else{
      draw.Draw(exp,"all","magnet",Form("%s[0]",Fgd2Bwdvar[ivar].Data()),80,-20,20,"all","NFgd2Bwd>0 && Fgd2Bwd_isECAL!=-1","","NODATA");
      TH1F* hmagnet = (TH1F*)draw.GetLastStackTotal();

      draw.Draw(exp,"all","sandmuon",Form("%s[0]",Fgd2Bwdvar[ivar].Data()),80,-20,20,"all","NFgd2Bwd>0 && Fgd2Bwd_isECAL!=-1","","NODATA");
      TH1F* hsand = (TH1F*)draw.GetLastStackTotal();

      draw.Draw(exp,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),80,-20,20,"all","NFgd2Bwd>0 && Fgd2Bwd_isECAL!=-1","","NOMC");
      TH1F* hdata = (TH1F*)draw.GetLastHisto();
    } 

    dofit(hmagnet, hdata, canvasFgd2Bwd[ivar], Fgd2Bwdvar[ivar], Fgd2BwdYaxisLabel[ivar]);
 
  }  

  TString Fgd2HAFwdvar[] = {
    "Fgd2HAFwd_ToF_ECal_FGD2_track",
    "Fgd2HAFwd_ToF_ECal_FGD2_shower"
  };
  Int_t tmp6 = sizeof(Fgd2HAFwdvar)/sizeof(TString);
  const Int_t NFgd2HAFwdvar = tmp6;
   
  TString Fgd2HAFwdYaxisLabel[] = {
    "ToF BrECal-FGD2",
    "ToF BrECal-FGD2"
  };

  TCanvas* canvasFgd2HAFwd[NFgd2HAFwdvar];
  for(int ivar=0; ivar<NFgd2HAFwdvar; ivar++){
    canvasFgd2HAFwd[ivar] = new TCanvas(Form("%s",Fgd2HAFwdvar[ivar].Data()),Form("%s",Fgd2HAFwdvar[ivar].Data()),1);
    canvasFgd2HAFwd[ivar]->Draw();
    draw.SetLegendPos("r");
    draw.SetOptStat("");
	draw.SetTitle(Form("%s",Fgd2HAFwdvar[ivar].Data()));
    draw.SetTitleY("Events");
    draw.SetTitleX(Form("%s",Fgd2HAFwdYaxisLabel[ivar].Data()));     
    
    draw.Draw(exp,"all","magnet",Form("%s[0]",Fgd2HAFwdvar[ivar].Data()),80,-20,20,"all","NFgd2HAFwd>0","","NODATA");
    TH1F* hmagnet = (TH1F*)draw.GetLastStackTotal();

    //draw.Draw(exp,"all","sandmuon",Form("%s[0]",Fgd2HAFwdvar[ivar].Data()),80,-20,20,"all","NFgd2HAFwd>0","","NODATA");
    //TH1F* hsand = (TH1F*)draw.GetLastStackTotal();

    draw.Draw(exp,Form("%s[0]",Fgd2HAFwdvar[ivar].Data()),80,-20,20,"all","NFgd2HAFwd>0","","NOMC");
    TH1F* hdata = (TH1F*)draw.GetLastHisto();

    dofit(hmagnet, hdata, canvasFgd2HAFwd[ivar], Fgd2HAFwdvar[ivar], Fgd2HAFwdYaxisLabel[ivar]);
  }  
  
 
  TString Fgd2HABwdvar[] = {
    "Fgd2HABwd_ToF_ECal_FGD2_track",
    "Fgd2HABwd_ToF_ECal_FGD2_shower" 
  };
  Int_t   tmp7 = sizeof(Fgd2HABwdvar)/sizeof(TString);
  const Int_t NFgd2HABwdvar = tmp7;

  TString Fgd2HABwdYaxisLabel[] = {
    "ToF BrECal-FGD2",
    "ToF BrECal-FGD2"
  };

  TCanvas* canvasFgd2HABwd[NFgd2HABwdvar];
  for(int ivar=0; ivar<NFgd2HABwdvar; ivar++){
    canvasFgd2HABwd[ivar] = new TCanvas(Form("%s_vs_%s",Fgd2HABwdvar[ivar].Data()),Form("%s_vs_%s",Fgd2HABwdvar[ivar].Data()),1);
    canvasFgd2HABwd[ivar]->Draw();
    draw.SetLegendPos("r");
    draw.SetOptStat("");
	draw.SetTitle(Form("%s",Fgd2HABwdvar[ivar].Data()));
    draw.SetTitleY("Events");
    draw.SetTitleX(Form("%s",Fgd2HABwdYaxisLabel[ivar].Data()));     

    draw.Draw(exp,"all","magnet",Form("%s[0]",Fgd2HABwdvar[ivar].Data()),80,-20,20,"all","NFgd2HABwd>0","","NODATA");
    TH1F* hmagnet = (TH1F*)draw.GetLastStackTotal();

    //draw.Draw(exp,"all","sandmuon",Form("%s[0]",Fgd2HABwdvar[ivar].Data()),80,-20,20,"all","NFgd2HABwd>0","","NODATA");
    //TH1F* hsand = (TH1F*)draw.GetLastStackTotal();

    draw.Draw(exp,Form("%s[0]",Fgd2HABwdvar[ivar].Data()),80,-20,20,"all","NFgd2HABwd>0","","NOMC");
    TH1F* hdata = (TH1F*)draw.GetLastHisto();

    dofit(hmagnet, hdata, canvasFgd2HABwd[ivar], Fgd2HABwdvar[ivar], Fgd2HABwdYaxisLabel[ivar]);
 
  } 
  
  //	gPad->Print(Form("%s.pdf]", pdf_title));

}

void dofit(TH1F *h_tof_magnet, TH1F *h_tof_data, TCanvas* c, TString varname, TString Xlabel){

  double lowlimit=-20., highlimit =+20.;

  TF1 *twogaus_magnet = new TF1("twogaus_magnet","[0]*exp(-0.5*((x-[1])/[2])**2)+[3]*exp(-0.5*((x-[4])/[5])**2)",-20,20);
  twogaus_magnet->SetLineColor(mc_color);      
  twogaus_magnet->SetParameter(1,-5.);//To be tuned for some ToF 
  twogaus_magnet->SetParLimits(1,-20.,0.);//To be tuned for some ToF      
  twogaus_magnet->SetParameter(2,2.5);
  twogaus_magnet->SetParameter(4,5.);//To be tuned for some ToF  
  twogaus_magnet->SetParLimits(4,0.,20.);//To be tuned for some ToF        
  twogaus_magnet->SetParameter(5,2.5);
  
  //TF1 *twogaus_sand = new TF1("twogaus_sand","[0]*exp(-0.5*((x-[1])/[2])**2)",-20,20);
 // twogaus_sand->SetLineColor(3);        
  //twogaus_sand->SetParameter(2,2.5);    
  
  TF1 *twogaus_data = new TF1("twogaus_data","[0]*exp(-0.5*((x-[1])/[2])**2)+[3]*exp(-0.5*((x-[4])/[5])**2)",-20,20);
  twogaus_data->SetLineColor(data_color);        
  twogaus_data->SetParameter(1,-5.);//To be tuned for some ToF    
  twogaus_data->SetParLimits(1,-20.,0.);//To be tuned for some ToF         
  twogaus_data->SetParameter(2,2.5);    
  twogaus_data->SetParameter(4,5.);//To be tuned for some ToF    
  twogaus_data->SetParLimits(4,0,20.);//To be tuned for some ToF   
  twogaus_data->SetParameter(5,2.5);   

  TLegend *legend=new TLegend(0.13,0.62,0.28,0.87);
  legend->SetFillColor(0);
  legend->AddEntry(h_tof_magnet,Form("%s",legend_entry_1),"pe");
  //legend->AddEntry(h_tof_sand,"Neut Sand","pe");
  legend->AddEntry(h_tof_data,Form("%s",legend_entry_2),"pe");
  legend->AddEntry(twogaus_magnet,Form("Fit %s",legend_entry_1),"l");
  //legend->AddEntry(twogaus_sand,"Fit Neut Sand","l");
  legend->AddEntry(twogaus_data,Form("Fit %s",legend_entry_2),"l");
 
  //gStyle->SetOptFit(111);

  h_tof_magnet->Fit("twogaus_magnet","","",lowlimit,highlimit);
 // h_tof_sand->Fit("twogaus_sand","","",lowlimit,highlimit);
  h_tof_data->Fit("twogaus_data","","",lowlimit,highlimit);

  h_tof_magnet->SetMarkerStyle(26);
  h_tof_magnet->SetMarkerColor(mc_color);
  h_tof_magnet->SetLineColor(mc_color);
  h_tof_magnet->SetStats(true);
  h_tof_magnet->Draw("");
  c->Update();

  h_tof_data->SetMarkerStyle(24);
  h_tof_data->SetMarkerColor(data_color);
  h_tof_data->SetLineColor(data_color);
  h_tof_data->SetStats(true);
  h_tof_data->Draw("");
  c->Update();


  h_tof_data->GetXaxis()->SetTitle(Form("%s",Xlabel.Data()));  
  h_tof_data->GetYaxis()->SetTitleOffset(1.0);
  h_tof_data->GetYaxis()->SetTitle("#Events");  

  float ymax0 = TMath::Max(-999.,h_tof_data->GetMaximum());
  float ymax1 = TMath::Max(ymax0,h_tof_magnet->GetMaximum());
  float ymax  = TMath::Max(ymax0,ymax1);

  h_tof_data->GetYaxis()->SetRangeUser(0,1.2*ymax);

  h_tof_data->Draw("");
  h_tof_magnet->Draw("same");
 // h_tof_sand->Draw("same");
  legend->Draw("same");
   
   TFile *fd = TFile::Open("/home/t2k/aspeers/ToF_Systematics/Gaussian_Plots_and_Macros/Gaussian_Data.root","UPDATE");
   h_tof_data->Write();
   fd->Close();
   TFile *fm = TFile::Open("/home/t2k/aspeers/ToF_Systematics/Gaussian_Plots_and_Macros/Gaussian_MC.root","UPDATE");
   h_tof_magnet->Write();
   fm->Close();
   
   // THStack *hs = new THStack("hs",Form("%s;ToF (ns);Entries (%%)",varname.Data()));
   // hs->Add(h_tof_data, "hist");
   // hs->Add(h_tof_magnet, "hist"); 
   // hs->Write();
   
  //gPad->Print((Form("prod_gaussian_plots/FitToF_%s.pdf",varname.Data())));
   //  gPad->Print(Form("%s.pdf", pdf_title));
  
  double neg_mean_magnet, neg_meanerr_magnet;
  double neg_sigma_magnet, neg_sigmaerr_magnet;
  double pos_mean_magnet, pos_meanerr_magnet;
  double pos_sigma_magnet, pos_sigmaerr_magnet;
 // double mean_sand, meanerr_sand;
 // double sigma_sand, sigmaerr_sand;
  double neg_mean_data, neg_meanerr_data;
  double neg_sigma_data, neg_sigmaerr_data;
  double pos_mean_data, pos_meanerr_data;
  double pos_sigma_data, pos_sigmaerr_data;

  neg_mean_magnet     = twogaus_magnet->GetParameter(1);
  neg_meanerr_magnet  = twogaus_magnet->GetParError(1);
  neg_sigma_magnet    = TMath::Power(twogaus_magnet->GetParameter(2),2);
  neg_sigmaerr_magnet = 2*TMath::Abs(twogaus_magnet->GetParameter(2))*twogaus_magnet->GetParError(2);
  pos_mean_magnet     = twogaus_magnet->GetParameter(4);
  pos_meanerr_magnet  = twogaus_magnet->GetParError(4);
  pos_sigma_magnet    = TMath::Power(twogaus_magnet->GetParameter(5),2);
  pos_sigmaerr_magnet = 2*TMath::Abs(twogaus_magnet->GetParameter(5))*twogaus_magnet->GetParError(5);
  
//  mean_sand     = twogaus_sand->GetParameter(1);
//  meanerr_sand  = twogaus_sand->GetParError(1);
//  sigma_sand    = TMath::Power(twogaus_sand->GetParameter(2),2);
//  sigmaerr_sand = 2*TMath::Abs(twogaus_sand->GetParameter(2))*twogaus_sand->GetParError(2);
  
  neg_mean_data     = twogaus_data->GetParameter(1);
  neg_meanerr_data  = twogaus_data->GetParError(1);
  neg_sigma_data    = TMath::Power(twogaus_data->GetParameter(2),2);
  neg_sigmaerr_data = 2*TMath::Abs(twogaus_data->GetParameter(2))*twogaus_data->GetParError(2);
  pos_mean_data     = twogaus_data->GetParameter(4);
  pos_meanerr_data  = twogaus_data->GetParError(4);
  pos_sigma_data    = TMath::Power(twogaus_data->GetParameter(5),2);
  pos_sigmaerr_data = 2*TMath::Abs(twogaus_data->GetParameter(5))*twogaus_data->GetParError(5);

  streambuf *psbuf, *backup;
  ofstream file_output;
  //ofstream total_output

  //file_output.open(Form("prod_gaussian_plots/FitResults_%s.txt",varname.Data()));
 // file_output.open("Prod_GaussianFitResults.txt",std::ios_base::app);

  backup = cout.rdbuf();         // back up cout's streambuf
  psbuf = file_output.rdbuf();   // get file's streambuf
  cout.rdbuf(psbuf);             // assign streambuf to cout

  //cout<<fixed;
  cout<<setprecision(3);
  cout<<"//================="<<varname.Data()<<"================//"<<endl;
  cout<<"Magnet:"<<endl;
  cout<<setw(5)<< " Negative mean "       <<setw(10)<<neg_mean_magnet<<" +- "<<setw(5)<<neg_meanerr_magnet<<endl;
  cout<<setw(5)<< " Negative sigma mean " <<setw(10)<<neg_sigma_magnet<<" +- "<<setw(5)<<neg_sigmaerr_magnet<<endl;
  cout<<setw(5)<< " Positive mean "       <<setw(10)<<pos_mean_magnet<<" +- "<<setw(5)<<pos_meanerr_magnet<<endl;
  cout<<setw(5)<< " Positive sigma mean " <<setw(10)<<pos_sigma_magnet<<" +- "<<setw(5)<<pos_sigmaerr_magnet<<endl;
  cout<<endl;
  cout<<"//======================================================//"<<endl;
  cout<<"Data:"<<endl;
  cout<<setw(5)<< " Negative mean "       <<setw(10)<<neg_mean_data<<" +- "<<setw(5)<<neg_meanerr_data<<endl;
  cout<<setw(5)<< " Negative sigma mean " <<setw(10)<<neg_sigma_data<<" +- "<<setw(5)<<neg_sigmaerr_data<<endl;
  cout<<setw(5)<< " Positive mean "       <<setw(10)<<pos_mean_data<<" +- "<<setw(5)<<pos_meanerr_data<<endl;
  cout<<setw(5)<< " Positive sigma mean " <<setw(10)<<pos_sigma_data<<" +- "<<setw(5)<<pos_sigmaerr_data<<endl;
  cout<<endl;
  cout<<"//======================================================//"<<endl;
  cout<<"Data-Magnet:"<<endl;
  cout<<setw(5)<< " Negative mean "       <<setw(10)<<neg_mean_data-neg_mean_magnet<<" +- "<<setw(5)<<neg_meanerr_data+neg_meanerr_magnet<<endl;
  cout<<setw(5)<< " Negative sigma mean " <<setw(10)<<TMath::Abs(neg_sigma_data-neg_sigma_magnet)<<" +- "<<setw(5)<<neg_sigmaerr_data+neg_sigmaerr_magnet<<endl;
  cout<<setw(5)<< " Positive mean "       <<setw(10)<<pos_mean_data-pos_mean_magnet<<" +- "<<setw(5)<<pos_meanerr_data+pos_meanerr_magnet<<endl;
  cout<<setw(5)<< " Positive sigma mean " <<setw(10)<<TMath::Abs(pos_sigma_data-pos_sigma_magnet)<<" +- "<<setw(5)<<pos_sigmaerr_data+pos_sigmaerr_magnet<<endl;
  cout<<endl;
  cout<<"//======================================================//"<<endl<<endl;
/*  cout<<"Sand:"<<endl;
  cout<<setw(5)<< " Mean "       <<setw(10)<<mean_sand<<" +- "<<meanerr_sand<<endl;
  cout<<setw(5)<< " Sigma mean " <<setw(10)<<sigma_sand<<" +- "<<sigmaerr_sand<<endl;
  cout<<endl;
  cout<<"//======================================================//"<<endl;
  cout<<"Sand-Data:"<<endl;
  cout<<setw(5)<< " Negative mean "       <<setw(10)<<neg_mean_data-mean_sand<<setw(5)<<" +- "<<setw(5)<<neg_meanerr_data+meanerr_sand<<endl;
  cout<<setw(5)<< " Negative sigma mean " <<setw(10)<<TMath::Abs(neg_sigma_data-sigma_sand)<<setw(5)<<" +- "<<setw(5)<<neg_sigmaerr_data+sigmaerr_sand<<endl;
  cout<<setw(5)<< " Positive mean "       <<setw(10)<<pos_mean_data-mean_sand<<setw(5)<<" +- "<<setw(5)<<pos_meanerr_data+meanerr_sand<<endl;
  cout<<setw(5)<< " Positive sigma mean " <<setw(10)<<TMath::Abs(pos_sigma_data-sigma_sand)<<setw(5)<<" +- "<<setw(5)<<pos_sigmaerr_data+sigmaerr_sand<<endl; 
  cout<<"//======================================================//"<<endl;
*/
  cout.rdbuf(backup);        // restore cout's original streambuf
  file_output.close();
}
