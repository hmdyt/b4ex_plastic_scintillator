void drawAngleTH2D(){
    // init TH2D
    const Double_t LAYER_NUM = 10;
    const Double_t DELEY_MAX = 10;
    TH2D* hist = new TH2D(
        "angle", ";time lag [ns]; layer",
        DELEY_MAX * 2,
        - DELEY_MAX,
        + DELEY_MAX,
        LAYER_NUM,
        0 - 0.5,
        LAYER_NUM - 0.5
    );

    map<Int_t, Double_t> channel_to_layer = {
        {0,  1}, {1,  1}, {2,  1}, {3,  1},
        {4,  2}, {5,  2}, {6,  2}, {7,  2},
        {8,  3}, {9,  3}, {10, 3}, {11, 3},
        {12, 4}, {13, 4}, {14, 4}, {15, 4},
        {16, 5}, {17, 5}, {18, 5}, {19, 5},
        {20, 6}, {21, 6}, {22, 6}, {23, 6},
        {24, 7}, {25, 7}, {26, 7}, {27, 7},
        {28, 8}, {29, 8}, {30, 8}, {31, 8},
    };

    // init for calling existing branch
    TChain* chain = getTChainByDistance("340");
    Int_t VadcHigh[64];
    Int_t VtdcLeading[64];
    TBranch* b_VadcHigh;
    TBranch* b_VtdcLeading;
    chain->SetBranchAddress("VadcHigh", VadcHigh, &b_VadcHigh);
    chain->SetBranchAddress("VtdcLeading", VtdcLeading, &b_VtdcLeading);

    // fill
    Double_t current_leyer, time_diff;
    Int_t ch_high, ch_low;
    for (Int_t i = 0; i < chain->GetEntries(); i++){
        chain->GetEntry(i);
        for (Int_t j = 0; j < 32; j++){
            ch_low  = j;
            ch_high = (Int_t) stoi((string) getInverseChannel((TString) to_string((int) ch_low)));
            current_leyer = channel_to_layer[ch_low];
            time_diff     = VtdcLeading[ch_low] - VtdcLeading[ch_high];
            if (VadcHigh[ch_low] > 1000 && VadcHigh[ch_high] > 1000){
                hist->Fill(time_diff, current_leyer);
            }
        }
    }

    // save
    auto c = new TCanvas();
    hist->Draw("box");
    c->SaveAs("img/week2/AngleTH2D.svg");
    c->SaveAs("img/week2/AngleTH2D.pdf");
}