void loadMacro(const TString macro_name){
    // load
    const int ret = gROOT->LoadMacro(macro_name);

    if (ret == 0){
        // load success
        cout << "loaded " + macro_name << endl;
    } else {
        //load failed
        cout << "faild " + macro_name << endl;
        exit(1);
    }
}

void SetMyStyle(bool is_show_fitted_values = true){
    if (is_show_fitted_values){
        gStyle->SetOptStat("e");
        gStyle->SetOptFit(1111);
    } else {
        gStyle->SetOptStat("e");
        gStyle->SetOptFit(1100);
    }
}

void SetStatNull(){
    gStyle->SetOptStat(000000000);
    gStyle->SetOptFit(000000000);
}

void rootlogon(){
    // message
    cout << "executed rootlogon" << endl;

    // style
    SetMyStyle(true);

    // week1
    loadMacro("src/week1/getHistMPPC.C");
    loadMacro("src/week1/getMultiGaus.C");
    loadMacro("src/week1/searchPeak.C");
    loadMacro("src/week1/getPedestalMean.C");
    loadMacro("src/week1/fitLED3018_CH26.C");
    loadMacro("src/week1/fitLED3018_CH29.C");
    loadMacro("src/week1/fitLED3019_CH26.C");
    loadMacro("src/week1/fitLED3019_CH29.C");
    loadMacro("src/week1/fitLED3020_CH26.C");
    loadMacro("src/week1/fitLED3020_CH29.C");
    loadMacro("src/week1/fitLED3021_CH26.C");
    loadMacro("src/week1/fitLED3021_CH29.C");
    loadMacro("src/week1/determineMeanWidth.C");
    loadMacro("src/week1/drawVoltWidthGraph.C");
    loadMacro("src/week1/drawCalbedHist.C");
	// week2
    loadMacro("src/week2/getInverseChannel.C");
    loadMacro("src/week2/getChannelCombinedHist.C");
    loadMacro("src/week2/searchSiglePeak.C");
    loadMacro("src/week2/fitDelayHist.C");
    loadMacro("src/week2/drawTimeDistGraph.C");
    loadMacro("src/week2/drawNonCombinedTimeDistGraph.C");
    // week2 angule
    loadMacro("src/week2/getTChainByDistance.C");
    // week2 track
    loadMacro("src/week2/getCalibrationConstants.C");
    loadMacro("src/week2/drawOneTrack.C");
    loadMacro("src/week2/drawSomeTracks.C");
}
