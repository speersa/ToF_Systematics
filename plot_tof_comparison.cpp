void format_hist(TH1D* hist, EColor col, int style=1, int width=2, int scale=100) {
  hist->SetLineColor(col);
  hist->SetLineWidth(width);
  hist->SetLineStyle(style);
  hist->Scale(scale/hist->Integral());
}


void plot_tof_comparison() {
  gROOT->SetBatch();
  gStyle->SetOptStat(1111);
  
  TFile *p7 = TFile::Open("ToF_Output_P7_run4air.root");
  if ((!p7) || p7->IsZombie()) {delete p7; return; } // just a precaution
  
  TFile *p6 = TFile::Open("ToF_Output_P6_run4air.root");
  if ((!p6) || p6->IsZombie()) { delete p7; delete p6; return; } // just a precaution
  
  TCanvas *canv = new TCanvas("canv", "canv", 1024, 1024);
  TString pdfname = "ToF_Plots_comparison.pdf"; // name of pdf
  canv->Print(pdfname+"["); // open multi-page pdf
  
  TIter nextp7(p7->GetListOfKeys());
  TKey *keyp7 = 0;
  
  while ((keyp7 = (TKey*)nextp7())) {
    std::string classname = keyp7->GetClassName();
    // Check the class name to be sure
    if (classname.find("TH1D") == std::string::npos) continue;
    
    TH1D *temp1; p7->GetObject(keyp7->GetName(), temp1);
    if (!temp1) continue; // just a precaution
    format_hist(temp1, kBlue);
    
    TH1D *temp2; p6->GetObject(keyp7->GetName(), temp2); // get the histogram with the same name
    if (!temp2) { delete temp1; continue; } // just a precaution
    format_hist(temp2, kRed);
    
    THStack *hs = new THStack("hs",Form("%s;ToF (ns);Entries (%%)",keyp7->GetName()));
    hs->Add(temp1, "hist");
    hs->Add(temp2, "hist");
    
    auto legend = new TLegend(0.1,0.8,0.45,0.9);
    legend->AddEntry(temp1, "Production 7 run8water", "l");
    legend->AddEntry(temp2, "Production 6 run8water", "l");
    
    canv->cd();
    hs->Draw("nostack");
    legend->Draw();
	gPad->Update();
	TPaveStats *st = (TPaveStats*)hs->FindObject("stats");
    
    canv->Print(pdfname); // add new page to pdf
    canv->SaveAs(Form("ToF_plots/%s.png",keyp7->GetName()));
    
    delete hs; delete legend; delete temp1; delete temp2; // no longer needed
  }
  
  canv->Print(pdfname+"]"); // close multi-page pdf
  delete canv; // no longer needed
  
  delete p6; delete p7; // no longer needed
}