vector<pair<Double_t, Double_t>> searchPeak(TH1D *hist, Int_t maxpeaks){
	// search peak
	Int_t sigma = 3;
	TSpectrum *spectrum = new TSpectrum(maxpeaks);
	spectrum->Search(hist, sigma, "new");
	
	// get peak parameter
	Double_t *xpeak = spectrum->GetPositionX();
	Double_t *ypeak = spectrum->GetPositionY();
	Int_t npeak = spectrum->GetNPeaks();
	for(Int_t i = 0; i < npeak; i++){
		cout << xpeak[i] << " " << ypeak[i] << endl;
	}

	vector<pair<Double_t, Double_t>> res;
	
	pair <Double_t, Double_t> p;

	for(Int_t i = 0; i < npeak; i++){
		p = make_pair(xpeak[i], ypeak[i]);
		res.push_back(p);
	}
	for(Int_t i = 0; i < npeak; i++){
		cout << res[i].first << " " << res[i].second << endl;
	}
	return res;
}
