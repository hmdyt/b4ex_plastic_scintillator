void fitLED3005_CH26(){
    // init file propaties
    const TString FILENAME = "led3005.root";
    const TString CHANNEL = "26";
    const Double_t XMIN = 1400;
    const Double_t XMAX = 3400;

    // fetch hist
    TH1D* hist = getHistMPPC(FILENAME, CHANNEL);

    // arrange x range
    hist->GetXaxis()->SetRangeUser(XMIN, XMAX);

    // draw and save
    auto c = new TCanvas();
    hist->Draw();
    c->SaveAs("img/week1/" + FILENAME + ".pdf");
}