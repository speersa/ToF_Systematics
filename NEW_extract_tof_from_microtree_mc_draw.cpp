////////////////////////////////////////////////////////////
//
//  Author: Yongheng Xu
//  email: riccioc<at>na.infn.it
//
//  usage: root 'DrawToF.C()'
//
//
////////////////////////////////////////////////////////////

int sense_category(double selmu_truestart, double selmu_trueend, int selmu_truefgdlayer, int run){
  bool backward;
  if(selmu_truestart-selmu_trueend>0) backward = true;  //BWD                                                                                                         
                          
  else                                backward = false; //FWD
  bool FGD;
  if(selmu_truefgdlayer!=-1) FGD = true;  //FGD                                                                                                                      
            
  else                       FGD = false; //not FGD
  if ( (run>80306000 && run<80308000) || (run>90306000 && run<90308000) ) return -10;
  else {
    if ( backward  &&  FGD ) return 0;
    if ( backward  && !FGD ) return 1;
    if ( !backward &&  FGD ) return 2;
    if ( !backward && !FGD ) return 3;
  }
}

void NEW_extract_tof_from_microtree_mc_draw(){

	gROOT->SetBatch();

  //=== Inizialize DrawingTools
 // gROOT->SetBatch();  
  DrawingTools draw("/home/t2k/aspeers/PROD7_validation/testing/MultiPiAnalysis_TEST.root");//option 3 for T2KStyle = publication/paper
  draw.SetStackFillStyle(3254);
  /*
  float win_scale = 0.75;
  int n_wide(2);
  int n_high(2);

	TCanvas* canvas = new TCanvas("canvas", "canvas", 750*n_wide*win_scale, 600*n_high*win_scale);
	
	canvas->Print("Plots.pdf[");
	*/
  //=== Inizialize Experiment     
  Experiment exp("nd280");

  SampleGroup run8air("run8air");

  //DataSample* run8air_mc     = new DataSample("/data/aspeers/ToF_Systematics/P7_V12_FHC_run4air_MC_default_settings.root");
  //DataSample* run8air_data     = new DataSample("/data/aspeers/ToF_Systematics/P7_V13_FHC_run4air_Data_default_settings.root");
  DataSample* run8air_mc     = new DataSample("/data/aspeers/ToF_Systematics/P6AA_FHC_run4air_MC_default_settings_OFFICIAL.root");
  DataSample* run8air_data     = new DataSample("/data/aspeers/ToF_Systematics/P6AA_FHC_run4air_Data_default_settings.root");
  SampleGroup run8air("run8air");
  run8air.AddMCSample("magnet", run8air_mc);
  run8air.AddDataSample(run8air_data);
  exp.AddSampleGroup( "run8air",   run8air    );
  /*
  DataSample* prod6_mc = new DataSample("/data/aspeers/ToF_Systematics/P6AA_FHC_run4air_MC_default_settings_OFFICIAL.root");
  DataSample* prod6_data = new DataSample("/data/aspeers/ToF_Systematics/P6AA_FHC_run4air_Data_default_settings.root");
  SampleGroup prod6("prod6");
  prod6.AddMCSample("magnet", prod6_mc);
  prod6.AddDataSample(prod6_data);
  exp.AddSampleGroup("prod6", prod6);
	*/

  const int nsense = 5;
  int sense_leg[nsense] = { 0, 1, 2, 3, -10 };
  int sense_col[nsense] = { 3, 4, 2, 7, 5   };
 
  string sense_name[nsense] = {"BWD FGD","BWD noFGD","FWD FGD","FWD noFGD","Sand"};
  
  //=== FGD1 
  string fgd1fwd_sense   = "sense_category(Fgd1Fwd_truepos[0][2],   Fgd1Fwd_trueendpos[0][2],   Fgd1Fwd_truefgdlayer[0],   run)";
  string fgd1bwd_sense   = "sense_category(Fgd1Bwd_truepos[0][2],   Fgd1Bwd_trueendpos[0][2],   Fgd1Bwd_truefgdlayer[0],   run)";
  string fgd1hafwd_sense = "sense_category(Fgd1HAFwd_truepos[0][2], Fgd1HAFwd_trueendpos[0][2], Fgd1HAFwd_truefgdlayer[0], run)";
  string fgd1habwd_sense = "sense_category(Fgd1HABwd_truepos[0][2], Fgd1HABwd_trueendpos[0][2], Fgd1HABwd_truefgdlayer[0], run)";


  
  draw.ChangeCategory(fgd1fwd_sense,   nsense , sense_name, sense_leg, sense_col);
  draw.ChangeCategory(fgd1bwd_sense,   nsense , sense_name, sense_leg, sense_col);
  draw.ChangeCategory(fgd1hafwd_sense, nsense , sense_name, sense_leg, sense_col);
  draw.ChangeCategory(fgd1habwd_sense, nsense , sense_name, sense_leg, sense_col);

  string fgd1fwd_rec_sense   = "sense_category(Fgd1Fwd_pos[0][2],   Fgd1Fwd_endpos[0][2],   Fgd1Fwd_fgdlayer[0],   run)";
  string fgd1bwd_rec_sense   = "sense_category(Fgd1Bwd_pos[0][2],   Fgd1Bwd_endpos[0][2],   Fgd1Bwd_fgdlayer[0],   run)";
  string fgd1hafwd_rec_sense = "sense_category(Fgd1HAFwd_pos[0][2], Fgd1HAFwd_endpos[0][2], Fgd1HAFwd_fgdlayer[0], run)";
  string fgd1habwd_rec_sense = "sense_category(Fgd1HABwd_pos[0][2], Fgd1HABwd_endpos[0][2], Fgd1HABwd_truefgdlayer[0], run)";


  draw.ChangeCategory(fgd1fwd_rec_sense,   nsense , sense_name, sense_leg, sense_col);
  draw.ChangeCategory(fgd1bwd_rec_sense,   nsense , sense_name, sense_leg, sense_col);
  draw.ChangeCategory(fgd1hafwd_rec_sense, nsense , sense_name, sense_leg, sense_col);
  draw.ChangeCategory(fgd1habwd_rec_sense, nsense , sense_name, sense_leg, sense_col);


TFile *ff = TFile::Open("/home/t2k/aspeers/ToF_Systematics/ToF_Output.root","RECREATE");


TString Fgd1Fwdvar[] = {
    "Fgd1Fwd_ToF_FGD1_FGD2",
    "Fgd1Fwd_ToF_ECal_FGD1_track",
    "Fgd1Fwd_ToF_ECal_FGD1_shower",
    "Fgd1Fwd_ToF_DSECal_FGD1_track",
    "Fgd1Fwd_ToF_DSECal_FGD1_shower",
  };
  
  Int_t tmp0 = sizeof(Fgd1Fwdvar)/sizeof(TString); //Length of array, apparently this is how you're supposed to do it in C++
  const Int_t NFgd1Fwdvar = tmp0;

  TString Fgd1FwdYaxisLabel[] = {
    "ToF FGD1-FGD2",
    "ToF BrECal-FGD1",
    "ToF BrECal-FGD1",
    "ToF DSECal-FGD1",
    "ToF DSECal-FGD1",
  };

  for(int ivar=0; ivar<NFgd1Fwdvar; ivar++){
    TH1D* fwd = new TH1D(Form("%s", Fgd1Fwdvar[ivar].Data()), Form("%s FWD", Fgd1Fwdvar[ivar].Data()), 120, -30, 30);
    TH1D* bwd = new TH1D(Form("%s_bwd", Fgd1Fwdvar[ivar].Data()), Form("%s BWD", Fgd1Fwdvar[ivar].Data()), 120, -30, 30); 
    TH1D* data= new TH1D(Form("%s_data", Fgd1Fwdvar[ivar].Data()), Form("%s Data", Fgd1Fwdvar[ivar].Data()), 120, -30, 30);;

    draw.Draw(*run8air_mc,Form("%s[0]",Fgd1Fwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Fwd>0 && Fgd1Fwd_truepos[0][2] >= Fgd1Fwd_trueendpos[0][2]","","NOAUTOLABELS");
	fwd->Add(draw.GetLastStackTotal());
	//draw.Draw(*prod6_mc,Form("%s[0]",Fgd1Fwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Fwd>0 && Fgd1Fwd_truepos[0][2] >= Fgd1Fwd_trueendpos[0][2]","same","NOAUTOLABELS");
   // fwd->Add(draw.GetLastStackTotal());
	//canvas->Print("Plots.pdf");

    draw.Draw(*run8air_mc,Form("%s[0]",Fgd1Fwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Fwd>0 && Fgd1Fwd_truepos[0][2] < Fgd1Fwd_trueendpos[0][2]","","NOAUTOLABELS");
	bwd->Add(draw.GetLastStackTotal());
	//draw.Draw(*prod6_mc,Form("%s[0]",Fgd1Fwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Fwd>0 && Fgd1Fwd_truepos[0][2] < Fgd1Fwd_trueendpos[0][2]","same","NOAUTOLABELS");
   // bwd->Add(draw.GetLastStackTotal());
	//canvas->Print("Plots.pdf");
	
    draw.Draw(*run8air_data,Form("%s[0]",Fgd1Fwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Fwd>0","","NOAUTOLABELS");
	data->Add(draw.GetLastStackTotal());
	//draw.Draw(*prod6_data,Form("%s[0]",Fgd1Fwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Fwd>0","same","NOAUTOLABELS");
   // data->Add(draw.GetLastStackTotal());
	//canvas->Print("Plots.pdf");


    fwd->Write();
    bwd->Write();
    data->Write();

    delete fwd;
    delete bwd;
    delete data;

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
  
  for(int ivar=0; ivar<NFgd1Bwdvar; ivar++){
    TH1D* fwd = new TH1D(Form("%s", Fgd1Bwdvar[ivar].Data()), Form("%s FWD", Fgd1Bwdvar[ivar].Data()), 120, -30, 30);
    TH1D* bwd = new TH1D(Form("%s_bwd", Fgd1Bwdvar[ivar].Data()), Form("%s BWD", Fgd1Bwdvar[ivar].Data()), 120, -30, 30); 
    TH1D* data= new TH1D(Form("%s_data", Fgd1Bwdvar[ivar].Data()), Form("%s Data", Fgd1Bwdvar[ivar].Data()), 120, -30, 30);;
    if(ivar<2){
        draw.Draw(*run8air_mc,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Bwd>0 && Fgd1Bwd_truepos[0][2] >= Fgd1Bwd_trueendpos[0][2]","","NOAUTOLABELS");
        fwd->Add(draw.GetLastStackTotal());

        draw.Draw(*run8air_mc,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Bwd>0 && Fgd1Bwd_truepos[0][2] < Fgd1Bwd_trueendpos[0][2]","","NOAUTOLABELS");
        bwd->Add(draw.GetLastStackTotal());

        draw.Draw(*run8air_data,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Bwd>0","","NOAUTOLABELS");
        data->Add(draw.GetLastStackTotal());
    }
    else{
        draw.Draw(*run8air_mc,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Bwd>0 && Fgd1Bwd_isECAL!=-1 && Fgd1Bwd_truepos[0][2] >= Fgd1Bwd_trueendpos[0][2] ","","NOAUTOLABELS");
        fwd->Add(draw.GetLastStackTotal());

        draw.Draw(*run8air_mc,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Bwd>0 && Fgd1Bwd_isECAL!=-1 && Fgd1Bwd_truepos[0][2] < Fgd1Bwd_trueendpos[0][2] ","","NOAUTOLABELS");
        bwd->Add(draw.GetLastStackTotal());

        draw.Draw(*run8air_data,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd1Bwd>0 && Fgd1Bwd_isECAL!=-1 ","","NOAUTOLABELS");
        data->Add(draw.GetLastStackTotal());
    }
    
    fwd->Write();
    bwd->Write();
    data->Write();

    delete fwd;
    delete bwd;
    delete data;

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

  for(int ivar=0; ivar<NFgd1HAFwdvar; ivar++){
    TH1D* fwd = new TH1D(Form("%s", Fgd1HAFwdvar[ivar].Data()), Form("%s FWD", Fgd1HAFwdvar[ivar].Data()), 120, -30, 30);
    TH1D* bwd = new TH1D(Form("%s_bwd", Fgd1HAFwdvar[ivar].Data()), Form("%s BWD", Fgd1HAFwdvar[ivar].Data()), 120, -30, 30); 
    TH1D* data= new TH1D(Form("%s_data", Fgd1HAFwdvar[ivar].Data()), Form("%s Data", Fgd1HAFwdvar[ivar].Data()), 120, -30, 30);
    
    draw.Draw(*run8air_mc,Form("%s[0]",Fgd1HAFwdvar[ivar].Data()),120,-30, 30,"all","NFgd1HAFwd>0 && Fgd1HAFwd_truepos[0][2] >= Fgd1HAFwd_trueendpos[0][2] && Fgd1HAFwd_EndStop_ECALSMRDFV != -1","","NOAUTOLABELS");
    fwd->Add(draw.GetLastStackTotal());

    draw.Draw(*run8air_mc,Form("%s[0]",Fgd1HAFwdvar[ivar].Data()),120,-30, 30,"all","NFgd1HAFwd>0 && Fgd1HAFwd_truepos[0][2] < Fgd1HAFwd_trueendpos[0][2] && Fgd1HAFwd_EndStop_ECALSMRDFV != -1","","NOAUTOLABELS");
    bwd->Add(draw.GetLastStackTotal());

    draw.Draw(*run8air_data,Form("%s[0]",Fgd1HAFwdvar[ivar].Data()),120,-30, 30,"all","NFgd1HAFwd>0","","NOAUTOLABELS");
    data->Add(draw.GetLastStackTotal());
    
    fwd->Write();
    bwd->Write();
    data->Write();

    delete fwd;
    delete bwd;
    delete data;
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

  for(int ivar=0; ivar<NFgd1HABwdvar; ivar++){
    TH1D* fwd = new TH1D(Form("%s", Fgd1HABwdvar[ivar].Data()), Form("%s FWD", Fgd1HABwdvar[ivar].Data()), 120, -30, 30);
    TH1D* bwd = new TH1D(Form("%s_bwd", Fgd1HABwdvar[ivar].Data()), Form("%s BWD", Fgd1HABwdvar[ivar].Data()), 120, -30, 30); 
    TH1D* data= new TH1D(Form("%s_data", Fgd1HABwdvar[ivar].Data()), Form("%s Data", Fgd1HABwdvar[ivar].Data()), 120, -30, 30);
    
    draw.Draw(*run8air_mc,Form("%s[0]",Fgd1HABwdvar[ivar].Data()),120,-30, 30,"all","NFgd1HABwd>0 && Fgd1HABwd_truepos[0][2] >= Fgd1HABwd_trueendpos[0][2] && Fgd1HABwd_StartStop_ECALSMRDFV != -1","","NOAUTOLABELS");
    fwd->Add(draw.GetLastStackTotal());

    draw.Draw(*run8air_mc,Form("%s[0]",Fgd1HABwdvar[ivar].Data()),120,-30, 30,"all","NFgd1HABwd>0 && Fgd1HABwd_truepos[0][2] < Fgd1HABwd_trueendpos[0][2] && Fgd1HABwd_StartStop_ECALSMRDFV != -1","","NOAUTOLABELS");
    bwd->Add(draw.GetLastStackTotal());

    draw.Draw(*run8air_data,Form("%s[0]",Fgd1HABwdvar[ivar].Data()),120,-30, 30,"all","NFgd1HABwd>0","","NOAUTOLABELS");
    data->Add(draw.GetLastStackTotal());
    
    fwd->Write();
    bwd->Write();
    data->Write();

    delete fwd;
    delete bwd;
    delete data;
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


  for(int ivar=0; ivar<NFgd2Fwdvar; ivar++){
    TH1D* fwd = new TH1D(Form("%s", Fgd2Fwdvar[ivar].Data()), Form("%s FWD", Fgd2Fwdvar[ivar].Data()), 120, -30, 30);
    TH1D* bwd = new TH1D(Form("%s_bwd", Fgd2Fwdvar[ivar].Data()), Form("%s BWD", Fgd2Fwdvar[ivar].Data()), 120, -30, 30); 
    TH1D* data= new TH1D(Form("%s_data", Fgd2Fwdvar[ivar].Data()), Form("%s Data", Fgd2Fwdvar[ivar].Data()), 120, -30, 30);;

    draw.Draw(*run8air_mc,Form("%s[0]",Fgd2Fwdvar[ivar].Data()),120,-30, 30,"all","NFgd2Fwd>0 && Fgd2Fwd_truepos[0][2] >= Fgd2Fwd_trueendpos[0][2]","","NOAUTOLABELS");
    fwd->Add(draw.GetLastStackTotal());

    draw.Draw(*run8air_mc,Form("%s[0]",Fgd2Fwdvar[ivar].Data()),120,-30, 30,"all","NFgd2Fwd>0 && Fgd2Fwd_truepos[0][2] < Fgd2Fwd_trueendpos[0][2]","","NOAUTOLABELS");
    bwd->Add(draw.GetLastStackTotal());

    draw.Draw(*run8air_data,Form("%s[0]",Fgd2Fwdvar[ivar].Data()),120,-30, 30,"all","NFgd2Fwd>0","","NOAUTOLABELS");
    data->Add(draw.GetLastStackTotal());


    fwd->Write();
    bwd->Write();
    data->Write();

    delete fwd;
    delete bwd;
    delete data;

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

  for(int ivar=0; ivar<NFgd2Bwdvar; ivar++){
    TH1D* fwd = new TH1D(Form("%s", Fgd2Bwdvar[ivar].Data()), Form("%s FWD", Fgd2Bwdvar[ivar].Data()), 120, -30, 30);
    TH1D* bwd = new TH1D(Form("%s_bwd", Fgd2Bwdvar[ivar].Data()), Form("%s BWD", Fgd2Bwdvar[ivar].Data()), 120, -30, 30); 
    TH1D* data= new TH1D(Form("%s_data", Fgd2Bwdvar[ivar].Data()), Form("%s Data", Fgd2Bwdvar[ivar].Data()), 120, -30, 30);;
    if(ivar==0){
        draw.Draw(*run8air_mc,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd2Bwd>0 && Fgd2Bwd_truepos[0][2] >= Fgd2Bwd_trueendpos[0][2]","","NOAUTOLABELS");
        fwd->Add(draw.GetLastStackTotal());

        draw.Draw(*run8air_mc,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd2Bwd>0 && Fgd2Bwd_truepos[0][2] < Fgd2Bwd_trueendpos[0][2]","","NOAUTOLABELS");
        bwd->Add(draw.GetLastStackTotal());

        draw.Draw(*run8air_data,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd2Bwd>0","","NOAUTOLABELS");
        data->Add(draw.GetLastStackTotal());
    }
    else{
        draw.Draw(*run8air_mc,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd2Bwd>0 && Fgd2Bwd_isECAL!=-1 && Fgd2Bwd_truepos[0][2] >= Fgd2Bwd_trueendpos[0][2]","","NOAUTOLABELS");
        fwd->Add(draw.GetLastStackTotal());

        draw.Draw(*run8air_mc,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd2Bwd>0 && Fgd2Bwd_isECAL!=-1 && Fgd2Bwd_truepos[0][2] < Fgd2Bwd_trueendpos[0][2]","","NOAUTOLABELS");
        bwd->Add(draw.GetLastStackTotal());

        draw.Draw(*run8air_data,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),120,-30, 30,"all","NFgd2Bwd>0 && Fgd2Bwd_isECAL!=-1 ","","NOAUTOLABELS");
        data->Add(draw.GetLastStackTotal());
    }
    
    fwd->Write();
    bwd->Write();
    data->Write();

    delete fwd;
    delete bwd;
    delete data;

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

  for(int ivar=0; ivar<NFgd2HAFwdvar; ivar++){
    TH1D* fwd = new TH1D(Form("%s", Fgd2HAFwdvar[ivar].Data()), Form("%s FWD", Fgd2HAFwdvar[ivar].Data()), 120, -30, 30);
    TH1D* bwd = new TH1D(Form("%s_bwd", Fgd2HAFwdvar[ivar].Data()), Form("%s BWD", Fgd2HAFwdvar[ivar].Data()), 120, -30, 30); 
    TH1D* data= new TH1D(Form("%s_data", Fgd2HAFwdvar[ivar].Data()), Form("%s Data", Fgd2HAFwdvar[ivar].Data()), 120, -30, 30);
    
    draw.Draw(*run8air_mc,Form("%s[0]",Fgd2HAFwdvar[ivar].Data()),120,-30, 30,"all","NFgd2HAFwd>0 && Fgd2HAFwd_truepos[0][2] >= Fgd2HAFwd_trueendpos[0][2] && Fgd2HAFwd_EndStop_ECALSMRDFV != -1","","NOAUTOLABELS");
    fwd->Add(draw.GetLastStackTotal());

    draw.Draw(*run8air_mc,Form("%s[0]",Fgd2HAFwdvar[ivar].Data()),120,-30, 30,"all","NFgd2HAFwd>0 && Fgd2HAFwd_truepos[0][2] < Fgd2HAFwd_trueendpos[0][2] && Fgd2HAFwd_EndStop_ECALSMRDFV != -1","","NOAUTOLABELS");
    bwd->Add(draw.GetLastStackTotal());

    draw.Draw(*run8air_data,Form("%s[0]",Fgd2HAFwdvar[ivar].Data()),120,-30, 30,"all","NFgd2HAFwd>0","","NOAUTOLABELS");
    data->Add(draw.GetLastStackTotal());
    
    fwd->Write();
    bwd->Write();
    data->Write();

    delete fwd;
    delete bwd;
    delete data;
  }

  TString Fgd2HABwdvar[] = {
    "Fgd2HABwd_ToF_ECal_FGD2_track",
    "Fgd2HABwd_ToF_ECal_FGD2_shower" 
  };
  Int_t tmp7 = sizeof(Fgd2HABwdvar)/sizeof(TString);
  const Int_t NFgd2HABwdvar = tmp7;

  TString Fgd2HABwdYaxisLabel[] = {
    "ToF BrECal-FGD2",
    "ToF BrECal-FGD2"
  };

  for(int ivar=0; ivar<NFgd2HABwdvar; ivar++){
    TH1D* fwd = new TH1D(Form("%s", Fgd2HABwdvar[ivar].Data()), Form("%s FWD", Fgd2HABwdvar[ivar].Data()), 120, -30, 30);
    TH1D* bwd = new TH1D(Form("%s_bwd", Fgd2HABwdvar[ivar].Data()), Form("%s BWD", Fgd2HABwdvar[ivar].Data()), 120, -30, 30); 
    TH1D* data= new TH1D(Form("%s_data", Fgd2HABwdvar[ivar].Data()), Form("%s Data", Fgd2HABwdvar[ivar].Data()), 120, -30, 30);
    
    draw.Draw(*run8air_mc,Form("%s[0]",Fgd2HABwdvar[ivar].Data()),120,-30, 30,"all","NFgd2HABwd>0 && Fgd2HABwd_truepos[0][2] >= Fgd2HABwd_trueendpos[0][2] && Fgd2HABwd_StartStop_ECALSMRDFV != -1","","NOAUTOLABELS");
    fwd->Add(draw.GetLastStackTotal());

    draw.Draw(*run8air_mc,Form("%s[0]",Fgd2HABwdvar[ivar].Data()),120,-30, 30,"all","NFgd2HABwd>0 && Fgd2HABwd_truepos[0][2] < Fgd2HABwd_trueendpos[0][2] && Fgd2HABwd_StartStop_ECALSMRDFV != -1","","NOAUTOLABELS");
    bwd->Add(draw.GetLastStackTotal());

    draw.Draw(*run8air_data,Form("%s[0]",Fgd2HABwdvar[ivar].Data()),120,-30, 30,"all","NFgd2HABwd>0","","NOAUTOLABELS");
    data->Add(draw.GetLastStackTotal());
    
    fwd->Write();
    bwd->Write();
    data->Write();

    delete fwd;
    delete bwd;
    delete data;
  }


ff->Close();
//canvas->Print("Plots.pdf]");
}
