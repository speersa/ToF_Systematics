////////////////////////////////////////////////////////////
//
//  Author: Ciro Riccio
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
// int NBINS = 59;
// float TStart = -29.0;
// float Tend = 30.0;

int NBINS = 119;
float TStart = -29.5;
float Tend = 30.0;

void extract_tof_from_microtree_data_draw(){
	
	gROOT->SetBatch();

  //=== Inizialize DrawingTools                                                                         
  DrawingTools draw("/home/t2k/aspeers/PROD7_validation/testing/MultiPiAnalysis_TEST.root");//option 3 for T2KStyle = publication/paper
  draw.SetStackFillStyle(3254);

  //=== Inizialize Experiment     
  Experiment exp("nd280");

 // SampleGroup run8air("run8air");
 // SampleGroup run8water("run8water");

  DataSample* run8air_data     = new DataSample("/data/aspeers/ToF_Systematics/P7E_RHC_Data.root");
  SampleGroup run8air("run8air");

 // DataSample* run8water_data     = new DataSample("/data/yxu/general_outputs/microtrees/20220620_validation_data/run8_water.root");
 // SampleGroup run8water("run8water");

  // run2air.AddDataSample(run2air_data);
  run8air.AddDataSample(run8air_data);

  // run8water.AddDataSample(run8water_data);

  // run2air.AddMCSample("sandmuon_nu", sandmu_nu);
  exp.AddSampleGroup( "run8air",   run8air    );
 // exp.AddSampleGroup( "run8water",   run8water    );

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


TFile *ff = TFile::Open("/home/t2k/aspeers/ToF_Systematics/ToF_Output_Data.root","RECREATE");


TString Fgd1Fwdvar[] = {
    "Fgd1Fwd_ToF_FGD1_FGD2",
    "Fgd1Fwd_ToF_ECal_FGD1_track",
    "Fgd1Fwd_ToF_ECal_FGD1_shower",
    "Fgd1Fwd_ToF_DSECal_FGD1_track",
    "Fgd1Fwd_ToF_DSECal_FGD1_shower",

  };
  
  Int_t tmp0 = sizeof(Fgd1Fwdvar)/sizeof(TString);
  const Int_t NFgd1Fwdvar = tmp0;

  TString Fgd1FwdYaxisLabel[] = {
    "ToF FGD1-FGD2",
    "ToF BrECal-FGD1",
    "ToF BrECal-FGD1",
    "ToF DSECal-FGD1",
    "ToF DSECal-FGD1",
  };

  for(int ivar=0; ivar<NFgd1Fwdvar; ivar++){
    TH1D* data= new TH1D(Form("%s", Fgd1Fwdvar[ivar].Data()), Form("%s Data", Fgd1Fwdvar[ivar].Data()), NBINS,TStart, Tend);;


    draw.Draw(*run8air_data,Form("%s[0]",Fgd1Fwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd1Fwd>0","","NOAUTOLABELS");
    data->Add(draw.GetLastStackTotal());
   // draw.Draw(*run8water_data,Form("%s[0]",Fgd1Fwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd1Fwd>0","","NOAUTOLABELS");
   // data->Add(draw.GetLastStackTotal());


    data->Write();

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
    TH1D* data= new TH1D(Form("%s", Fgd1Bwdvar[ivar].Data()), Form("%s Data", Fgd1Bwdvar[ivar].Data()), NBINS,TStart, Tend);;
    if(ivar<2){
        draw.Draw(*run8air_data,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd1Bwd>0","","NOAUTOLABELS");
        data->Add(draw.GetLastStackTotal());
     //   draw.Draw(*run8water_data,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd1Bwd>0","","NOAUTOLABELS");
     //   data->Add(draw.GetLastStackTotal());
    }
    else{
        draw.Draw(*run8air_data,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd1Bwd>0 && Fgd1Bwd_isECAL!=-1 ","","NOAUTOLABELS");
        data->Add(draw.GetLastStackTotal());
      //  draw.Draw(*run8water_data,Form("%s[0]",Fgd1Bwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd1Bwd>0 && Fgd1Bwd_isECAL!=-1 ","","NOAUTOLABELS");
      //  data->Add(draw.GetLastStackTotal());
    }
    
    data->Write();

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
    TH1D* data= new TH1D(Form("%s", Fgd1HAFwdvar[ivar].Data()), Form("%s Data", Fgd1HAFwdvar[ivar].Data()), NBINS,TStart, Tend);
    
    draw.Draw(*run8air_data,Form("%s[0]",Fgd1HAFwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd1HAFwd>0 && Fgd1HAFwd_EndStop_ECALSMRD != -1","","NOAUTOLABELS");
    data->Add(draw.GetLastStackTotal());
  //  draw.Draw(*run8water_data,Form("%s[0]",Fgd1HAFwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd1HAFwd>0 && Fgd1HAFwd_EndStop_ECALSMRD != -1","","NOAUTOLABELS");
  //  data->Add(draw.GetLastStackTotal());
    
    data->Write();

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
    TH1D* data= new TH1D(Form("%s", Fgd1HABwdvar[ivar].Data()), Form("%s Data", Fgd1HABwdvar[ivar].Data()), NBINS,TStart, Tend);
    
    draw.Draw(*run8air_data,Form("%s[0]",Fgd1HABwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd1HABwd>0 && Fgd1HABwd_StartStop_ECALSMRD != -1","","NOAUTOLABELS");
    data->Add(draw.GetLastStackTotal());
  //  draw.Draw(*run8water_data,Form("%s[0]",Fgd1HABwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd1HABwd>0 && Fgd1HABwd_StartStop_ECALSMRD != -1","","NOAUTOLABELS");
  //  data->Add(draw.GetLastStackTotal());
    
    data->Write();

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
    TH1D* data= new TH1D(Form("%s", Fgd2Fwdvar[ivar].Data()), Form("%s Data", Fgd2Fwdvar[ivar].Data()), NBINS,TStart, Tend);;


    draw.Draw(*run8air_data,Form("%s[0]",Fgd2Fwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd2Fwd>0","","NOAUTOLABELS");
    data->Add(draw.GetLastStackTotal());
  //  draw.Draw(*run8water_data,Form("%s[0]",Fgd2Fwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd2Fwd>0","","NOAUTOLABELS");
  //  data->Add(draw.GetLastStackTotal());


    data->Write();

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
    TH1D* data= new TH1D(Form("%s", Fgd2Bwdvar[ivar].Data()), Form("%s Data", Fgd2Bwdvar[ivar].Data()), NBINS,TStart, Tend);;
    if(ivar==0){

        draw.Draw(*run8air_data,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd2Bwd>0 && Fgd2Bwd_StartStop_FGD1FV != 1","","NOAUTOLABELS");
        data->Add(draw.GetLastStackTotal());
      //  draw.Draw(*run8water_data,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd2Bwd>0 && Fgd2Bwd_StartStop_FGD1FV != 1","","NOAUTOLABELS");
      //  data->Add(draw.GetLastStackTotal());
    }
    else{
        draw.Draw(*run8air_data,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd2Bwd>0 && Fgd2Bwd_isECAL!=-1  && Fgd2Bwd_StartStop_FGD1FV != 1","","NOAUTOLABELS");
        data->Add(draw.GetLastStackTotal());
      //  draw.Draw(*run8water_data,Form("%s[0]",Fgd2Bwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd2Bwd>0 && Fgd2Bwd_isECAL!=-1  && Fgd2Bwd_StartStop_FGD1FV != 1","","NOAUTOLABELS");
      //  data->Add(draw.GetLastStackTotal());
    }
    
    data->Write();

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
    TH1D* data= new TH1D(Form("%s", Fgd2HAFwdvar[ivar].Data()), Form("%s Data", Fgd2HAFwdvar[ivar].Data()), NBINS,TStart, Tend);
    

    draw.Draw(*run8air_data,Form("%s[0]",Fgd2HAFwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd2HAFwd>0 && Fgd2HAFwd_EndStop_ECALSMRD != -1","","NOAUTOLABELS");
    data->Add(draw.GetLastStackTotal());
  //  draw.Draw(*run8water_data,Form("%s[0]",Fgd2HAFwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd2HAFwd>0 && Fgd2HAFwd_EndStop_ECALSMRD != -1","","NOAUTOLABELS");
  //  data->Add(draw.GetLastStackTotal());
    
    data->Write();

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
    TH1D* data= new TH1D(Form("%s", Fgd2HABwdvar[ivar].Data()), Form("%s Data", Fgd2HABwdvar[ivar].Data()), NBINS,TStart, Tend);
    
    draw.Draw(*run8air_data,Form("%s[0]",Fgd2HABwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd2HABwd>0 && Fgd2HABwd_StartStop_ECALSMRD != -1","","NOAUTOLABELS");
    data->Add(draw.GetLastStackTotal());
   // draw.Draw(*run8water_data,Form("%s[0]",Fgd2HABwdvar[ivar].Data()),NBINS,TStart, Tend,"all","NFgd2HABwd>0 && Fgd2HABwd_StartStop_ECALSMRD != -1","","NOAUTOLABELS");
  //  data->Add(draw.GetLastStackTotal());
    
    data->Write();

    delete data;
  }


ff->Close();
}
