#include "functions.cpp"

std::vector<std::vector<double>> a16(std::vector<std::vector<double>> &high, std::vector<std::vector<double>> &volume, int days = 5)
{
    // ith row contains value of all securities at ith day
    // jth column contains values of jth security on all days
    int n = high.size();                                           // number of days
    int s = high[0].size();                                        // number of securities
    std::vector<std::vector<double>> highranks(n), volumeranks(n); // calculated on a fixed day
    for (int i = 0; i < n; i++)
    {
        std::vector<std::pair<double, double>> temphigh = rank(high[i]);
        for (int j = 0; j < s; j++)
        {
            highranks[i].push_back(temphigh[j].second);
        }
        std::vector<std::pair<double, double>> tempvol = rank(volume[i]);
        for (int j = 0; j < s; j++)
        {
            highranks[i].push_back(tempvol[j].second);
        }
    }
    std::vector<std::vector<double>> covar(s); // calculated on a fixed security
    for (int i = 0; i < s; i++)
    {
        std::vector<double> securityhigh(n), securityvolume(n);
        for (int j = 0; j < n; j++)
        {
            securityhigh[j] = highranks[j][i];
            securityvolume[j] = volumeranks[j][i];
        }
        //Store in column order
        covar[i] = cov(securityhigh, securityvolume, days);
    }
    std::vector<std::vector<double>> covarranks(n); // calculated  on a fixed day
    for (int i = 0; i < n; i++)
    {
        std::vector<std::pair<double, double>> tempcovarranks = rank(covar[i]);
        for (int j = 0; j < s; j++)
        {
            covarranks[i].push_back((-1.0) * tempcovarranks[j].second);
        }
    }
    return covarranks;
}