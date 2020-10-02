/************************************************************************
 * Copyright (C) 2017 Richard Palmer
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

#include "SymmetricBitSet.h"
using rlib::SymmetricBitSet;
#include <iostream>


static const int BYTE_SZ = 8;


SymmetricBitSet::SymmetricBitSet( size_t s)
    : sz( s), buffer(NULL)
{
    int bsz = (int)byteSize();
    buffer = new byte[ bsz];
    for ( int i = 0; i < bsz; ++i)
        buffer[i] = 0;
}   // end ctor


SymmetricBitSet::~SymmetricBitSet()
{
    if ( buffer != NULL)
        delete[] buffer;
}   // end dtor


// On return, ensure i <= than j
void orderIndices( uint &i, uint &j)
{
    if ( i <= j)
        return;
    uint tmp = i;
    i = j;
    j = tmp;
}   // end orderIndices


uint calcBitIndex( size_t sz, uint low, uint high)
{
    return (uint)sz*low - (low*(low + 1))/2 + high;
}   // end calcBitIndex


bool SymmetricBitSet::isSet( uint i, uint j) const
{
    orderIndices( i, j);
    uint idx = calcBitIndex( sz, i, j);
    return buffer[idx / BYTE_SZ] >> (BYTE_SZ - (idx % BYTE_SZ) - 1) & 0x01;
}   // end getValue


void SymmetricBitSet::set( uint i, uint j, bool val)
{
    if ( val)
        set( i, j);
    else
        unset( i, j);
}   // end set


void SymmetricBitSet::set( uint i, uint j)
{
    orderIndices( i, j);
    uint idx = calcBitIndex( sz, i, j);
    buffer[idx / BYTE_SZ] |= 0x80 >> (idx % BYTE_SZ);
}   // end set


void SymmetricBitSet::unset( uint i, uint j)
{
    orderIndices( i, j);
    uint idx = calcBitIndex( sz, i, j);
    buffer[idx / BYTE_SZ] &= ~(0x80 >> (idx % BYTE_SZ));
}   // end unset


size_t SymmetricBitSet::byteSize() const
{
    return (sz*(sz+1)-2) / (2*BYTE_SZ) + 1;
}   // end byteSize


ostream &rlib::operator<<( ostream &os, const SymmetricBitSet &bsm)
{
    const int sz = (int)bsm.sz;
    for ( int i = 0; i < sz; ++i)
    {
        for ( int j = 0; j < sz; ++j)
            os << (bsm.isSet( i, j) ? '#' : '-') << " ";
        os << std::endl;
    }   // end for
    return os;
}   // end operator<<


