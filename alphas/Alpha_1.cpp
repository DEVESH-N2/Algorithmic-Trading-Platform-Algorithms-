#include "functions_extended.cpp"

std::vector<std::pair<double, double>> Alpha_1(std::vector<double> &returns, std::vector<double> &close)
{
    std::vector<double> std_dev_return = stddev(returns, 20);
    std::vector<double> PowArg(close.size());

    for(int i=0; i<close.size(); i++)
    {
        if(returns[i] < 0)
        {
            PowArg[i] = std_dev_return[i];
        }
        else
        {
            PowArg[i] = close[i];
        }
    }

    std::vector<double> MaxArg_Arg = SignedPower(PowArg, 2);
    std::vector<double> rankedvect = ts_argmax(MaxArg_Arg, 5);

    std::vector<std::pair<double,double>> OutPut = rank(rankedvect);

    return OutPut;
}