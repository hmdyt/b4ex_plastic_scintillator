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

void rootlogon(){
    // message
    cout << "executed rootlogon" << endl;

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
}
