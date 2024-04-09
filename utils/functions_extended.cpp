#include "functions_extended.h"

std::vector<double> cov(const std::vector<double> &x, const std::vector<double> &y, int days)
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

std::vector<double> stddev(const std::vector<double> &x, int d)
{
    int n = x.size();
    std::vector<double> sigma = cov(x, x, d);
    for (int i = d; i < n; i++)
    {
        sigma[i] = sqrtl(sigma[i]);
    }
    return sigma;
}

std::vector<double> cor(const std::vector<double> &x, const std::vector<double> &y, int days)
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

std::vector<std::pair<double, double>> rank(const std::vector<double> &values)
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

std::vector<double> decay_linear(const std::vector<double>& data,int d){
    std::vector<double> decayed_linear_values;
    double weighted_sum,weight,sum_of_weights,moving_average;

    for(int i=0;i<=data.size()-d;i++){
        weighted_sum=0,weight=d;
        for(int j=i+d-1;j>=i;j--){
            weighted_sum+=data[j]*weight;
            weight--;
        }

        sum_of_weights=(d*(d+1))/2;  // Sum of linearly decreasing weights
        moving_average=weighted_sum/sum_of_weights;
        decayed_linear_values.push_back(moving_average);
    }
    return decayed_linear_values;
}


/*indneutralize(x, g) = x cross-sectionally neutralized against groups g (subindustries, industries,
sectors, etc.), i.e., x is cross-sectionally demeaned within each group g*/

/*It divides the data points in x into different groups based on the group assignments in vector 
g. It creates a mapping of group identifiers to the data points within each group.For each group, 
it calculates the mean of the data points within that group. This provides the "group mean" for 
each group.It then goes through each data point in x, identifies its associated group based on the 
corresponding value in g, and subtracts the group mean from that data point. This subtraction is 
the "demeaning" process.The result is a new vector, denoted as demeaned_data, where each data point
has been neutralized with respect to its group by removing the group-level mean.The values in this 
vector represent how much each data point deviates from the typical value within its group.*/


std::vector<double> indneutralize(const std::vector<double>& x, const std::vector<int>& g){
    //g contains the id(integer) of each group 
    int n=x.size();  // Number of data points
    std::unordered_map<int, std::vector<double>> group_data;
    
    // Collect data points within each group
    for(int i=0;i<n;i++){
        group_data[g[i]].push_back(x[i]);
    }

    // Calculate group means and demean each data point within its group
    std::vector<double> demeaned_data;
    int group_id;
    double group_mean,demeaned_value;
    for(int i=0;i<n;i++){
        group_id=g[i];
        group_mean=0;

        for(double value:group_data[group_id]){
            group_mean+=value;
        }
        group_mean/=group_data[group_id].size();

        demeaned_value=x[i]-group_mean;
        demeaned_data.push_back(demeaned_value);
    }

    return demeaned_data;
}


std::vector<double> ts_argmax(const std::vector<double>& x, int d){
    int n=x.size();  // Number of data points
    std::vector<double> max_days;

    int start_index,end_index,max_day;
    double max_val;
    for(int i=0;i<n;i++){
        start_index=std::max(0,i-d+1);  // Start index for the rolling window
        end_index=i;  // End index is the current day

        // Finding maximum value day within the rolling window
        max_val=x[start_index];
        max_day=start_index+1;
        for(int j=start_index+1;j<=end_index;j++){
            if(max_val<x[j]){
                max_day=j+1;
            }
            max_val=std::max(max_val,x[j]);
        }
        double daynew = max_day*1.0;
        max_days.push_back(daynew);
    }

    return max_days;
}


std::vector<double> ts_argmin(const std::vector<double>& x, int d){
    int n=x.size();  // Number of data points
    std::vector<double> min_days;

    int start_index,end_index,min_day;
    double min_val;
    for(int i=0;i<n;i++){
        start_index=std::max(0,i-d+1);  // Start index for the rolling window
        end_index=i;  // End index is the current day

        // Finding minimum value day within the rolling window
        min_val=x[start_index];
        min_day=start_index+1;
        for(int j=start_index+1;j<=end_index;j++){
            if(min_val<x[j]){
                min_day=j+1;
            }
            min_val=std::min(min_val,x[j]);
        }
        min_days.push_back((min_day*1.0));
    }

    return min_days;
}

std::vector<double> ts_max(const std::vector<double>& x, int d){
    int n=x.size();  // Number of data points
    std::vector<double> max_values;

    int start_index,end_index;
    double max_val;
    for(int i=0;i<n;i++){
        start_index=std::max(0,i-d+1);  // Start index for the rolling window
        end_index=i;  // End index is the current day

        // Finding maximum value within the rolling window
        max_val=x[start_index];
        for(int j=start_index+1;j<=end_index;j++){
            max_val=std::max(max_val,x[j]);
        }

        max_values.push_back(max_val);
    }

    return max_values;
}

std::vector<double> ts_min(const std::vector<double>& x, int d){
    int n=x.size();  // Number of data points
    std::vector<double> min_values;

    int start_index,end_index;
    double min_val;
    for(int i=0;i<n;i++){
        start_index=std::max(0,i-d+1);  // Start index for the rolling window
        end_index=i;  // End index is the current day

        // Finding minimum value within the rolling window
        min_val=x[start_index];
        for(int j=start_index+1;j<=end_index;j++){
            min_val=std::min(min_val,x[j]);
        }

        min_values.push_back(min_val);
    }

    return min_values;
}

std::vector<double> ts_rank(const std::vector<double>& data, int d){
    int n=data.size();  // Number of data points
    std::vector<double> rank_values;

    int start_index,end_index,rank;
    double current_value;

    for(int i=0;i<n;i++) {
        start_index=std::max(0,i-d+1);  // Start index for the rolling window
        end_index=i;  // End index is the current day

        // Extract and sort the data within the rolling window
        std::vector<double> window_data(data.begin()+start_index,data.begin()+end_index+1);
        std::sort(window_data.begin(),window_data.end());

        // Finding the rank of the current day's value within the sorted window
        current_value=data[i];
        rank=1;
        for(double value:window_data){
            if(value<current_value){
                rank++;
            }
            else{
                break;
            }
        }

        rank_values.push_back(static_cast<double>(rank)/(end_index-start_index+1)); // Normalize rank
    }

    return rank_values;
}

std::vector<double> SignedPower(const std::vector<double> &data, int a)
{
    std::vector<double> PowerReturn(data.size());
    
    for(int i=0; i<data.size(); i++)
    {
        PowerReturn[i] = 1;
        for(int j=0; j<a; j++)
        {
            PowerReturn[i] = PowerReturn[i] * data[i];
        }
    }

    return PowerReturn;
}

