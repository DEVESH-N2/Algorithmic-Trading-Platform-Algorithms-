#include "functions_extended.cpp"


std::vector<double> Alpha13(const std::vector<double>& close, const std::vector<double>& volume){
    int n=close.size();

    std::vector<std::pair<double, double>> rankClose=rank(close);
    std::vector<std::pair<double, double>> rankVolume=rank(volume);

    std::vector<double> rankCloseSecond, rankVolumeSecond;
    for(const auto& pair:rankClose){
        rankCloseSecond.push_back(pair.second);
    }
    for(const auto& pair:rankVolume){
        rankVolumeSecond.push_back(pair.second);
    }

    std::vector<std::pair<double,double>> rankCovar=rank(cov(rankCloseSecond,rankVolumeSecond,5));

    std::vector<double> alpha(n,0.0);
    for(int i=0;i<n;i++){
        alpha[i]=-1.0*rankCovar[i].second;
    }

    return alpha;
}


