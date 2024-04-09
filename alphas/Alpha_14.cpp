#include "functions_extended.cpp"


std::vector<double> Alpha14(std::vector<double>& returns, const std::vector<double>& open, const std::vector<double>& volume){
    int n=open.size();

    std::vector<double> deltaReturns=delta(returns,3);

    std::vector<std::pair<double, double>> rankDeltaReturns=rank(deltaReturns);

    std::vector<double> correlation=cor(open,volume,10);

    std::vector<double> alpha(n,0.0);
    for (int i=0;i<n;i++) {
        alpha[i]=-1.0*rankDeltaReturns[i].second*correlation[i];
    }

    return alpha;
}

