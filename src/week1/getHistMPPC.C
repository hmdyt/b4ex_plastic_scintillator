TH1D* getHistMPPC(TString filename, TString channel){
    TFile* file = TFile::Open("data/week1/" + filename);
    TH1D* hist = (TH1D*)file->Get("ADC_HIGH_" + channel);
    return hist;
}