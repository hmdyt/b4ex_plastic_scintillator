void determineMeanWidth(TString run_number = "3018_CH26"){
    // string correspond to function
    map<TString, vector<pair<Double_t, Double_t>>(*)()> fitLED = {
        {"3018_CH26", fitLED3018_CH26},
        {"3018_CH29", fitLED3018_CH29},
        {"3019_CH26", fitLED3019_CH26},
        {"3019_CH29", fitLED3019_CH29},
        {"3020_CH26", fitLED3020_CH26},
        {"3020_CH29", fitLED3020_CH29},
        {"3021_CH26", fitLED3021_CH26},
        {"3021_CH29", fitLED3021_CH29},
    };

    // fetch many gaussians fitting data
    vector<pair<Double_t, Double_t>> fitted_means = fitLED[run_number]();
    
    // initialize TGraph
    TGraphErrors* g = new TGraphErrors();
    g->SetTitle("Each width between gaussians (" + run_number + ");x th width;width [ADC value]");

    // fill i_width-width points
    Double_t mean_big, mean_small, mean_big_error, mean_small_error, width, width_error;
    for (Int_t i=0; i<fitted_means.size() - 1; i++){
        mean_big         = fitted_means[i+1].first;
        mean_big_error   = fitted_means[i+1].second;
        mean_small       = fitted_means[i].first;
        mean_small_error = fitted_means[i].second;
        width = mean_big - mean_small;
        width_error = sqrt( pow(mean_big_error, 2) + pow(mean_small_error, 2) );
        g->SetPoint(i, i, width);
        g->SetPointError(i, 0, width_error);
    }

    // initialize fitting TF1 as constant
    TF1* f = new TF1("f", "[0]", 0, 1000);
    f->SetParName(0, "width");

    // execute fitting
    g->Fit(f, "R");

    // draw and save
    auto c = new TCanvas();
    g->Draw("AP");
    c->Draw();
    c->SaveAs("img/week1/" + run_number + ".svg");
    c->SaveAs("img/week1/" + run_number + ".pdf");
}