void drawVoltWidthGraph(bool is_show_zero = false){
    // init run numbers in order to call determineMeanWidth
    vector<TString> run_numbers_ch26 = {
        "3018_CH26",
        "3019_CH26",
        "3020_CH26",
        "3021_CH26"
    };
    vector<TString> run_numbers_ch29 = {
        "3018_CH29",
        "3019_CH29",
        "3020_CH29",
        "3021_CH29"
    };

    // init HV
    map<TString, Double_t> HVs_ch26 = {
        {"3018_CH26", 52.99},
        {"3019_CH26", 53.50},
        {"3020_CH26", 54.00},
        {"3021_CH26", 54.50},
    };
    map<TString, Double_t> HVs_ch29 = {
        {"3018_CH29", 52.99},
        {"3019_CH29", 53.50},
        {"3020_CH29", 54.00},
        {"3021_CH29", 54.50},
    };
    
    // init TGraphErrors
    TGraphErrors* g_ch26 = new TGraphErrors();
    TGraphErrors* g_ch29 = new TGraphErrors();
    g_ch26->SetTitle("HV - width; HV [V]; width[ADC value]");
    g_ch29->SetTitle("HV - width; HV [V]; width[ADC value]");

    // fill points
    Double_t x_HV, y_width, x_HV_error, y_width_error;
    pair<Double_t, Double_t> tmp;
    // ch26
    for (Int_t i=0; i<run_numbers_ch26.size(); i++){
        tmp = determineMeanWidth(run_numbers_ch26[i]);
        x_HV          = HVs_ch26[run_numbers_ch26[i]];
        x_HV_error    = 0;
        y_width       = tmp.first;
        y_width_error = tmp.second;
        g_ch26->SetPoint(i, x_HV, y_width);
        g_ch26->SetPointError(i, x_HV_error, y_width_error);
    }
    // ch29
    for (Int_t i=0; i<run_numbers_ch29.size(); i++){
        tmp = determineMeanWidth(run_numbers_ch29[i]);
        x_HV          = HVs_ch29[run_numbers_ch29[i]];
        x_HV_error    = 0;
        y_width       = tmp.first;
        y_width_error = tmp.second;
        g_ch29->SetPoint(i, x_HV, y_width);
        g_ch29->SetPointError(i, x_HV_error, y_width_error);
    }

    // init fitting TF1
    TF1* f_ch26 = new TF1("f_ch26", "[0]*x + [1]", 0, 100);
    TF1* f_ch29 = new TF1("f_ch29", "[0]*x + [1]", 0, 100);
    
    // execute fitting
    g_ch26->Fit(f_ch26, "R");
    g_ch29->Fit(f_ch29, "R");

    // init TH2D in order to set range
    const Double_t X_MIN_CH26 = 0;
    const Double_t X_MAX_CH26 = 60;
    const Double_t Y_MIN_CH26 = f_ch26->GetParameter(1);
    const Double_t Y_MAX_CH26 = 60;
    const Double_t X_MIN_CH29 = 0;
    const Double_t X_MAX_CH29 = 60;
    const Double_t Y_MIN_CH29 = f_ch29->GetParameter(1);
    const Double_t Y_MAX_CH29 = 60;
    TH2D* axis_ch26 = new TH2D("axis_ch26", "HV - width;HV [V];width [ADC value]", 0, X_MIN_CH26, X_MAX_CH26, 0, Y_MIN_CH26, Y_MAX_CH26);
    TH2D* axis_ch29 = new TH2D("axis_ch29", "HV - width;HV [V];width [ADC value]", 0, X_MIN_CH29, X_MAX_CH29, 0, Y_MIN_CH29, Y_MAX_CH29);
    
    // draw and save
    // ch26
    TCanvas* c_ch26 = new TCanvas();
    if (is_show_zero == true){
        axis_ch26->Draw("AXIS");
        g_ch26->Draw("P SAME");
        c_ch26->Draw();
        c_ch26->SaveAs("img/week1/HV_Width_ch26_showzero.svg");
        c_ch26->SaveAs("img/week1/HV_Width_ch26_showzero.pdf");
    } else {
        g_ch26->Draw("AP");
        c_ch26->Draw();
        c_ch26->SaveAs("img/week1/HV_Width_ch26.svg");
        c_ch26->SaveAs("img/week1/HV_Width_ch26.pdf");
    }
    // ch29
    TCanvas* c_ch29 = new TCanvas();
    if (is_show_zero == true){
        axis_ch29->Draw("AXIS");
        g_ch29->Draw("P SAME");
        c_ch29->Draw();
        c_ch29->SaveAs("img/week1/HV_Width_ch29_showzero.svg");
        c_ch29->SaveAs("img/week1/HV_Width_ch29_showzero.pdf");
    } else {
        g_ch29->Draw("AP");
        c_ch29->Draw();
        c_ch29->SaveAs("img/week1/HV_Width_ch29.svg");
        c_ch29->SaveAs("img/week1/HV_Width_ch29.pdf");
    }
}