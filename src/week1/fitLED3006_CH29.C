void fitLED3006_CH29(){
    // init file propaties
    const TString FILENAME = "led3006.root";
    const TString CHANNEL = "29";
    const Double_t XMIN = 2100;
    const Double_t XMAX = 3550;

    // fetch hist
    TH1D* hist = getHistMPPC(FILENAME, CHANNEL);

	//set title
	hist->SetTitle("led3006_ch29");

    // arrange x range
    hist->GetXaxis()->SetRangeUser(XMIN, XMAX);

    // draw and save
    auto c = new TCanvas();
    hist->Draw();
    c->SaveAs("img/week1/" + FILENAME + ".pdf");
}
