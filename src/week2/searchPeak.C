vector<pair<Double_t, Double_t>> searchSinglePeak(TH1D *hist){

	// init parameter
	Int_t max_peak = 1;
	Int_t sigma = 3;

	//search peak
	TSpectrum *spectrum = new TSpectrum(max_peak);
	spectrum->Search(hist, sigma, "new");

	// get peak parameter
	Double_t *xpeak = spectrum->GetPositionX();
	Double_t *ypeak = spectrum->GetPositionY();

	vector<pair<Double_t, Double_t>> res;

	// make pair
	pair <Double_t, Double_t> p;
	p = make_pair(xpeak[0], ypeak[0]);
	res.push_back(p);

	return res;
}
