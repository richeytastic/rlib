#include "LinearRegressor.h"
using rlib::LinearRegressor;
#include <cmath>
#include <iostream>
using std::cerr;
using std::endl;


LinearRegressor::LinearRegressor( const vector<float> &vals)
    : M( vals.size()), sumy(0.0), sumx(0.0), dotxy(0.0), sumxsq(0.0)
{
    for ( size_t i = 0; i < M; ++i)
    {
        y.push_back(vals[i]);
        inity.push_back(y[i]);  // Retain copy for end (calculating R^2)
        sumy += y[i];
        x.push_back((float)(i+1));
        sumx += x[i];
        dotxy += x[i] * y[i];
        sumxsq += x[i] * x[i];
    }   // end for
}   // end ctor



double LinearRegressor::calcSmoothedLine()
{
    calcLineParams();   // Parameters for the initial line (with outliers)
    removeOutliers();   // Remove outliers > 2 std devs away from mean

    /*
    if ( M > 2 && M < inity.size())  // Removed some outliers so parse one more time to get rid of hangers on
    {
        calcLineParams();
        removeOutliers();
    }   // end if
    */

    calcLineParams();   // Line parameters are now lovely

    double rSquared = 0.0;
    if ( M < 2) // No line is possible if M is less than 2 (rSquared is set to 0 indicating impossible fit)
        return rSquared;

    // Create the smoothed line for return and get R^2 params
    double sserr = 0.0;
    double sstot = 0.0;
    double meany = sumy / y.size();

    for ( size_t i = 0; i < x.size(); ++i)
    {
        outy.push_back( (float)(slope * (i+1) + intercept));
        sserr += pow( y[i] - (float)(slope * x[i] + intercept), 2);
        sstot += pow( y[i] - meany, 2);
    }   // end for

    for ( size_t i = x.size(); i < inity.size(); ++i)
        outy.push_back( (float)(slope * (i+1) + intercept));

    rSquared = 1.0;
    if ( sstot > 0.0)
        rSquared -= sserr/sstot;

    return rSquared;
}   // end calcSmoothedLine



vector<float> LinearRegressor::getLine() const
{
    if ( outy.size() >= 2)
        return outy;
    else
        return inity;
}   // end getLine



float LinearRegressor::getStartPoint() const
{
    if ( outy.size() >= 2)
        return *outy.begin();
    else
        return *inity.begin();
}   // end getStartPoint



float LinearRegressor::getEndPoint() const
{
    if ( outy.size() >= 2)
        return *outy.rbegin();
    else
        return *inity.rbegin();
}   // end getEndPoint



void LinearRegressor::calcLineParams()
{
    slope = (M * dotxy - sumx * sumy) / (M * sumxsq - sumx * sumx);
    intercept = 1.0/M * (sumy - slope * sumx);
    //cerr << "f(x) = " << slope << "x + " << intercept << endl;
}   // end calcLineParams



void LinearRegressor::removeOutliers()
{
    vector<double> d;
    double sum_sq_d = 0.0;

    for ( size_t i = 0; i < M; ++i)
    {
        d.push_back( y[i] - (slope * x[i] + intercept));
        sum_sq_d += d[i] * d[i];
    }   // end for

    double std_d = sqrt( sum_sq_d / M); // Std dev of differences is sqrt of mean sqrd error (std err)

    // Remove all data points corresponding to the difference value in d being greater than 1
    // standard error and adjust the parameters required to calculate the slope and intercept
    vector<float> y2;
    vector<float> x2;
    size_t M2 = 0;
    for ( size_t i = 0; i < M; ++i)
    {
        if ( (double)fabs(d[i]) > 2 * std_d)
        {
            sumy -= y[i];
            dotxy -= x[i] * y[i];
            sumx -= x[i];
            sumxsq -= x[i] * x[i];
        }   // end if
        else
        {
            y2.push_back( y[i]);
            x2.push_back( x[i]);
            M2++;
        }   // end else
    }   // end for

    y = y2;
    x = x2;
    M = M2;
}   // end removeOutliers
