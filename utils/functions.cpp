#include "functions.h"

std::vector<double> cov(std::vector<double> &x, std::vector<double> &y, int days)
{
    int n = x.size();
    std::vector<double> xy(n);
    for (int i = 0; i < n; i++)
    {
        xy[i] = x[i] * y[i];
    }
    std::vector<double> covar(n, 0.0);
    double sumxy = 0.0, sumx = 0.0, sumy = 0.0;
    for (int i = 0; i < days; i++)
    {
        sumxy += xy[i];
        sumx += x[i];
        sumy += y[i];
    }
    int d = days - 1; // unbiased estimator
    if (d == 0)
        d++;
    for (int i = days; i < n; i++)
    {
        covar[i] = sumxy / (d * 1.0) - (sumx / (d * 1.0)) * (sumy / (d * 1.0));
        sumxy += xy[i] - xy[i - days];
        sumx += x[i] - x[i - days];
        sumy += y[i] - y[i - days];
    }
    return covar;
}

std::vector<double> stddev(std::vector<double> &x, int d)
{
    int n = x.size();
    std::vector<double> sigma = cov(x, x, d);
    for (int i = d; i < n; i++)
    {
        sigma[i] = sqrtl(sigma[i]);
    }
    return sigma;
}

std::vector<double> cor(std::vector<double> &x, std::vector<double> &y, int days)
{
    int n = x.size();
    std::vector<double> correl = cov(x, y, days);
    std::vector<double> sigmax = stddev(x, days);
    std::vector<double> sigmay = stddev(y, days);
    for (int i = days; i < n; i++)
    {
        if (sigmax[i] * sigmay[i] != 0.0)
            correl[i] = (correl[i]) / (sigmax[i] * sigmay[i]);
    }
    return correl;
}

std::vector<std::pair<double, double>> rank(std::vector<double> &values)
{
    int n = values.size();
    std::vector<double> sorted = values; // values of different securites at a fixed date
    std::sort(sorted.begin(), sorted.end());
    std::vector<std::pair<double, double>> ranks(n);
    for (int i = 0; i < n; i++)
    {
        ranks[i].first = values[i];
        ranks[i].second = n + 1 - ((lower_bound(sorted.begin(), sorted.end(), values[i]) - sorted.begin() + 1) * 1.0 
                                 + (upper_bound(sorted.begin(), sorted.end(), values[i]) - sorted.begin()) * 1.0) / 2.0;
    }
    return ranks;
}

std::vector<double> delta(std::vector<double> &val, int days)
{
    int n = val.size();
    std::vector<double> del(n, 0.0);
    for (int i = days; i < n; i++)
    {
        del[i] = val[i] - val[i - days];
    }
    return del;
}