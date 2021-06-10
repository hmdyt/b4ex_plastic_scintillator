void fitLED3006_CH26(){
    // init file propaties
    const TString FILENAME = "led3006.root";
    const TString CHANNEL = "26";
    const Double_t XMIN = 1900;
    const Double_t XMAX = 3550;

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