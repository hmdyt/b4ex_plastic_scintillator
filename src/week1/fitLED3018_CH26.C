void fitLED3018_CH26(){
    // init file propaties
    const TString FILENAME = "led3018.root";
    const TString CHANNEL = "26";
    const Double_t XMIN = 800;
    const Double_t XMAX = 1350;

    // init fitting propaties
    //const Int_t GAUSNUM = 10;
    const Double_t FIT_RANGE_MIN = 800;
    const Double_t FIT_RANGE_MAX = 1260;
    const TString SETTING_FILE = "src/week1/settings/fitLED3018_CH26.txt";

    // fetch and configurate hist
    TH1D* hist = getHistMPPC(FILENAME, CHANNEL);
    hist->GetXaxis()->SetRangeUser(XMIN, XMAX);
    hist->SetTitle(FILENAME + " " + CHANNEL);

	// search peak 
	const Int_t peakmax = 10;
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
    hist->Draw();
    //c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + ".pdf");
    //c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + ".svg");
}
