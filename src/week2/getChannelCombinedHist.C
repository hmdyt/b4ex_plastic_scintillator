TH1D* getChannelCombinedHist(
    TString tar_dist = "140",
    vector<TString> tar_channels = {"28", "29", "30", "31"}
)
{
    // init
    vector<TString> tar_files;

    // get target run number from info.txt
    ifstream ifs("data/week2/info.txt");
    TString run_number, HV_MPPC, HV_trig, distance, events;
    while (ifs >> run_number >> HV_MPPC >> HV_trig >> distance >> events){
        if (tar_dist != distance) continue;
        if (tar_dist == distance) tar_files.push_back(run_number + ".root");
    }

    // histogram for return
    // init hist name
    TString hist_res_name = tar_dist + "mm";
    for (Int_t i=0; i<tar_channels.size(); i++){ hist_res_name += " " + tar_channels[i]; }
    // init hist
    TH1D* hist_res = new TH1D(hist_res_name, hist_res_name + ";Time;Event", 4096, 0, 8196);

    // fill to hist_res
    TH1D* hist_tmp;
    Double_t hist_tmp_nbins;
    for (Int_t i = 0; i < tar_files.size(); i++){
        for(Int_t j = 0; j < tar_channels.size(); j++){
            hist_tmp = (TH1D*)TFile::Open("data/week2/" + tar_files[i])->Get("TDC_LEADING_" + tar_channels[j]);
            hist_tmp_nbins = hist_tmp->GetNbinsX();
            cout << hist_tmp_nbins << endl;
            for (Int_t k = 0; k < hist_tmp_nbins; k++){
                for (Int_t l = 0; l < (Int_t)hist_tmp->GetBinContent(k); l++){
                    hist_res->Fill(k);
                }
            }
        }
    }

    // evil
    hist_res->GetXaxis()->SetLimits(0, 8196*2);

    return hist_res;
}