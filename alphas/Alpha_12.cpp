#include "functions_extended.cpp"


std::vector<double> Alpha12(std::vector<double>& close, std::vector<double>& volume){
    int n=close.size();

    std::vector<double> deltaVolume=delta(volume,1);
    std::vector<double> deltaClose=delta(close,1);

    std::vector<double> alpha(n-1); 
    for (int i=0;i<n-1;i++){
        alpha[i]=(deltaVolume[i]>0?1.0:(deltaVolume[i]<0?-1.0:0.0))*(-1.0*deltaClose[i]);
    }

    return alpha;
}


