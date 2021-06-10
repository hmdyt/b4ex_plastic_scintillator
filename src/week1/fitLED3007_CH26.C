void fitLED3007_CH26(){
    // init file propaties
    const TString FILENAME = "led3007.root";
    const TString CHANNEL = "26";
    const Double_t XMIN = 1000;
    const Double_t XMAX = 2100;

    // fetch hist
    TH1D* hist = getHistMPPC(FILENAME, CHANNEL);

    // arrange x range
    hist->GetXaxis()->SetRangeUser(XMIN, XMAX);

    // arrange hist title
    hist->SetTitle(FILENAME + " " + CHANNEL);
    
    // draw and save
    auto c = new TCanvas();
    hist->Draw();
    c->SaveAs("img/week1/" + FILENAME + ".pdf");
}