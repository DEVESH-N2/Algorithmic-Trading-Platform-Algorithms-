#include "functions_extended.cpp"

std::vector<double> Alpha3(const std::vector<double> &volume, const std::vector<double> &open)
{
    std::vector<std::pair<double, double>> allrankopen = rank(open);
    std::vector<std::pair<double, double>> allrankvol = rank(volume);

    std::vector<double> openrank(open.size());

    for(int i=0; i<open.size(); i++)
    {
        openrank[i] = allrankopen[i].second;
    }

    std::vector<double> volrank(volume.size());

    for(int i=0; i<volume.size(); i++)
    {
        volrank[i] = allrankvol[i].second;
    }    

   std::vector<double> OutPut = cor(openrank, volrank, 10);

   for(int i=0; i<OutPut.size(); i++)
   {
        OutPut[i] = -1*OutPut[i];
   }

    return OutPut;

}