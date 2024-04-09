#include "functions.cpp"

std::vector<double> a53(std::vector<double> &close, std::vector<double> &low, std::vector<double> &high, int days = 9)
{
    int n = close.size();
    std::vector<double> alpha(n);
    for (int i = 0; i < n; i++)
    {
        alpha[i] = (2 * close[i] - high[i] - low[i]) / (close[i] - low[i]);
        alpha[i] *= (-1);
    }
    alpha = delta(alpha, days);
    return alpha;
}