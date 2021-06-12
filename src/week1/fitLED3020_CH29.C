void fitLED3020_CH29(){
    // init file propaties
    const TString FILENAME = "led3020.root";
    const TString CHANNEL = "29";
    const Double_t XMIN = 800;
    const Double_t XMAX = 2200;

    // fetch hist
    TH1D* hist = getHistMPPC(FILENAME, CHANNEL);

    // arrange x range
    hist->GetXaxis()->SetRangeUser(XMIN, XMAX);

    // arrange hist title
    hist->SetTitle(FILENAME + " " + CHANNEL);

    // draw and save
    auto c = new TCanvas();
    hist->Draw();
    c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + ".pdf");
    c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + ".svg");
}