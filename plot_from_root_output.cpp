

void plot_from_root_output(){
	
	gROOT->SetBatch();

	TFile *f = new TFile("ToF_Output.root");
	TIter next(f->GetListOfKeys());
	TKey *key = NULL;
	TCanvas *canv = new TCanvas("canv", "canv", 1024, 1024);
	TString pdfname = "ToF_Plots.pdf"; // name of pdf
	canv->Print(pdfname+"["); // open multi-page pdf
	
	
	while ((key = (TKey*)next())) {
		std::string classname = key->GetClassName();
		// Check the class name to be sure
		if (classname.find("TH1D") == std::string::npos) continue;
		TH1D *temp = (TH1D*)gDirectory->Get(key->GetName());
		// Or use key->ReadObj()...
		canv->cd();
		temp->Draw();
		canv->Print(pdfname); // add new page to pdf
		
		canv->SaveAs(Form("ToF_plots/%s.png",key->GetName()));
	}
	
	canv->Print(pdfname+"]"); // close multi-page pdf


}