#include "functions_extended.cpp"

std::vector<double> Alpha4(std::vector<double> &low)
{
    std::vector<std::pair<double, double>> allranklow = rank(low);

    std::vector<double> lowrank(allranklow.size());

    for(int i=0; i<lowrank.size(); i++)
    {
        lowrank[i] = allranklow[i].second;
    }

    std::vector<double> OutPut = ts_rank(lowrank, 9);

    for(int i=0; i<OutPut.size(); i++)
    {
        OutPut[i] = OutPut[i]*-1;
    }

    return OutPut;
}