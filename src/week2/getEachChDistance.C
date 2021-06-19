vector<vector<Double_t>> getEachChDistance(TChain* chain){
    // init for calling existing branch
    Int_t VadcHigh[64];
    Int_t VtdcLeading[64];
    TBranch* b_VadcHigh;
    TBranch* b_VtdcLeading;
    chain->SetBranchAddress("VadcHigh", VadcHigh, &b_VadcHigh);
    chain->SetBranchAddress("VtdcLeading", VtdcLeading, &b_VtdcLeading);

    // for res
    vector<vector<Double_t>> res;
    vector<Double_t> res_child;
    Int_t ch_low, ch_high;

    // fetch calibration parameter
    pair<Double_t ,Double_t> param_tmp = drawTimeDistGraph(
        {"28", "29", "30", "31"},
        {"0", "140", "280", "420", "560", "670"}
    );

    // init calibration function
    Double_t a = param_tmp.first;
    Double_t b = param_tmp.second;
    auto f_calb = [](Double_t a, Double_t b, Double_t x){ return a * x + b; };

    // calb and then fill into res
    for (Int_t i = 0; i < chain->GetEntries(); i++){
        chain->GetEntry(i);
        res_child = {};
        for (Int_t j = 0; j < 32; j++){
            ch_low = j;
            ch_high = (Int_t) stoi((string) getInverseChannel((TString) to_string((int) ch_low)));
            if (
                VadcHigh[ch_low] > 1000 &&
                VadcHigh[ch_high] > 1000
                ){
                res_child.push_back(f_calb(a, b, (Double_t) VtdcLeading[ch_low] - VtdcLeading[ch_high]));
            } else {
                res_child.push_back(10);
            }
        }
        res.push_back(res_child);
    }
    return res;
}