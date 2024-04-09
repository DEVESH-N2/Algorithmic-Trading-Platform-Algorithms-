#include "functions.cpp"

std::vector<double> a6(std::vector<double> &open, std::vector<double> &volume, int days = 10)
{
    int n = open.size();
    std::vector<double> alpha(n, 0.0);
    std::vector<double> correl = cor(open, volume, days);
    for (int i = days; i < n; i++)
    {
        alpha[i] = (-1.0) * (correl[i]);
    }
}