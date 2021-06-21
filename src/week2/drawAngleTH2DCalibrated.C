void drawAngleTH2DCalibrated(){
    // init TH2D
    const Double_t LAYER_NUM = 10;
    const Double_t DELEY_MAX = 10;
    TH2D* hist = new TH2D(
        "angle", ";distance [mm]; layer",
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
    
    // prepare calibration constant
    map<Int_t, pair<Double_t, Double_t>> calb_const = {
        { 1, drawTimeDistGraph({"0" , "1",  "2",  "3"})  },
        { 2, drawTimeDistGraph({"4" , "5",  "6",  "7"})  },
        { 3, drawTimeDistGraph({"8" , "9",  "10", "11"}) },
        { 4, drawTimeDistGraph({"12", "13", "14", "15"}) },
        { 5, drawTimeDistGraph({"16", "17", "18", "19"}) },
        { 6, drawTimeDistGraph({"20", "21", "22", "23"}) },
        { 7, drawTimeDistGraph({"24", "25", "26", "27"}) },
        { 8, drawTimeDistGraph({"28", "29", "30", "31"}) },
    };
    auto f_calb = [](Double_t x, Double_t a, Double_t b){return a * x + b;};

    // arrange Xaxis
    hist->GetXaxis()->SetLimits(
        f_calb(- DELEY_MAX, calb_const[8].first, calb_const[1].second),
        f_calb(+ DELEY_MAX, calb_const[8].first, calb_const[1].second)
    );
    cout << calb_const[8].first << " " << calb_const[8].second << endl;

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
                hist->Fill(
                    f_calb(time_diff, calb_const[current_leyer].first, calb_const[current_leyer].second),
                    current_leyer
                );
            }
        }
    }

    // save
    auto c = new TCanvas();
    hist->Draw("box");
    c->SaveAs("img/week2/AngleTH2D_calibrated.svg");
    c->SaveAs("img/week2/AngleTH2D_calibrated.pdf");
}