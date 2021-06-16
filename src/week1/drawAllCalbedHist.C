void drawAllCalbedHist(){
    vector<TString> run = {
        "led3018.root",
        "led3019.root",
        "led3020.root",
        "led3021.root"
    };
    vector<TString> ch = {
        "26",
        "29"
    };

    for (Int_t i=0; i<run.size(); i++){
        for (Int_t j=0; j<ch.size(); j++){
            drawCalbedHist(run[i], ch[j]);
        }
    }
}