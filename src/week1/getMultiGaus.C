TString getMultiGaus(Int_t gaus_num){
    // create gaus + gaus + ...
    TString multi_gaus = "";
    for (Int_t i=0; i<gaus_num; i++){ multi_gaus += "+gaus(" + to_string(3*i) + ")"; }
    multi_gaus = multi_gaus(1, multi_gaus.Length()-1);
    return multi_gaus;
}