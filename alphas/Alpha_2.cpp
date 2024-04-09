#include "functions_extended.cpp"

std::vector<double> log_vect(const std::vector<double> &v)
{
    std::vector<double> Output(v.size());
    for(int i=0; i<v.size(); i++)
    {
        Output[i] = std::log(v[i]);
    }
    return Output;
}

std::vector<double> Fn(const std::vector<double> &close, const std::vector<double> &open)
{
    std::vector<double> Output(close.size());
    
    for(int i=0; i<close.size(); i++)
    {
        Output[i] = (close[i]-open[i])/open[i];
    }
    return Output;
}

std::vector<double> Alpha2(const std::vector<double> &volume, const std::vector<double> &close, const std::vector<double> &open)
{
    std::vector<double> VolLog = log_vect(volume);
    std::vector<double> Delta_LogVol = delta(VolLog, 2);
    std::vector<double> Fn2 = Fn(close, open);
    std::vector<std::pair<double, double>> rank1all = rank(Delta_LogVol);
    std::vector<std::pair<double, double>> rank2all = rank(Fn2);

    std::vector<double> rank1(rank1all.size());
    
    for(int i=0; i<rank1.size(); i++)
    {
        rank1[i] = rank1all[i].second;
    }

    std::vector<double> rank2(rank2all.size());
    
    for(int i=0; i<rank2all.size(); i++)
    {
        rank2[i] = rank2all[i].second;
    }
    
    std::vector<double> Alpha_OUT = cor(rank1, rank2, 6);

    for(int i=0; i<Alpha_OUT.size(); i++)
    {
        Alpha_OUT[i] = Alpha_OUT[i] * (-1);
    }

   return Alpha_OUT;
}