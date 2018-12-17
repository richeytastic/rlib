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

#include <RangedScalarDistribution.h>
#include <stdexcept>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <boost/algorithm/string.hpp>
using rlib::RangedScalarDistribution;


namespace {

bool readData( const std::string& fname, Vec_3DP& dvec)
{
    bool readOk = false;
    try
    {
        std::ifstream ifs;
        ifs.open( fname.c_str(), std::ifstream::in);
        using namespace rlib;
        ifs >> dvec;
        ifs.close();
        readOk = !dvec.empty();
    }   // end try
    catch ( const std::exception&)
    {
        readOk = false;
    }   // end catch

    return readOk;
}   // end readData

}   // end namespace


RangedScalarDistribution::Ptr RangedScalarDistribution::create( const Vec_3DP& d)
{
    if ( d.size() < 2)
    {
        std::cerr << "[ERROR] rlib::RangedScalarDistribution::create: Must have >= 2 data points!" << std::endl;
        return Ptr();
    }   // end if
    return Ptr( new RangedScalarDistribution( d));
}   // end create


RangedScalarDistribution::Ptr RangedScalarDistribution::create( const Vec_2DP& d)
{
    if ( d.size() < 2)
    {
        std::cerr << "[ERROR] rlib::RangedScalarDistribution::create: Must have >= 2 data points!" << std::endl;
        return Ptr();
    }   // end if
    return Ptr( new RangedScalarDistribution( d));
}   // end create


RangedScalarDistribution::Ptr RangedScalarDistribution::create( const Vec_1DP& d)
{
    if ( d.size() < 2)
    {
        std::cerr << "[ERROR] rlib::RangedScalarDistribution::create: Must have >= 2 data points!" << std::endl;
        return Ptr();
    }   // end if
    return Ptr( new RangedScalarDistribution( d));
}   // end create


RangedScalarDistribution::Ptr RangedScalarDistribution::fromFile( const std::string& fname)
{
    Vec_3DP dvec;
    if ( !readData( fname, dvec))
    {
        std::cerr << "[ERROR] rlib::RangedScalarDistribution::fromFile: Failed to read input file " << fname << std::endl;
        return Ptr();
    }   // end if
    return create(dvec);
}   // end fromFile


std::ostream& rlib::operator<<( std::ostream& os, const Vec_3DP& dvec)
{
    const size_t n = dvec.size();
    for ( size_t i = 0; i < n; ++i)
        os << dvec[i][0] << "\t" << dvec[i][1] << "\t" << dvec[i][2] << std::endl; 
    return os;
}   // end operator<<


std::istream& rlib::operator>>( std::istream& is, Vec_3DP& dvec)
{
    int lnCount = 0;
    DP t, y, z;
    std::string ln;
    while ( is.good() && !is.eof())
    {
        std::getline( is, ln);
        boost::algorithm::trim(ln);

        if ( ln.empty())
            continue;

        std::vector<std::string> toks;
        boost::split( toks, ln, boost::is_any_of("\t "));
        std::istringstream iss( ln);

        t = y = z = 0;
        if ( toks.size() == 1)
        {
            t = lnCount;
            iss >> y;
        }   // end if
        else if ( toks.size() == 2)
            iss >> t >> y;
        else if ( toks.size() == 3)
            iss >> t >> y >> z;

        dvec.push_back({t, y, z});
        lnCount++;
    }   // end while

    return is;
}   // end operator>>


RangedScalarDistribution::RangedScalarDistribution( const Vec_3DP& d)
    : _minterp( nullptr), _zinterp(nullptr), _tmin(0), _tmax(0), _hasz(true)
{
    const size_t n = d.size();
    _dvec.resize(n);

    assert( n >= 2);
    std::vector<double> t(n);
    std::vector<double> m(n);
    std::vector<double> z(n);
    for ( size_t i = 0; i < n; ++i)
    {
        t[i] = d[i][0];
        m[i] = d[i][1];
        z[i] = d[i][2];

        _dvec[i] = d[i];   // For storage
    }   // end for

    _tmin = t[0];
    _tmax = t[n-1];
    _minterp = new boost::math::barycentric_rational<double>( t.data(), m.data(), n);
    _zinterp = new boost::math::barycentric_rational<double>( t.data(), z.data(), n);
}  // end ctor


RangedScalarDistribution::RangedScalarDistribution( const Vec_2DP& d)
    : _minterp( nullptr), _zinterp(nullptr), _tmin(0), _tmax(0), _hasz(false)
{
    const size_t n = d.size();
    _dvec.resize(n);

    assert( n >= 2);
    std::vector<double> t(n);
    std::vector<double> m(n);
    std::vector<double> z(n);
    for ( size_t i = 0; i < n; ++i)
    {
        t[i] = d[i][0];
        m[i] = d[i][1];
        z[i] = 0;

        _dvec[i] = {t[i], m[i], z[i]}; // For storage
    }   // end for

    _tmin = t[0];
    _tmax = t[n-1];
    _minterp = new boost::math::barycentric_rational<double>( t.data(), m.data(), n);
    _zinterp = new boost::math::barycentric_rational<double>( t.data(), z.data(), n);
}  // end ctor



RangedScalarDistribution::RangedScalarDistribution( const Vec_1DP& d)
    : _minterp( nullptr), _zinterp(nullptr), _tmin(0), _tmax(0), _hasz(false)
{
    const size_t n = d.size();
    _dvec.resize(n);

    assert( n >= 2);
    std::vector<double> t(n);
    std::vector<double> m(n);
    std::vector<double> z(n);
    for ( size_t i = 0; i < n; ++i)
    {
        t[i] = double(i);
        m[i] = d[i];
        z[i] = 0;

        _dvec[i] = {t[i], m[i], z[i]}; // For storage
    }   // end for

    _tmin = t[0];
    _tmax = t[n-1];
    _minterp = new boost::math::barycentric_rational<double>( t.data(), m.data(), n);
    _zinterp = new boost::math::barycentric_rational<double>( t.data(), z.data(), n);
}  // end ctor



RangedScalarDistribution::~RangedScalarDistribution()
{
    delete _minterp;
    delete _zinterp;
}   // end dtor


double RangedScalarDistribution::mval( double t) const { return (*_minterp)(t);}
double RangedScalarDistribution::zval( double t) const { return _hasz ? (*_zinterp)(t) : 0;}


double RangedScalarDistribution::zscore( double t, double x) const
{
    double zval = (*_zinterp)(t);
    if ( zval <= 0.0)
        return 0.0;
    return (x - (*_minterp)(t))/zval;
}   // end zscore

