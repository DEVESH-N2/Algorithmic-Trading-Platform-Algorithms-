#include <iostream>
#include "functions.cpp"

int main()
{
    int n;
    std::cin >> n;
    std::vector<double> high(n), low(n), open(n), close(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> open[i] >> close[i] >> high[i] >> low[i];
    }
    std::vector<double> returns(n), volume(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> returns[i] >> volume[i];
    }
}