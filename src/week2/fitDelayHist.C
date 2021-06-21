pair<Double_t, Double_t> fitDelayHist(
	TString distance = "140",
	vector<TString> tar_channels = {"28", "29", "30", "31"}
){

	// init fitting para
	//Int_t FitMin = 0;
	//Int_t FitMax = 8000;

	// get fitting parameter
	TH1D *hist = getChannelCombinedHist(distance, tar_channels);
	vector<pair<Double_t, Double_t>> peak = searchSinglePeak(hist);
	Double_t Mean = peak[0].first;
	Double_t Const = peak[0].second;
	Double_t Sigma = 0;
	
	Int_t FitMin = Mean - 50;
	Int_t FitMax = Mean + 50;
	
	cout << Mean << " " << Const << " " << Sigma << endl;

	// make fit
	TF1 *f = new TF1("f", "gaus", FitMin, FitMax);

	// set fitting parameter
	f->SetParameter(0, Const);
	f->SetParameter(1, Mean);
	f->SetParameter(2, Sigma);
	f->SetParLimits(2, 0, 20);

	// set para name
	f->SetParName(0, "Const");
	f->SetParName(1, "Mean");
	f->SetParName(2, "Sigma");

	// execute fitting
	hist->Fit(f, "R");

	// get parameter
	Double_t Peak_Mean = f->GetParameter(1);
	Double_t Peak_Sigma = f->GetParameter(2);
	Double_t Mean_Error = f->GetParError(1);

	// prepare identify name for saving filename
	TString identify_name = "_ch";
	for (Int_t i = 0; i < tar_channels.size(); i++){
		identify_name += "_" + tar_channels[i];
	}

	// draw and save
	auto c = new TCanvas();
	hist->GetXaxis()->SetRangeUser(Peak_Mean - 10 * Peak_Sigma, Peak_Mean + 10 * Peak_Sigma );
	hist->Draw();
	c->SaveAs("img/week2/Combined" + distance + "mm" + identify_name + ".pdf");
	c->SaveAs("img/week2/Combined" + distance + "mm" + identify_name + ".svg");
	
	//make pair
	pair<Double_t, Double_t> res_pair;
	
	res_pair = make_pair(Peak_Mean, Mean_Error);

	return res_pair;
}
