pair<Double_t, Double_t> drawTimeDistGraph(
    // init calibration distances
    vector<TString> target_channels_low  = {"28", "29", "30", "31"},
    vector<TString> calb_distances = {"0", "140", "280", "420", "560", "670"}
){
    vector<TString> target_channels_high;
    for (Int_t i = 0; i < target_channels_low.size(); i++){ target_channels_high.push_back(getInverseChannel(target_channels_low[i])); }

    // init TGraphErrors
    // x -> time, y -> distance
    TGraphErrors* g = new TGraphErrors();
    g->SetTitle(";time lag [ps];distance [mm]");

    // set points
    // init tmp variables
    Double_t x, y, x_err, y_err;
    pair<Double_t, Double_t> tmp_low, tmp_high;
    for (Int_t i=0; i < calb_distances.size(); i++){
        // fetch
        tmp_low  = fitDelayHist(calb_distances[i], target_channels_low);
        tmp_high = fitDelayHist(calb_distances[i], target_channels_high);
        // prepare points
        x     = tmp_low.first - tmp_high.first;
        x_err = sqrt( pow(tmp_low.second, 2) + pow(tmp_high.second, 2) );
        y     = (Double_t)stod((string)calb_distances[i]);
        y_err = 0;
        // set
        g->SetPoint(i, x, y);
        g->SetPointError(i, x_err, y_err);
    }

    // init canvas
    TCanvas* c = new TCanvas();

    // init TF1 and fit
    TF1* f = new TF1("f", "[0]*x + [1]", -8196, 8196);
    f->SetParameters(y/x, 0);
    g->Fit(f, "R");

    // save and draw
    TString identify_name = "_ch";
    for (Int_t i = 0; i < target_channels_low.size(); i++){
        identify_name += "_" + target_channels_low[i];
    }
    g->Draw("AP");
    c->Draw();
    c->SaveAs("img/week2/time_distance_graph" + identify_name + ".pdf");
    c->SaveAs("img/week2/time_distance_graph" + identify_name + ".svg");

    // return y=ax+b pair(a, b)
    Double_t a = f->GetParameter(0);
    Double_t b = f->GetParameter(1);
    return make_pair(a, b);
}