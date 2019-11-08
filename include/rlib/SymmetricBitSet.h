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

#pragma once
#ifndef RLIB_SYMMETRIC_BIT_SET_H
#define RLIB_SYMMETRIC_BIT_SET_H

#include "rlib_Export.h"
#include <cstdlib>
typedef unsigned int uint;
typedef unsigned char byte;
#include <ostream>
using std::ostream;


namespace rlib
{

class rlib_EXPORT SymmetricBitSet
{
public:
    SymmetricBitSet( size_t sz);
    virtual ~SymmetricBitSet();

    inline size_t size() const { return sz;}
    bool isSet( uint i, uint j) const;
    // Set element to the provided value
    void set( uint i, uint j, bool val);
    // Set element true
    void set( uint i, uint j);
    // Set element false
    void unset( uint i, uint j);

    // Returns the total number of bytes used in the storage buffer.
    size_t byteSize() const;

private:
    size_t sz;  // Size in bits
    byte *buffer;

    friend ostream &operator<<( ostream &os, const SymmetricBitSet &bsm);
};  // end class


ostream &operator<<( ostream &os, const SymmetricBitSet &bsm);

}   // end namespace

#endif
