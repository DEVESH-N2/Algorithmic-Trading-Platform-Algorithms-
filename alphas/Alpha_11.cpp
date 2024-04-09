#include "functions_extended.cpp"


std::vector<double> Alpha11(const std::vector<double>& vwap, const std::vector<double>& close, std::vector<double>& volume){
    int n=vwap.size();

    std::vector<double> vwapMinusClose(n);
    for (int i=0;i<n;i++){
        vwapMinusClose[i]=vwap[i]-close[i];
    }

    std::vector<std::pair<double, double>>rankTsMax=rank(ts_max(vwapMinusClose,3));
    std::vector<std::pair<double, double>>rankTsMin=rank(ts_min(vwapMinusClose,3));
    std::vector<std::pair<double, double>>rankDeltaVolume=rank(delta(volume,3));

    std::vector<double> alpha(n);
    for (int i=0;i<n;i++){
        alpha[i]=(rankTsMax[i].second+rankTsMin[i].second)*rankDeltaVolume[i].second;
    }

    return alpha;
}
