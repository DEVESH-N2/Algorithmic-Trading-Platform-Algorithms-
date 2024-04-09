#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include<unordered_map>

std::vector<double> cov(const std::vector<double> &x, const std::vector<double> &y, int days);

std::vector<double> stddev(const std::vector<double> &x, int d);

std::vector<double> cor(const std::vector<double> &x, const std::vector<double> &y, int days);

std::vector<std::pair<double, double>> rank(const std::vector<double> &values);

std::vector<double> delta(std::vector<double> &val, int days);

std::vector<double> decay_linear(const std::vector<double>& data,int d);

std::vector<double> indneutralize(const std::vector<double>& x, const std::vector<int>& g);

std::vector<double> ts_argmax(const std::vector<double> &x, int d);

std::vector<double> ts_argmin(const std::vector<double>& x, int d);

std::vector<double> ts_max(const std::vector<double>& x, int d);

std::vector<double> ts_min(const std::vector<double>& x, int d);

std::vector<double> ts_rank(const std::vector<double>& data, int d);

std::vector<double> SignedPower(std::vector<double> &data, int a);