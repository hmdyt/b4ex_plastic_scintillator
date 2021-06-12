void fitLED3018_CH26(){
    // init file propaties
    const TString FILENAME = "led3018.root";
    const TString CHANNEL = "26";
    const Double_t XMIN = 800;
    const Double_t XMAX = 1350;

    // init fitting propaties
    // initial const, mean sigma are FIT_HEIGHT ,FIT_MID_MIN~MAX, FIT_WIDTH
    const Int_t GAUSNUM = 12;
    const Double_t FIT_HEIGHT = 500;
    const Double_t FIT_MID_MIN = 840;
    const Double_t FIT_MID_MAX = 1250;
    const Double_t FIT_WIDTH = (FIT_MID_MAX - FIT_MID_MIN) / (GAUSNUM - 1);
    const Double_t FIT_RANGE_MIN = 800;
    const Double_t FIT_RANGE_MAX = 1260;
    const TString MULTIGAUS = getMultiGaus(GAUSNUM);

    // fetch and configurate hist
    TH1D* hist = getHistMPPC(FILENAME, CHANNEL);
    hist->GetXaxis()->SetRangeUser(XMIN, XMAX);
    hist->SetTitle(FILENAME + " " + CHANNEL);

    // init TF1
    TF1* f = new TF1("f", MULTIGAUS, FIT_RANGE_MIN, FIT_RANGE_MAX);

    // set parnames and initial params
    for (Int_t i=0; i<GAUSNUM; i++) {
        f->SetParName(3*i + 0, (TString)to_string(i) + (TString)"th Const");
        f->SetParName(3*i + 1, (TString)to_string(i) + (TString)"th Mean"); 
        f->SetParName(3*i + 2, (TString)to_string(i) + (TString)"th Sigma"); 
        f->SetParameter(3*i + 0, FIT_HEIGHT);
        f->SetParameter(3*i + 1, FIT_MID_MIN + FIT_WIDTH * i);
        f->SetParameter(3*i + 2, FIT_WIDTH);
        f->SetParLimits(3*i + 0, 0, 1000);
        f->SetParLimits(3*i + 1, FIT_RANGE_MIN, FIT_RANGE_MAX);
        f->SetParLimits(3*i + 2, 0, 100);
     }

    // execute fitting
    hist->Fit(f, "R");

    // draw and save
    auto c = new TCanvas();
    hist->Draw();
    c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + ".pdf");
    c->SaveAs("img/week1/" + FILENAME + "CH" + CHANNEL + ".svg");
}