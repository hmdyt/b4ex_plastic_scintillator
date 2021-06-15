vector<pair<Double_t, Double_t>> fitLEDXXXX_CHXX_Pedestal(
    TString FILENAME = "led3018.root",
    TString FILENAME_Pedestal = "led3022.root",
    TString CHANNEL = "26",
    Double_t XMIN = 800,
    Double_t XMAX = 1350,
    Double_t FIT_RANGE_MIN = 800,
    Double_t FIT_RANGE_MAX = 1260,
    Int_t peakmax = 10
){   
    // fetch and configurate hist
    TH1D* hist = getHistMPPC(FILENAME, CHANNEL);
    hist->GetXaxis()->SetRangeUser(XMIN, XMAX);
    hist->SetTitle(FILENAME + " " + CHANNEL + ";ADC value;Events");

	// search peak 
	vector<pair<Double_t, Double_t>> search_peak = searchPeak(hist, peakmax);

	const Int_t GAUSNUM = search_peak.size();
    const TString MULTIGAUS = getMultiGaus(GAUSNUM);

    // init TF1
    TF1* f = new TF1("f", MULTIGAUS, FIT_RANGE_MIN, FIT_RANGE_MAX);
    f->SetNpx(10000);

    // set parnames
    for (Int_t i=0; i<GAUSNUM; i++) {
        f->SetParName(3*i + 0, (TString)to_string(i) + (TString)"th Const");
        f->SetParName(3*i + 1, (TString)to_string(i) + (TString)"th Mean"); 
        f->SetParName(3*i + 2, (TString)to_string(i) + (TString)"th Sigma"); 
    }

    // set init params from setting file
    Double_t ini_sigma =20;
	for (Int_t i=0; i<GAUSNUM; i++){
        f->SetParameter(3*i + 0, search_peak[i].second);
        f->SetParameter(3*i + 1, search_peak[i].first);
        f->SetParameter(3*i + 2, ini_sigma);
        f->SetParLimits(3*i + 2, 0, 100);
    }
    
    // execute fitting	
	hist->Fit(f, "R");

    // draw and save
    auto c = new TCanvas();
    getHistMPPC(FILENAME_Pedestal, CHANNEL)->Draw();
    hist->Draw("SAME");
    c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + "_Pedestal.pdf");
    c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + "_Pedestal.svg");

    // return gaussian means
    // res = {pair(mean1, mean1_error), pair(mean2, mean2_error)}
    vector<pair<Double_t, Double_t>> res;
    for (Int_t i=0; i<GAUSNUM; i++){
        res.push_back(make_pair(
            f->GetParameter(3*i + 1), 
            f->GetParError(3*i + 1)
            ));
    }
    sort(res.begin(), res.end());
    return res;
}
