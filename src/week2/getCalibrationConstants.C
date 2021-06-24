map<Int_t, pair<Double_t, Double_t>> getCalibrationConstants(){
    return {
        { 1, drawTimeDistGraph({"0" , "1",  "2",  "3"})  },
        { 2, drawTimeDistGraph({"4" , "5",  "6",  "7"})  },
        { 3, drawTimeDistGraph({"8" , "9",  "10", "11"}) },
        { 4, drawTimeDistGraph({"12", "13", "14", "15"}) },
        { 5, drawTimeDistGraph({"16", "17", "18", "19"}) },
        { 6, drawTimeDistGraph({"20", "21", "22", "23"}) },
        { 7, drawTimeDistGraph({"24", "25", "26", "27"}) },
        { 8, drawTimeDistGraph({"28", "29", "30", "31"}) },
    };
}