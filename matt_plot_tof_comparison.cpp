
void format_hist(TH1D* hist, EColor col, int style=1, int width=2, int scale=100) {
  hist->SetLineColor(col);
  hist->SetLineWidth(width);
  hist->SetLineStyle(style);
  hist->Scale(scale/hist->Integral());
}


void matt_plot_tof_comparison(){
	
	gROOT->SetBatch();

	TFile *p7 = new TFile("/home/t2k/aspeers/ToF_Systematics/ToF_Output_P7_run4.root");
	TIter nextp7(p7->GetListOfKeys());
	TKey *keyp7 = NULL;
	
	TFile *p6 = new TFile("/home/t2k/aspeers/ToF_Systematics/ToF_Output_P6_run4.root");
	TIter nextp6(p6->GetListOfKeys());
	TKey *keyp6 = NULL;
	
	TCanvas *canv = new TCanvas("canv", "canv", 1024, 1024);
	TString pdfname = "ToF_Plots_comparison.pdf"; // name of pdf
	canv->Print(pdfname+"["); // open multi-page pdf
	
	
	while ((keyp7 = (TKey*)nextp7())) {
		keyp6 = (TKey*)nextp6();
		std::string classname = keyp7->GetClassName();
		// Check the class name to be sure
		if (classname.find("TH1D") == std::string::npos) continue;

		auto legend = new TLegend(0.1,0.8,0.28,0.9);		
		THStack *hs = new THStack("hs",Form("%s;ToF (ns);Entries (%%)",keyp7->GetName()));

		p7->cd();
		TH1D *temp1 = (TH1D*)gDirectory->Get(keyp7->GetName());
		format_hist(temp1, kRed);
		legend->AddEntry(temp1, "Production 7", "l");
		hs->Add(temp1);
		
		p6->cd();
		TH1D *temp2 = (TH1D*)gDirectory->Get(keyp6->GetName());
		format_hist(temp2, kBlue, 0);
		legend->AddEntry(temp2, "Production 6", "l");
		hs->Add(temp2);
		
		canv->cd();
		hs->Draw("NOSTACK HIST");
		//temp2->Draw();
		legend->Draw();
		
		canv->Print(pdfname); // add new page to pdf
		canv->SaveAs(Form("ToF_plots/%s.png",keyp7->GetName()));
	}
	
	canv->Print(pdfname+"]"); // close multi-page pdf


}