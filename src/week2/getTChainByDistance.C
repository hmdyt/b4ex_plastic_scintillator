TChain* getTChainByDistance(TString target_distance = "340"){
    const TString INFO_TEXT_PATH = "data/week2/info.txt";

    // fetch target file name
    vector<TString> target_files;
    // init for while loop
    TString number, HV_MPPC, HV_trig, distance, events;
    ifstream ifs(INFO_TEXT_PATH);
    while (ifs >> number >> HV_MPPC >> HV_trig >> distance >> events){
        if (distance != target_distance) continue; 
        target_files.push_back(number + ".root");
        cout << number << endl;
    }

    TChain* chain = new TChain("tree");
    for (Int_t i=0; i<target_files.size(); i++){
        chain->Add("data/week2/" + target_files[i]);
    }

    return chain;
}