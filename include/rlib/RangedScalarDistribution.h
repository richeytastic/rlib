/************************************************************************
 * Copyright (C) 2017 Richard Palmer.
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

#ifndef RLIB_RANGED_SCALAR_DISTRIBUTION_H
#define RLIB_RANGED_SCALAR_DISTRIBUTION_H

/**
 * Defines mean and standard deviation distributions over ranges (typically age ranges).
 * Functions for the value of the mean/standard deviation as the age variable changes
 * are given together. Function RangedScalarDistribution::zscore(a,x) returns the 
 * signed z-score of a value x at the distribution that maps to age variable a.
 */

#ifdef _WIN32
#pragma warning( disable : 4251)
#endif

#include "rlib_Export.h"
#include <boost/math/interpolators/barycentric_rational.hpp>
#include <boost/container/static_vector.hpp>
#include <iostream>
#include <cfloat>
#include <string>
#include <vector>
#include <memory>

using DP = double;
using Vec_3DP = std::vector<boost::container::static_vector<DP,3> >;
using Vec_2DP = std::vector<boost::container::static_vector<DP,2> >;
using Vec_1DP = std::vector<DP>;

namespace rlib {

class rlib_EXPORT RangedScalarDistribution
{
public:
    using Ptr = std::shared_ptr<RangedScalarDistribution>;
    using CPtr = std::shared_ptr<const RangedScalarDistribution>;

    // Create a new distribution from the given vector of triples {t,m,z} that
    // specify the independent variable t, the mean of the distribution at t, and
    // the Z value (1*+stddev) of the distribution at t.
    // The supplied vector must have at least two members!
    static Ptr create( const Vec_3DP&);
    static Ptr create( const Vec_2DP&);
    static Ptr create( const Vec_1DP&);

    // Create a new distribution from the combined average of the given distributions over ascending
    // independent points trng. The returned distribution ranges over these values as an average
    // distribution of those distributions having elements of trng in their domain.
    // This function naturally assumes that all of the distributions being combined are independent.
    static Ptr average( const std::vector<DP>& trng, const std::vector<CPtr>&);

    // Create from a data file which must have a row for each sample point.
    // Rows can be triples, doubles, or single values with values on a row separated by
    // whitespace. For double and triple value rows, the first value is taken as the independent
    // variable (age). For triples, the subsequent two values are taken to be the mean and z-score.
    // For double values, the second value is taken as the mean (z-score not used - set to zero).
    // Single value rows are taken as the mean with the row count (starting at zero) taken to be
    // the independent variable.
    // Null is returned if the input file cannot be read.
    static Ptr fromFile( const std::string& fname);

    RangedScalarDistribution( const Vec_3DP&);
    RangedScalarDistribution( const Vec_2DP&);
    RangedScalarDistribution( const Vec_1DP&);
    virtual ~RangedScalarDistribution();

    // Return the datapoints used to construct this object.
    const Vec_3DP& data() const { return _dvec;}

    // Simply return the value of the mean for this ranged distribution at t.
    DP operator()( DP t) const { return mval(t);}
    DP mval( DP t) const;

    // Return the z value at t (zero if not set).
    DP zval( DP t) const;

    // Returns true iff this object was constructed with Z values.
    bool hasZScores() const { return _hasz;}

    // Return the Z-score (# standard deviations) that measurement x is away from
    // the distribution's mean at point t. Will be zero if z-scores not present.
    DP zscore( DP t, DP x) const;

    // Return the min and max values of the independent variable.
    DP tmin() const { return _tmin;}
    DP tmax() const { return _tmax;}

private:
    Vec_3DP _dvec;
    boost::math::barycentric_rational<DP> *_minterp, *_zinterp;
    DP _tmin, _tmax;
    bool _hasz;

    RangedScalarDistribution( const RangedScalarDistribution&) = delete;
    void operator=( const RangedScalarDistribution&) = delete;
};  // end class

using RSD = RangedScalarDistribution;

rlib_EXPORT std::ostream& operator<<( std::ostream&, const Vec_3DP&);
rlib_EXPORT std::istream& operator>>( std::istream&, Vec_3DP&);

}   // end namespace

#endif
