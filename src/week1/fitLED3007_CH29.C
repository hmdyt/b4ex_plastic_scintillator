void fitLED3007_CH29(){
    // init file propaties
    const TString FILENAME = "led3007.root";
    const TString CHANNEL = "29";
    const Double_t XMIN = 1100;
    const Double_t XMAX = 2000;

    // fetch hist
    TH1D* hist = getHistMPPC(FILENAME, CHANNEL);

	//set title
	hist->SetTitle("led3007_ch29");

    // arrange x range
    hist->GetXaxis()->SetRangeUser(XMIN, XMAX);

    // draw and save
    auto c = new TCanvas();
    hist->Draw();
    c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + ".pdf");
    c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + ".svg");
}
