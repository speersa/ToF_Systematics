#include <iostream>   
#include <string>  
#include <fstream>


std::string sample_names[24] = {
    "Fgd1Fwd_ToF_ECal_FGD1_track",
    "Fgd1Fwd_ToF_ECal_FGD1_shower",
    "Fgd1Fwd_ToF_DSECal_FGD1_track",
    "Fgd1Fwd_ToF_DSECal_FGD1_shower",
    "Fgd1Bwd_ToF_P0D_FGD1_track",
    "Fgd1Bwd_ToF_P0D_FGD1_shower",
    "Fgd1Bwd_ToF_ECal_FGD1_track",
    "Fgd1Bwd_ToF_ECal_FGD1_shower",
    "Fgd1HAFwd_ToF_ECal_FGD1_track",
    "Fgd1HAFwd_ToF_ECal_FGD1_shower",
    "Fgd1HABwd_ToF_ECal_FGD1_track",
    "Fgd1HABwd_ToF_ECal_FGD1_shower",
    "Fgd2Fwd_ToF_ECal_FGD2_track",
    "Fgd2Fwd_ToF_ECal_FGD2_shower",
    "Fgd2Fwd_ToF_DSECal_FGD2_track",
    "Fgd2Fwd_ToF_DSECal_FGD2_shower",
    "Fgd2Bwd_ToF_ECal_FGD2_track",
    "Fgd2Bwd_ToF_ECal_FGD2_shower",
    "Fgd2HAFwd_ToF_ECal_FGD2_track",
    "Fgd2HAFwd_ToF_ECal_FGD2_shower",
    "Fgd2HABwd_ToF_ECal_FGD2_track",
    "Fgd2HABwd_ToF_ECal_FGD2_shower", 
    "Fgd1Fwd_ToF_FGD1_FGD2", 
    "Fgd2Bwd_ToF_FGD1_FGD2",

};

std::string sample_names_psyche[24] = {
    "kToFTopo_FGD1ECAL_LAStartFgd_Track",
    "kToFTopo_FGD1ECAL_LAStartFgd_Shower",
    "FGD1 DSECAL track",
    "FGD1 DSECAL shower",
    "kToFTopo_FGD1P0D_Track",
    "kToFTopo_FGD1P0D_Shower",
    "kToFTopo_FGD1ECAL_LAEndFgd_Track",
    "kToFTopo_FGD1ECAL_LAEndFgd_Shower",
    "kToFTopo_FGD1ECAL_HAStartFgd_Track",
    "kToFTopo_FGD1ECAL_HAStartFgd_Shower",
    "kToFTopo_FGD1ECAL_HAEndFgd_Track",
    "kToFTopo_FGD1ECAL_HAEndFgd_Shower",
    "kToFTopo_FGD2ECAL_LAStartFgd_Track",
    "kToFTopo_FGD2ECAL_LAStartFgd_Shower",
    "kToFTopo_FGD2DSECAL_LAStartFgd_Track",
    "kToFTopo_FGD2DSECAL_LAStartFgd_Shower",
    "kToFTopo_FGD2ECAL_LAEndFgd_Track",
    "kToFTopo_FGD2ECAL_LAEndFgd_Shower",
    "kToFTopo_FGD2ECAL_HAStartFgd_Track",
    "kToFTopo_FGD2ECAL_HAStartFgd_Shower",
    "kToFTopo_FGD2ECAL_HAEndFgd_Track",
    "kToFTopo_FGD2ECAL_HAEndFgd_Shower", 
    "kToFTopo_FGD1FGD2",
    "kToFTopo_FGD1FGD2_NoStopFGD1",
};

std::string sample_names_thesis[24] = {
    "FGD1ECAL_Track",
    "FGD1ECAL_Shower",
    "FGD1DSECAL_Track",
    "FGD1DSECAL_Shower",
    "P0DFGD1_Track",
    "P0DFGD1_Shower",
    "ECALFGD1_Track",
    "ECALFGD1_Shower",
    "FGD1ECAL_HighAngle_Track",
    "FGD1ECAL_HighAngle_Shower",
    "ECALFGD1_HighAngle_Track",
    "ECALFGD1_HighAngle_Shower",
    "FGD2ECAL_Track",
    "FGD2ECAL_Shower",
    "FGD2DSECAL_Track",
    "FGD2DSECAL_Shower",
    "ECALFGD2_Track",
    "ECALFGD2_Shower",
    "FGD2ECAL_HighAngle_Track",
    "FGD2ECAL_HighAngle_Shower",
    "ECALFGD2_HighAngle_Track",
    "ECALFGD2_HighAngle_Shower",
    "FGD1FGD2",
    "FGD2FGD1",
};


float fractions_p_m[24][2] = {
    {0.057, 0.041,},    // "Fgd1Fwd_ToF_ECal_FGD1_track",
    {0.065, 0.027,},    // "Fgd1Fwd_ToF_ECal_FGD1_shower",
    {0    ,     0,},    // Fgd1Fwd_ToF_DSECal_FGD1_track
    {0    ,     0,},    // Fgd1Fwd_ToF_DSECal_FGD1_shower
    {0.028, 0.039,},    // Fgd1Bwd_ToF_P0D_FGD1_track
    {0.073, 0.060,},    // Fgd1Bwd_ToF_P0D_FGD1_shower
    {0.103, 0.056,},    // Fgd1Bwd_ToF_ECal_FGD1_track
    {0.076, 0.072,},    // Fgd1Bwd_ToF_ECal_FGD1_shower
    {0.046, 0.050,},    // Fgd1HAFwd_ToF_ECal_FGD1_track
    {0.063, 0.040,},    // Fgd1HAFwd_ToF_ECal_FGD1_shower
    {0.082, 0.045,},    // Fgd1HABwd_ToF_ECal_FGD1_track
    {0.055, 0.065,},    // Fgd1HABwd_ToF_ECal_FGD1_shower
    {0.051, 0.040,},    // Fgd2Fwd_ToF_ECal_FGD2_track
    {0.066, 0.062,},    // Fgd2Fwd_ToF_ECal_FGD2_shower
    {0.011, 0.022,},    // Fgd2Fwd_ToF_DSECal_FGD2_track
    {0.015, 0.014,},    // Fgd2Fwd_ToF_DSECal_FGD2_shower
    {0.094, 0.056,},    // Fgd2Bwd_ToF_ECal_FGD2_track
    {0.083, 0.054,},    // Fgd2Bwd_ToF_ECal_FGD2_shower
    {0.060, 0.043,},    // Fgd2HAFwd_ToF_ECal_FGD2_track 
    {0.043, 0.099,},    // Fgd2HAFwd_ToF_ECal_FGD2_shower
    {0.073, 0.043,},    // Fgd2HABwd_ToF_ECal_FGD2_track
    {0.062, 0.035,},    // Fgd2HABwd_ToF_ECal_FGD2_shower
    {0.0,   0.0,  },    // Fgd1Fwd_ToF_FGD1_FGD2
    {0.0,   0.0,  },    // Fgd2Bwd_ToF_FGD1_FGD2

};

float smear_parameters_fb[24][3] = {
    {3.0, 1.0, 0.2},    // "Fgd1Fwd_ToF_ECal_FGD1_track",
    {2.8, 0.2, 1.8},   // "Fgd1Fwd_ToF_ECal_FGD1_shower",
    {0,0,0},    // Fgd1Fwd_ToF_DSECal_FGD1_track
    {0,0,0},    // Fgd1Fwd_ToF_DSECal_FGD1_shower
    {2.2, -1.4, -3.0},    // Fgd1Bwd_ToF_P0D_FGD1_track
    {3.2, -1.8, -3.0},    // Fgd1Bwd_ToF_P0D_FGD1_shower
    {3.4, -1.0,  1.0},    // Fgd1Bwd_ToF_ECal_FGD1_track
    {3.2, -1.0,  1.0},    // Fgd1Bwd_ToF_ECal_FGD1_shower
    {2.4,  0.6,  0.6},    // Fgd1HAFwd_ToF_ECal_FGD1_track
    {2.0,  0.6,  1.8},    // Fgd1HAFwd_ToF_ECal_FGD1_shower
    {2.4, -0.6, -1.0},    // Fgd1HABwd_ToF_ECal_FGD1_track
    {2.4,  0.6,  0.2},    // Fgd1HABwd_ToF_ECal_FGD1_shower
    {3.2, -0.2,  0.2},    // Fgd2Fwd_ToF_ECal_FGD2_track
    {3.0, -0.2,  1.0},    // Fgd2Fwd_ToF_ECal_FGD2_shower
    {1.4,  0.2,  3.0},    // Fgd2Fwd_ToF_DSECal_FGD2_track
    {1.4,  0.6,  2.2},    // Fgd2Fwd_ToF_DSECal_FGD2_shower
    {2.8, -0.2,  3.0},    // Fgd2Bwd_ToF_ECal_FGD2_track
    {3.0,  1.0,  3.0},    // Fgd2Bwd_ToF_ECal_FGD2_shower
    {2.8, -0.2, -0.2},    // Fgd2HAFwd_ToF_ECal_FGD2_track 
    {2.6,  0.6,  2.2},    // Fgd2HAFwd_ToF_ECal_FGD2_shower
    {2.2, -0.2, -1.0},    // Fgd2HABwd_ToF_ECal_FGD2_track
    {2.4,  1.0, -0.6},    // Fgd2HABwd_ToF_ECal_FGD2_shower
    {1.0, -0.6, -0.2},
    {0.8, -1.0, 0.2},
};


double chi2_[24][3];
double _matrix[24][3];


const int Nbins = 119;
const float upper_limit = 30;
const float lower_limit = -29.5;

// const int Nbins = 59;
// const float upper_limit = 30;
// const float lower_limit = -29;


double manual_chi2_test(TH1*mc, TH1* data, bool over_ndf = false){
    int nmcbins = mc->GetNbinsX();
    int ndatabins = data->GetNbinsX();

    if (nmcbins != ndatabins) throw;
    int ndf = nmcbins - 1;

    TH1* mc_clone = dynamic_cast<TH1*>(mc->Clone());
    mc_clone->Scale(data->Integral()/mc_clone->Integral());
    std::cout << mc_clone->Integral() << " " << mc->Integral() << " " << data->Integral() << std::endl;
    double chi2_sum = 0;

    
    for (int i = 1; i <= nmcbins; i++){
        if (data->GetBinContent(i) == 0 && mc_clone->GetBinContent(i) == 0) ndf--;
        else{
            chi2_sum += (mc_clone->GetBinContent(i) - data->GetBinContent(i)) * (mc_clone->GetBinContent(i) - data->GetBinContent(i)) / (data->GetBinContent(i) + mc_clone->GetBinContent(i)) ;
        }
    }

    if (over_ndf){
        return chi2_sum/ndf;
    }
    
    else{
        return chi2_sum;
    }
}

void left_compensation(TH1 *hist){
    double lastbin = 0;
    for (int i = 1; i <= hist->GetNbinsX(); i++){
        if (i == 1) lastbin = 0;
        else lastbin = hist->GetBinContent(i - 1);
        hist->SetBinContent(i, (hist->GetBinContent(i) + lastbin)/2.0);
    }
}


void convolute_1d(TH1* mc, TH1* kernel, TH1D*convoluted_mc){
    int nmcbins = mc->GetNbinsX();
    int nkernelbins = kernel->GetNbinsX();
    int nconvolutedbins = convoluted_mc->GetNbinsX();
    std::cout << nmcbins << " " << nkernelbins << " " << nconvolutedbins << std::endl;

    if (nmcbins != nconvolutedbins || nmcbins != nkernelbins) throw;


    double mc_integral = mc->Integral();
    double kernel_integral = kernel->Integral();

    mc->Scale(1/mc_integral);
    kernel->Scale(1/kernel_integral);


    double full_convoluted[2 * nmcbins - 1];

    for (int i_conv = 0; i_conv < 2 * nmcbins - 1; i_conv ++){
        int kmin, kmax, k;
        full_convoluted[i_conv] = 0;

        kmin = (i_conv >= nkernelbins - 1) ? i_conv - (nkernelbins - 1) : 0;
        kmax = (i_conv < nmcbins - 1) ? i_conv : nmcbins - 1;

        for (k = kmin; k <= kmax; k++)
        {
        full_convoluted[i_conv] += mc->GetBinContent(k + 1) * kernel->GetBinContent(i_conv - k + 1);
        }

    }
    for (int i_result = 0; i_result < nmcbins; i_result++){
        if (nmcbins%2 == 1){
            convoluted_mc->SetBinContent(i_result + 1, full_convoluted[i_result + nmcbins/2]);
        }
        else {
            convoluted_mc->SetBinContent(i_result + 1, full_convoluted[i_result + nmcbins/2 - 1]);
        }
        // cout << "Setting bin " << i_result + 1 << " to " << i_result + nmcbins/2 + 1 << endl;
    }
    mc->Scale(mc_integral);

    convoluted_mc->Scale(mc_integral);
    // left_compensation(convoluted_mc);
}


void apply_correction(TH1D *mchist, TH1D* corrected_mc, double mu,  double sigma){
    std::cout << mu << " " << sigma << std::endl;
    TF1* kernel = new TF1("Convolution_kernel","gaus",-30,30);
    for (int i = 1; i <= corrected_mc->GetNbinsX(); i++){
        corrected_mc->SetBinContent(i, 0);
    }
    // for (int i = 1; i <= corrected_mc->GetNbinsX(); i++){
    //     std::cout << mchist->GetBinContent(i) << std::endl;
    // }

    Double_t par[3] = {1, mu, sigma};

    kernel->SetParameters(1, mu, sigma);

    int nbinsmc = mchist->GetNbinsX();

    TH1D* kernel_th1 = new TH1D("convolution_kernel", "Convolution kernel", Nbins, lower_limit, upper_limit);
    for (int i = 1; i <= kernel_th1->GetNbinsX(); i++){
        kernel_th1->SetBinContent(i, kernel->Eval(kernel_th1->GetBinCenter(i)));
        // std::cout << "kernel: " << kernel_th1->GetBinCenter(i) << " " << kernel_th1->GetBinContent(i) << std::endl;
    }
    // kernel_th1->Scale(1/kernel_th1_area);
    convolute_1d(mchist, kernel_th1, corrected_mc);
    delete kernel_th1;
}


void frac_fit(){
    
std::string output_folder = "/home/t2k/aspeers/ToF_Systematics/tofSystematics/macros/frac_plots/";
std::string suffix = ".pdf";
std::string xxstatus = " not Normalised";

// TFile *file_data = TFile::Open("/data/yxu/general_outputs/th1s/20220507_time_slip_corr/r8air+water_267_data.root");
    
// TFile *file_mc = TFile::Open("/data/yxu/general_outputs/th1s/20220525_grid_search/r8air+water_267_mc.root");

// TFile *file_data = TFile::Open("/data/yxu/general_outputs/th1s/20220525_grid_search/r8air+water_267_data_60.root");
// TFile *file_data = TFile::Open("/data/yxu/general_outputs/th1s/20220525_grid_search/sam_data_267.root");

// TFile *file_data = TFile::Open("/data/yxu/general_outputs/th1s/20220602_tofsyst_draw/data_smrd_fgd1fgd2.root");
// TFile *file_mc = TFile::Open("/data/yxu/general_outputs/th1s/20220602_tofsyst_draw/mc_0611_nocorrection.root");


// run8 good MC & data. Dont touch
TFile *file_mc = TFile::Open("/data/aspeers/ToF_Systematics/P7_V12_FHC_run4air_MC_default_settings_OFFICIAL.root");
TFile *file_data = TFile::Open("/data/aspeers/ToF_Systematics/P7_V13_FHC_run4air_Data_default_settings_OFFICIAL.root");
TFile *file_sand = TFile::Open("/data/yxu/general_outputs/th1s/20220602_tofsyst_draw/20220704_tofsyst_run8_kinematic_sand.root");


// FHC run2-4 good MC & data. Dont touch
// TFile *file_sand = TFile::Open("/data/yxu/general_outputs/th1s/20220602_tofsyst_draw/20220704_tofsyst_run8_kinematic_sand.root");
// TFile *file_mc = TFile::Open("/data/yxu/general_outputs/th1s/20220602_tofsyst_draw/FHC_test.root");
// TFile *file_data = TFile::Open("/data/yxu/general_outputs/th1s/20220602_tofsyst_draw/FHC_DATA_test.root");

// TFile *file_sand = TFile::Open("/data/yxu/general_outputs/th1s/20220602_tofsyst_draw/20220728_ToFAnalysis_RHCSand_NoSyst.root");
// TFile *file_mc   = TFile::Open("/data/yxu/general_outputs/th1s/20220602_tofsyst_draw/20220728_ToFAnalysis_RHCMagnet_NoSyst.root");
// TFile *file_data = TFile::Open("/data/yxu/general_outputs/th1s/20220602_tofsyst_draw/20220728_ToFAnalysis_RHCData_NoSyst.root");


// TFile *file_mc = TFile::Open("/data/yxu/general_outputs/th1s/20220602_tofsyst_draw/RHC_test_2.root");
// TFile *file_data = TFile::Open("/data/yxu/general_outputs/th1s/20220602_tofsyst_draw/RHC_DATA_test.root");


// TFile *file_mc = TFile::Open("/data/yxu/general_outputs/th1s/20220525_grid_search/r8air+water_267_mc_60.root");

// TFile *file_mc = TFile::Open("/data/yxu/general_outputs/th1s/20220525_grid_search/r8air+water_267_100.root");
float bestfit_parameters[24][5];

for (int i = 0; i < 24; i++){
    gStyle->SetOptTitle(0);

    string sample(sample_names[i]);
    string _bwd("_bwd");

    TH1D *data, *mc_fwd, *mc_bwd;

    // TFile *file_data = TFile::Open("/data/yxu/general_outputs/th1s/20220507_time_slip_corr/r8air+water_data.root");


    file_data->GetObject(sample.c_str(), data);
    file_mc->GetObject(sample.c_str(), mc_fwd);
    file_mc->GetObject((sample + _bwd).c_str(), mc_bwd);
    

    // Sand files. Comment out to ignore sand.
    TH1D *sand_fwd, *sand_bwd;

    file_sand->GetObject(sample.c_str(), sand_fwd);
    file_sand->GetObject((sample + _bwd).c_str(), sand_bwd);

    // Sand already counted twice when extracting TH1s, so no need to do it again
    // Run 8 scaling
    // sand_fwd->Scale(2 * 19.0/(44.53 + 27.17));
    // sand_bwd->Scale(2 * 19.0/(44.53 + 27.17));

    // Run 2-4 scaling
    // sand_fwd->Scale(5 * 19.0/(16.8 + 12.0 + 30.8 + 36.1 + 36.1));
    // sand_bwd->Scale(5 * 19.0/(16.8 + 12.0 + 30.8 + 36.1 + 36.1));

    // Run 5-9 scaling
    sand_fwd->Scale(4 * 1.19/(2.24 + 3.47 + 3.32 + 2.66));
    sand_bwd->Scale(4 * 1.19/(2.24 + 3.47 + 3.32 + 2.66));


    // TH1D mc_combined = *mc_fwd + *mc_bwd;
    TH1D mc_combined = *mc_fwd + *mc_bwd  + *sand_fwd + *sand_bwd;

    std::cout << sample << " " << mc_fwd->Integral() << " " << mc_bwd->Integral() << std::endl;
    std::cout << mc_combined.GetNbinsX() << std::endl;
 

    double bestchi2ndf = 1e8;
    float best_par[4];
    double best_partition[3];
    TH1* best_stack;    
    TH1* best_getplot;
    double fraction_m = 0;
    double fraction_p = 0;

    int nruns = 0;

    for (int ifs = 1; ifs<=30; ifs++){
        for (int ifm = 0; ifm<=25; ifm++){
            for (int ibs = 1; ibs<=1; ibs++){
                for (int ibm = 0; ibm<=25; ibm++){
    // for (int ifs = 1; ifs<=1; ifs++){
    //     for (int ifm = 0; ifm<=0; ifm++){
    //         for (int ibs = 1; ibs<=1; ibs++){
    //             for (int ibm = 0; ibm<=0; ibm++){

                    nruns++;
                    if (nruns%100 == 0){
                        std::cout << "Already " << nruns << " runs!" << std::endl;
                    }
                        std::cout << "New iteration! " << ifs << " " << ifm << " " << ibs << " " << ibm << " " << std::endl;
                    TH1D *corrected_mc_fwd; 
                    TH1D *corrected_mc_bwd;
                    TH1D *corrected_mc_positive; 
                    TH1D *corrected_mc_negative; 



                    double sigma_f = 0,  mu_f = 0, sigma_b = 0, mu_b = 0;

                    sigma_f = 0.2 * ifs;
                    mu_f = -5 + 0.4 * ifm;

                    sigma_b = sigma_f;
                    mu_b = -5 + 0.4 * ibm;   

                    corrected_mc_fwd = new TH1D("corrected_mc_fwd", "Convoluted MC Fwd", Nbins, lower_limit, upper_limit);
                    corrected_mc_bwd = new TH1D("corrected_mc_bwd", "Convoluted MC Bwd", Nbins, lower_limit, upper_limit);
                    corrected_mc_positive = new TH1D("corrected_mc_p10", "Convoluted MC + 10", Nbins, lower_limit, upper_limit);
                    corrected_mc_negative = new TH1D("corrected_mc_m10", "Convoluted MC - 10", Nbins, lower_limit, upper_limit);


                

                    std::cout << sigma_f << " " << mu_f << " " << sigma_b << " " << mu_b << std::endl;

                    std::cout << mc_fwd->GetNbinsX() << " " << corrected_mc_fwd->GetNbinsX() << std::endl;
                    if (sigma_f == 0 || sigma_b == 0){
                        continue;
                    }


                    apply_correction(mc_fwd, corrected_mc_fwd, mu_f, sigma_f);
                    apply_correction(mc_bwd, corrected_mc_bwd, mu_b, sigma_b);
                    corrected_mc_fwd->Add(corrected_mc_bwd);

                    // Adding sand component                    
                    // corrected_mc_fwd->Add(sand_fwd);   
                    // corrected_mc_bwd->Add(sand_bwd);
                    
                    TH1D *corrected_mc = dynamic_cast<TH1D*>(corrected_mc_fwd->Clone());

                    int offset_10ns = 20;

                    for(int j = 1; j <= corrected_mc->GetNbinsX(); j++){
                        if (j <= offset_10ns) {corrected_mc_positive->SetBinContent(j, 0);}
                        else {corrected_mc_positive->SetBinContent(j, corrected_mc->GetBinContent(j - offset_10ns));}
                        if (j > (corrected_mc->GetNbinsX() - offset_10ns)) {corrected_mc_negative->SetBinContent(j, 0);}
                        else {corrected_mc_negative->SetBinContent(j, corrected_mc->GetBinContent(j + offset_10ns));}
                    }

                    TObjArray *mc_array = new TObjArray(3);        // MC histograms are put in this array
                    std::cout << "GetMaximumBin: " << corrected_mc->GetMaximumBin() << std::endl;
                    mc_array->Add(corrected_mc);
                    mc_array->Add(corrected_mc_positive);
                    mc_array->Add(corrected_mc_negative);

                    TFractionFitter* fit = new TFractionFitter(data, mc_array, "Q"); // initialise

                    fit->Constrain(0,0.0,1.0);               // constrain fraction 1 to be between 0 and 1
                    fit->Constrain(1,0.0,1.0);               // constrain fraction 1 to be between 0 and 1
                    fit->Constrain(2,0.0,1.0);               // constrain fraction 1 to be between 0 and 1

                    fit->SetRangeX(1,Nbins);                    // use only the first 15 bins in the fit
                    Int_t status = fit->Fit();               // perform the fit
                    // std::cout << "fit status: " << status << std::endl;
                    if (status != 0) continue;
                    double partition[3];
                    double error[3];
                    
                    for (int j = 0; j < 3; j++){
                        fit->GetResult(j, partition[j], error[j]);
                        // std::cout << partition[j] << std::endl;
                    }
                    corrected_mc->Scale(partition[0]);
                    corrected_mc_positive->Scale(partition[1]);
                    corrected_mc_negative->Scale(partition[2]);
                    double slip_chi2 = fit->GetChisquare();

                    TH1D hs_total = *corrected_mc + *corrected_mc_positive + *corrected_mc_negative;
                    // double slip_chi2 = hs_total.Chi2Test(data, "NORM CHI2/NDF");

                    // hs_total.Scale(data->Integral()/hs_total.Integral());

                    // // for (int k = 1; k < hs_total.GetNbinsX(); k++){
                    // //     std::cout << hs_total.GetBinContent(k) << " " <<  data->GetBinContent(k) << std::endl;
                    // // }

                    // double slip_chi2 = hs_total.Chi2Test(data, "UU CHI2/NDF");
                    if (slip_chi2 < bestchi2ndf){
                        best_par[0] = sigma_f;
                        best_par[1] = mu_f;
                        best_par[2] = sigma_b;
                        best_par[3] = mu_b;
                        bestchi2ndf = slip_chi2;
                        fraction_p = partition[1];
                        fraction_m = partition[2];

                        std::cout << "New best chi2: " << slip_chi2 << std::endl;
                        best_getplot = dynamic_cast<TH1*>(fit->GetPlot()->Clone());
                        best_stack = dynamic_cast<TH1*>(hs_total.Clone());

                    }
                    
                    delete fit;
                    delete mc_array;
                    delete corrected_mc_fwd;
                    delete corrected_mc_bwd;
                    // delete corrected_mc;
                    delete corrected_mc_positive;
                    delete corrected_mc_negative;


                }
            }
        }
    }

    double xsigma_f = best_par[0];
    double xmu_f = best_par[1];

    double xsigma_b = best_par[2];
    double xmu_b = best_par[3];

    bestfit_parameters[i][0] = xsigma_f;
    bestfit_parameters[i][1] = xmu_f;
    bestfit_parameters[i][2] = xmu_b;
    bestfit_parameters[i][3] = fraction_p;
    bestfit_parameters[i][4] = fraction_m;
    // std::cout << xsigma_f << " " << xmu_f << " " <<xsigma_b << " " << xmu_b << std::endl;
   
    // std::cout << bestchi2ndf << std::endl;

    TCanvas *c1 = new TCanvas("c1","c1",800,600);
    c1->SetLeftMargin(0.12);    // Adjust as needed
    c1->SetRightMargin(0.04);   // Adjust as needed
    c1->SetBottomMargin(0.12);  // Adjust as needed
    c1->SetTopMargin(0.06);     // Adjust as needed

    best_stack->Scale(data->Integral()/best_stack->Integral());
    mc_combined.Scale(data->Integral()/mc_combined.Integral());


    float largest_bin_stack = 0;
    for (int j = 1; j<=best_stack->GetNbinsX(); j ++){
        if (best_stack->GetBinContent(j) >= largest_bin_stack) largest_bin_stack = best_stack->GetBinContent(j);
    }

    float largest_bin_combined = 0;
    for (int j = 1; j<=mc_combined.GetNbinsX(); j ++){
        if (mc_combined.GetBinContent(j) >= largest_bin_combined) largest_bin_combined = mc_combined.GetBinContent(j);
    }

    float largest_bin_data = 0;
    for (int j = 1; j<=data->GetNbinsX(); j ++){
        if (data->GetBinContent(j) >= largest_bin_data) largest_bin_data = data->GetBinContent(j);
    }

    float ymax = TMath::Max(TMath::Max(largest_bin_data, largest_bin_combined), largest_bin_stack);



    // mc_combined->Scale(data->Integral()/mc_combined->Integral());
    // mc_combined->SetLineColor(kRed);
    // mc_combined->SetLineStyle(2);
    // mc_combined->Draw("hist same");
    best_stack->GetYaxis()->SetRangeUser(0., 1.2 * ymax);
    best_stack->GetXaxis()->SetTitle("ToF [ns]");
    best_stack->GetYaxis()->SetTitle("Events");
    best_stack->GetXaxis()->SetTitleSize(0.05); // Adjust the value as needed
    best_stack->GetYaxis()->SetTitleSize(0.05); // Adjust the value as needed

    best_stack->GetXaxis()->CenterTitle();
    best_stack->GetYaxis()->CenterTitle();

    best_stack->SetLineColor(kBlue);
    best_stack->SetLineStyle(1);
    best_stack->SetLineWidth(1);
    best_stack->Draw("hist");

    mc_combined.SetLineColor(kRed);
    mc_combined.SetLineStyle(1);
    mc_combined.SetLineWidth(1);
    mc_combined.Draw("hist same");

    data->SetLineColor(kBlack);
    data->SetLineStyle(1);
    data->SetLineWidth(1);
    data->Draw("hist same");

    string str_data("Data");
    string str_nominal("Nominal MC chi^2/NDF ");
    string str_smeared("Corrected MC chi^2/NDF ");

    double nominal_chi2 = mc_combined.Chi2Test(data, "CHI2/NDF");
    double slip_chi2 = best_stack->Chi2Test(data, "CHI2/NDF");

    auto legend = new TLegend(0.0,0.8,0.5,1.0);

    legend->AddEntry(data, str_data.c_str(),"lep");
    legend->AddEntry(&mc_combined, Form("Nominal MC chi2 %.4f", nominal_chi2),"l");
    legend->AddEntry(best_stack,Form("Corrected MC chi2 %.4f", slip_chi2),"l");
    legend->SetHeader(sample_names_thesis[i].c_str(), "l"); // option "C" allows to center the header
    // gStyle->SetLegendTextSize(5);

    legend->Draw();


    TText *t1 = new TText(-15,0.8 * ymax , Form("SB %.2f MB %.2f",xsigma_b, xmu_b));
    TText *t2 = new TText(-15,0.7 * ymax , Form("SF %.2f MF %.2f",xsigma_f, xmu_f));
    TText *t3 = new TText(-15,0.6 * ymax , Form("-10 %.3f +10 %.3f",fraction_m, fraction_p));

    // t1->SetTextAlign(22);
    // t1->SetTextColor(kBlack);
    // t1->SetTextFont(43);
    // t1->SetTextSize(20);
    // t1->Draw();

    // t2->SetTextAlign(22);
    // t2->SetTextColor(kBlack);
    // t2->SetTextFont(43);
    // t2->SetTextSize(20);
    // t2->Draw();

    // t3->SetTextAlign(22);
    // t3->SetTextColor(kBlack);
    // t3->SetTextFont(43);
    // t3->SetTextSize(20);
    // t3->Draw();



    c1->Update();
    // c1->Print("/home/t2k/yxu/banffworkbench/fittest.png");

    c1->Print((output_folder + std::string(Form("%d_%s",i, sample_names[i].c_str())) + suffix).c_str());
    // if (i==0){
    //     c1->Print("/home/t2k/yxu/banffworkbench/grid_test.pdf[");
    // }
    // else if (i==21){
    //     c1->Print("/home/t2k/yxu/banffworkbench/grid_test.pdf]");
    // }
    // else{
    //     c1->Print("/home/t2k/yxu/banffworkbench/grid_test.pdf");
    // }





    // TF1* kernel_f = new TF1("Convolution_kernel F","gaus",-20,20);
    // TF1* kernel_b = new TF1("Convolution_kernel B","gaus",-20,20);

    // kernel->SetParameters(1, xmu_f, xsigma_f);
    // kernel->SetParameters(1, xmu_b, xsigma_b);

    // TH1D* kernel_f_th1 = new TH1D("convolution_kernel_th1 F", "Convolution kernel_th1", 40,-20,20);
    // TH1D* kernel_b_th1 = new TH1D("convolution_kernel_th1 B", "Convolution kernel_th1", 40,-20,20);

    // for (int i = 1; i < 41; i++){
    //     kernel_f_th1->SetBinContent(i, kernel_f->Eval(kernel_f_th1->GetBinCenter(i)));
    //     kernel_b_th1->SetBinContent(i, kernel_b->Eval(kernel_b_th1->GetBinCenter(i)));



    // }

    cout << sample_names[i] << " Sigma: " << bestfit_parameters[i][0] << "Mu F: " << bestfit_parameters[i][1] << "Mu B: " << bestfit_parameters[i][2] << "Frac P: " << bestfit_parameters[i][3] << "Frac M: " << bestfit_parameters[i][4] << endl;
    string result_summary_file = output_folder + string("output_summary");
    std::ofstream myfile;
    myfile.open(result_summary_file.c_str(), std::ios_base::app);
    if (myfile.is_open())
    {
        myfile << Form("%i %s Sigma: %.4f MuF:%.4f MuB:%.4f FP:%.4f FM%.4f \n", i, sample_names[i].c_str(), bestfit_parameters[i][0], bestfit_parameters[i][1], bestfit_parameters[i][2], bestfit_parameters[i][3], bestfit_parameters[i][4]);
        myfile.close();
    }
    else cout << "Unable to open file";



}

return 0;
}
