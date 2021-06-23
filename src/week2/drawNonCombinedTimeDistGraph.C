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

    return g;
}

TF1* initEachNonCombinedTimeDistFunc(TGraphErrors* g){
    TF1* f = new TF1("f", "[0]*x + [1]", -8196, 8196);
    Double_t x_1 = g->GetPointX(1);
    Double_t y_1 = g->GetPointY(1);
    Double_t x_2 = g->GetPointX(4);
    Double_t y_2 = g->GetPointY(4);
    Double_t grad = (y_2 - y_1) / (x_2 - x_1);
    Double_t segm = (y_1 * x_2 - y_2 * x_1) / (x_2 - x_1);
    f->SetParameters(grad, segm);
    return f;
}

void drawNonCombinedTimeDistGraph(vector<TString> tar_chs = {"28", "29", "30", "31"}){
    TString tar_chs_now;
    vector<TF1*> fs;
    map<Int_t, EColor> fit_color = { {0, kRed}, {1, kBlue}, {2, kGreen}, {3, kCyan}, };
    map<Int_t, Int_t> point_style = {{0, 8}, {1, 3}, {2, 4}, {3, 5},};
    map<TString, TGraphErrors*> gg;
    for (Int_t i = 0; i < tar_chs.size(); i++){
        tar_chs_now = tar_chs[i];
        TGraphErrors* g_i = drawEachNonCombinedTimeDistGraph(tar_chs_now);
        g_i->SetMarkerStyle(point_style[i]);
        TF1* f_i = initEachNonCombinedTimeDistFunc(g_i);
        f_i->SetLineColor(fit_color[i]);
        fs.push_back(f_i);
        g_i->Fit(fs[i], "R");
        gg[tar_chs_now] = g_i;
    }

    TCanvas* c_drawNonCombined = new TCanvas();
    auto leg1 = new TLegend(0.3, 0.6, 0.4, 0.9, "");
    for (Int_t i = 0; i < tar_chs.size(); i++){
        leg1->AddEntry(gg[tar_chs[i]], "ch" + tar_chs[i], "p");
    }
    auto leg2 = new TLegend(0.15, 0.6, 0.3, 0.9, "");
    for (Int_t i = 0; i < fs.size(); i++){
        leg2->AddEntry(fs[i], "ch" + tar_chs[i], "l");
    }
    
    // identify name
    TString identify_name = "_ch";
    for (Int_t i = 0; i < tar_chs.size(); i++){
        identify_name += "_" + tar_chs[i];
    }

    gg[tar_chs[0]]->Draw("AP");
    for (Int_t i = 0; i < tar_chs.size(); i++){ gg[tar_chs[i]]->Draw("P SAME"); }
    leg1->Draw();
    leg2->Draw();
    c_drawNonCombined->Draw();
    c_drawNonCombined->SaveAs("img/week2/NonCombinedTimeDistGraph" + identify_name + ".pdf");
    c_drawNonCombined->SaveAs("img/week2/NonCombinedTimeDistGraph" + identify_name + ".svg");
}