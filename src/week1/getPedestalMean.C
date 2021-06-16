Double_t getPedestalMean(TString file_name = "led3022.root", TString channel = "26"){
    // canvas
    TCanvas* c = new TCanvas();

    // fetch hist and configurate
    auto hist = getHistMPPC(file_name, channel);
    hist->SetTitle(file_name + " " + channel + "ch Pedestal;ADC value;Events");

    // init tf1 and fit
    TF1* f = new TF1("f", "gaus", 0, 4096);
    f->SetParName(0, "Const");
    f->SetParName(1, "Mean");
    f->SetParName(2, "Sigma");
    hist->Fit(f, "R");

    // set histgram range
    const Double_t f_mean = f->GetParameter(1);
    const Double_t f_sigma = f->GetParameter(2);
    const Double_t x_min = f_mean - 7 * f_sigma;
    const Double_t x_max = f_mean + 7 * f_sigma;
    hist->GetXaxis()->SetRangeUser(x_min, x_max);

    // draw and save
    c->Draw();
    c->SaveAs("img/week1/" + file_name + channel + "pedestal.svg");
    c->SaveAs("img/week1/" + file_name + channel + "pedestal.pdf");

    return f->GetParameter(1);
}