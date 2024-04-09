#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

std::vector<double> cov(std::vector<double> &x, std::vector<double> &y, int days);

std::vector<double> stddev(std::vector<double> &x, int d);

std::vector<double> cor(std::vector<double> &x, std::vector<double> &y, int days);

std::vector<std::pair<double, double>> rank(std::vector<double> &values);

std::vector<double> delta(std::vector<double> &val, int days);