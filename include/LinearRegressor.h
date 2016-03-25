#pragma once
#ifndef RLIB_LINE_REGRESSOR_H
#define RLIB_LINE_REGRESSOR_H

#include "rlib_Export.h"
#include <vector>
using std::vector;
#include <sys/types.h>


namespace rlib
{

class rlib_EXPORT LinearRegressor
{
public:
    /**
     * Create a new linear regressor with the provided vector of values.
     */
    LinearRegressor( const vector<float> &vals);

    /**
     * Calculate the best fit line returning the coefficient of determination
     * for the goodness of fit. Values closer to 1 indicate a better fit.
     */
    double calcSmoothedLine();

    /**
     * Return the smoothed line if calcSmoothedLine has been called,
     * otherwise returns a copy of the original line.
     */
    vector<float> getLine() const;

    /**
     * Returns the smoothed start point of the line if calcSmoothedLine
     * has been called, otherwise returns the start value of the original line.
     */
    float getStartPoint() const;

    /**
     * Returns the smoothed end point of the line if calcSmoothedLine
     * has been called, otherwise returns the end value of the original line.
     */
    float getEndPoint() const;

private:
    size_t M;
    double sumy;
    double sumx;
    double dotxy;
    double sumxsq;

    vector<float> inity;// Saved original
    vector<float> y;    // Adjusted
    vector<float> x;

    double slope;
    double intercept;

    vector<float> outy;

    void calcLineParams();

    void removeOutliers();
};  // end class

}   // end namespace rlib


#endif
