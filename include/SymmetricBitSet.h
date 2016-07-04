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
