void format_hist(TH1D* hist, EColor col, int style=1, int width=2, int scale=100) {
  hist->SetLineColor(col);
  hist->SetLineWidth(width);
  hist->SetLineStyle(style);
  hist->Scale(scale/hist->Integral());
}


void Double_Plot_Root() {
  gROOT->SetBatch();
  gStyle->SetOptStat(1111);
  
  TFile *p7MC = TFile::Open("P7_V12_run4air_Gaussian_MC.root"); 
  TFile *p7Data = TFile::Open("P7_V13_run4air_Gaussian_Data.root");
  
  TFile *p6MC = TFile::Open("P6AA_run4air_Gaussian_MC.root"); 
  TFile *p6Data = TFile::Open("P6AA_run4air_Gaussian_Data.root");
  
  TCanvas *canv = new TCanvas("canv", "canv", 1024, 1024);
  TString pdfname = "run4air_Gaussian_Plots_comparison.pdf"; // name of pdf
  canv->Print(pdfname+"["); // open multi-page pdf
  
  TIter nextp7MC(p7MC->GetListOfKeys());
  TKey *keyp7MC = 0;
  
  TIter nextp7Data(p7Data->GetListOfKeys());
  TKey *keyp7Data = 0;
  
  while ((keyp7MC = (TKey*)nextp7MC())) {
	  keyp7Data = (TKey*)nextp7Data();
    std::string classname = keyp7MC->GetClassName();
    // Check the class name to be sure
    if (classname.find("TH1D") == std::string::npos) continue;
    
    TH1D *temp1; p7MC->GetObject(keyp7MC->GetName(), temp1);
    format_hist(temp1, kBlue);
	
	TH1D *temp2; p7Data->GetObject(keyp7Data->GetName(), temp2);
    format_hist(temp2, kGreen);
    
    TH1D *temp3; p6MC->GetObject(keyp7MC->GetName(), temp3); // get the histogram with the same name
    format_hist(temp3, kRed);
	
	TH1D *temp4; p6Data->GetObject(keyp7Data->GetName(), temp4); // get the histogram with the same name
    format_hist(temp4, kMagenta);
    
    THStack *hs = new THStack("hs",Form("%s;ToF (ns);Entries (%%)",keyp7MC->GetName()));
    hs->Add(temp1, "hist");
    hs->Add(temp2, "hist");
	hs->Add(temp3, "hist");
	hs->Add(temp4, "hist");
    
    auto legend = new TLegend(0.1,0.8,0.45,0.9);
    legend->AddEntry(temp1, "Production 7 MC", "l");
    legend->AddEntry(temp2, "Production 7 Data", "l");
	legend->AddEntry(temp3, "Production 6 MC", "l");
	legend->AddEntry(temp4, "Production 6 Data", "l");
    
    canv->cd();
    hs->Draw("nostack");
    legend->Draw();
	gPad->Update();
	TPaveStats *st = (TPaveStats*)hs->FindObject("stats");
    
    canv->Print(pdfname); // add new page to pdf
   // canv->SaveAs(Form("ToF_plots/%s.png",keyp7->GetName()));
    
  //  delete hs; delete legend; delete temp1; delete temp2; // no longer needed
  }
  
  canv->Print(pdfname+"]"); // close multi-page pdf
 // delete canv; // no longer needed
  
//  delete p6; delete p7; // no longer needed
}