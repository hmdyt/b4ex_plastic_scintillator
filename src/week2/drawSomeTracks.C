void drawSomeTracks(Int_t ini_track, Int_t n_tracks){
    auto chain = getTChainByDistance("340");
    auto calb_const = getCalibrationConstants();

    for (Int_t i = ini_track; i < n_tracks; i++){
        drawOneTrack(chain, i, calb_const);
    }
}