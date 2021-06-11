void fitLED3005_CH26(){
    // init file propaties
    const TString FILENAME = "led3005.root";
    const TString CHANNEL = "26";
    const Double_t XMIN = 1400;
    const Double_t XMAX = 3300;

    // init fitting propaties
    // initial const, mean sigma are FITHEIGHT ,FITMIDMIN~MAX, FITWIDTH
    const Double_t FITHEIGHT = 20;
    const Double_t FITMIDMIN = 1550;
    const Double_t FITMIDMAX = 2900;
    const Double_t FITWIDTH = 50;
    const Double_t FITRANGEMAX = FITMIDMIN - FITWIDTH/2;
    const Double_t FITRANGEMIN = FITMIDMAX + FITWIDTH/2;
    const Int_t GAUSNUM = (Int_t) (FITMIDMAX - FITMIDMIN) / FITWIDTH;
    const TString MULTIGAUS = getMultiGaus(GAUSNUM);

    // fetch hist
    TH1D* hist = getHistMPPC(FILENAME, CHANNEL);

    // arrange x range
    hist->GetXaxis()->SetRangeUser(XMIN, XMAX);

    // arrange hist title
    hist->SetTitle(FILENAME + " " + CHANNEL);

    // init TF1
    TF1* f = new TF1("f", MULTIGAUS, FITRANGEMIN, FITRANGEMAX);

    // set parnames ane initial params
    for (Int_t i=0; i<GAUSNUM; i++) {
        f->SetParName(3*i + 0, (TString)to_string(i) + (TString)"th Const");
        f->SetParName(3*i + 1, (TString)to_string(i) + (TString)"th Mean"); 
        f->SetParName(3*i + 2, (TString)to_string(i) + (TString)"th Sigma"); 
        f->SetParameter(3*i + 0, FITHEIGHT);
        f->SetParameter(3*i + 1, FITMIDMIN + FITWIDTH * i);
        f->SetParameter(3*i + 2, FITWIDTH);
     }
    
    // execute fitting
    hist->Fit(f, "R");

    // draw and save
    auto c = new TCanvas();
    hist->Draw();
    c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + ".pdf");
    c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + ".svg");
}