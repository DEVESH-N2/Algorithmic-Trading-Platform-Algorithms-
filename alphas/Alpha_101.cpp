#include "functions.cpp"

std::vector<double> a101(std::vector<double> &high, std::vector<double> &low, std::vector<double> &open, std::vector<double> &close)
{
    int n = high.size();
    std::vector<double> alpha(n);
    for (int i = 0; i < n; i++)
    {
        alpha[i] = (close[i] - open[i]) / (high[i] - low[i] + 0.001);
    }
    return alpha;
}