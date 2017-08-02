#include "ConvexOptimiser.h"
using rlib::ConvexOptimiser;
#include <cmath>


// Find a domain of f where f'(x1) < 0 and f'(x2) > 0
void ConvexOptimiser::findDomain( double &x1, double &x2) const
{
    double diff = 0.0;
    while ( d(x1) * d(x2) >= 0.0) // Keep going while both are -ve or +ve slopes
    {
        i++;
        diff = fabs(x2-x1) * 2;
        if ( d(x1) < 0)
            x2 += diff; // Expand x2 out to the right
        else
            x1 -= diff; // Expand x1 out to the left
    }   // end while
}   // end findDomain



double ConvexOptimiser::minimise( double precision) const
{
    precision = fabs(precision);    // Ensure precision is absolute

    i = 0;  // Reset loop count
    double x1 = 0.00001;
    double x2 = 1.0;
    findDomain( x1, x2);

    double diff = 0.0;
    while ( fabs( operator()(x1) - operator()(x2)) >= precision)
    {
        i++;
        diff = fabs(x2-x1) / 2;
        if ( d( x1 + diff) < 0.0)  // Keep f'(x1) negative
            x1 += diff; // Move x1 toward x2
        else
            x2 -= diff; // Move x2 toward x1
    }   // end while

    return (x2+x1) / 2;   // Split the difference
}   // end minimise
