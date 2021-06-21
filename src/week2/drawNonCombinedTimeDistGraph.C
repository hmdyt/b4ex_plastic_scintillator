TGraphErrors* drawEachNonCombinedTimeDistGraph(TString tar_channel_low){
    vector<TString> calb_distances = {"0", "140", "280", "420", "560", "670"};
    TString tar_channel_high = getInverseChannel(tar_channel_low);

    // init TGraph
    TGraphErrors* g = new TGraphErrors();
    g->SetTitle(";time lag[ps];distance [mm]");

    // fill
    Double_t x, y, x_err, y_err;
    pair<Double_t, Double_t> tmp_low, tmp_high;
    for (Int_t i = 0; i < calb_distances.size(); i++){
        // fetch
        tmp_low = fitDelayHist(calb_distances[i], {tar_channel_low});
        tmp_high = fitDelayHist(calb_distances[i], {tar_channel_high});
        // prepare points
        x     = tmp_low.first - tmp_high.first;
        x_err = sqrt( pow(tmp_low.second, 2) + pow(tmp_high.second, 2) );
        y     = (Double_t)stod((string)calb_distances[i]);
        y_err = 0;
        // set
        g->SetPoint(i, x, y);
        g->SetPointError(i, x_err, y_err);
    }

    // init TF1 and fit
    TF1* f = new TF1("f", "[0]*x + [1]", -8196, 8196);
    f->SetParameters(y/x, 0);
    g->Fit(f, "R");

    return g;
}

void drawNonCombinedTimeDistGraph(){
    vector<TString> tar_chs = {"28", "29", "30", "31"};
    map<TString, TGraphErrors*> gg;
    for (Int_t i = 0; i < tar_chs.size(); i++){
        gg[tar_chs[i]] = drawEachNonCombinedTimeDistGraph(tar_chs[i]);
    }

    TCanvas* c_drawNonCombined = new TCanvas();
    auto leg = new TLegend(0.5, 0.6, 0.89, 0.89,"Legend");
    for (Int_t i = 0; i < tar_chs.size(); i++){
        leg->AddEntry(gg[tar_chs[i]], "ch" + tar_chs[i], "l");
    }
    
    gg[tar_chs[0]]->Draw("AP");
    for (Int_t i = 1; i < tar_chs.size(); i++){ gg[tar_chs[i]]->Draw("P SAME"); }
    leg->Draw();
    c_drawNonCombined->Draw();
    c_drawNonCombined->SaveAs("img/week2/drawNonCombinedTimeDistGraph.pdf");
    c_drawNonCombined->SaveAs("img/week2/drawNonCombinedTimeDistGraph.svg");
}