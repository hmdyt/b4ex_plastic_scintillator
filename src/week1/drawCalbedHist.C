void drawCalbedHist(TString file_name = "led3018.root", TString channel = "26"){
    // run <=> pedestal table
    map<TString, TString> pedestal_file_name = {
        {"led3018.root", "led3022.root"},
        {"led3019.root", "led3023.root"},
        {"led3020.root", "led3024.root"},
        {"led3021.root", "led3025.root"},
    };

    // hist ranges -> pair(x_min, x_max)
    map<TString, pair<Double_t, Double_t>> hist_range = {
        {"led3018.root", make_pair(800, 1350)},
        {"led3019.root", make_pair(800, 1750)},
        {"led3020.root", make_pair(800, 2100)},
        {"led3021.root", make_pair(800, 2600)},
    };

    // init hist
    auto hist = getHistMPPC(file_name, channel);
    hist->SetTitle(file_name + " " + channel + "ch;Number of photon;Event");

    // calibration
    TString run_number = file_name(3, 4) + (TString)"_CH" + channel;
    const Double_t pedestal_mean = getPedestalMean(pedestal_file_name[file_name], channel);
    const Double_t peak_width = determineMeanWidth(run_number).first;
    auto ADCToNPhoton = [](Double_t x, Double_t m, Double_t a){ return m * (x - a); };
    hist->GetXaxis()->SetLimits(
        ADCToNPhoton(0, 1/peak_width, pedestal_mean),
        ADCToNPhoton(4096, 1/peak_width, pedestal_mean)
    );
    hist->GetXaxis()->SetRangeUser(
        ADCToNPhoton(hist_range[file_name].first, 1/peak_width, pedestal_mean),
        ADCToNPhoton(hist_range[file_name].second, 1/peak_width, pedestal_mean)
    );

    // save and draw
    TCanvas* c = new TCanvas();
    hist->Draw();
    c->SaveAs("img/week1/" + run_number + "_Clbed.svg");
    c->SaveAs("img/week1/" + run_number + "_Clbed.pdf");
}