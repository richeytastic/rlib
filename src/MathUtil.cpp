/************************************************************************
 * Copyright (C) 2018 Richard Palmer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ************************************************************************/

#include <MathUtil.h>
#include <iostream>
#include <cassert>
#include <cfloat>
#include <cmath>


DP rlib::polint( const Vec_DP& xa, const Vec_DP& ya, const DP x, DP& dy)
{
    const int n = (int)xa.size();
    assert( n == (int)ya.size());
    assert( n > 0);
    if ( n == 0)
    {
        dy = DBL_MAX;
        return 0.0;
    }   // end if

    // Find ns as the index of the closest entry in xa to x.
    Vec_DP c(n), d(n);
    int ns = 0;
    DP dif = fabs(x-xa[0]);
    DP dift;
    for ( int i = 0; i < n; ++i)
    {
        if ( ( dift = fabs(x-xa[i])) < dif)
        {
            ns = i;
            dif = dift;
        }   // end if

        c[i] = d[i] = ya[i];    // Also initialise vectors c and d (the tableau)
    }   // end for

    DP y = ya[ns--];    // Initial approximation to f(x)

    for ( int m = 1; m < n; ++m)    // For each column of the tableau
    {
        for ( int i = 0; i < n-m; ++i)
        {
            DP ho = xa[i] - x;
            DP hp = xa[i+m] - x;
            DP w = c[i+1] - d[i];
            DP den = ho - hp;
            if ( den == 0.0)
            {
                std::cerr << "[ERROR] rlib::polint: Too small difference in input x values!: "
                          << "|xa[" << i << "] - xa[" << (i+m) << "]| = " << fabs(xa[i] - xa[i+m]) << std::endl;
                dy = DBL_MAX;
                return 0.0;
            }   // end if

            // Update the c and d vectors
            den = w/den;
            d[i] = hp*den;
            c[i] = ho*den;
        }   // end for

        dy = 2*(ns+1) < (n-m) ? c[ns+1] : d[ns--];
        y += dy;
    }   // end for

    return y;
}   // end polint


double rlib::round( double x, size_t ndp)
{
    const double E = pow(10,ndp);
    const double y = double(long(x));
    const double z = double(long((x-y)*E + 0.5));
    return y + z/E;
}   // end round
