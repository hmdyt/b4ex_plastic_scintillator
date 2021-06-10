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
    loadMacro("src/week1/fitLED3005_CH26.C");
    loadMacro("src/week1/fitLED3006_CH26.C");
    loadMacro("src/week1/fitLED3007_CH26.C");
    loadMacro("src/week1/fitLED3005_CH29.C");
    loadMacro("src/week1/fitLED3006_CH29.C");
    loadMacro("src/week1/fitLED3007_CH29.C");

}