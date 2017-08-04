#ifndef RLIB_LINE_REGRESSOR_H
#define RLIB_LINE_REGRESSOR_H

#ifdef _WIN32
#pragma warning( disable : 4251)
#endif

#include "rlib_Export.h"
#include <vector>
#include <sys/types.h>

/*
#ifdef _WIN32
struct rlib_EXPORT std::_Container_base12;
template struct rlib_EXPORT std::_Simple_types<float>;
template class rlib_EXPORT std::_Vector_val<std::_Simple_types<float> >;
template class rlib_EXPORT std::allocator<float>;
template struct rlib_EXPORT std::_Wrap_alloc<std::allocator<float> >;
template class rlib_EXPORT std::_Compressed_pair<std::_Wrap_alloc<std::allocator<float> >, std::_Vector_val<std::_Simple_types<float> >, true>;
template class rlib_EXPORT std::vector<float>;
#endif
*/


namespace rlib
{

class rlib_EXPORT LinearRegressor
{
public:
    /**
     * Create a new linear regressor with the provided vector of values.
     */
    LinearRegressor( const std::vector<float> &vals);

    /**
     * Calculate the best fit line returning the coefficient of determination
     * for the goodness of fit. Values closer to 1 indicate a better fit.
     */
    double calcSmoothedLine();

    /**
     * Return the smoothed line if calcSmoothedLine has been called,
     * otherwise returns a copy of the original line.
     */
    std::vector<float> getLine() const;

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

    std::vector<float> inity;// Saved original
    std::vector<float> y;    // Adjusted
    std::vector<float> x;

    double slope;
    double intercept;

    std::vector<float> outy;

    void calcLineParams();

    void removeOutliers();
};  // end class

}   // end namespace rlib


#endif
