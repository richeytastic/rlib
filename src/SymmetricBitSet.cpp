#include "SymmetricBitSet.h"
using rlib::SymmetricBitSet;
#include <iostream>


static const int BYTE_SZ = 8;


SymmetricBitSet::SymmetricBitSet( size_t s)
    : sz( s), buffer(NULL)
{
    int bsz = byteSize();
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


uint calcBitIndex( uint sz, uint low, uint high)
{
    return sz*low - (low*(low + 1))/2 + high;
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
    const int &sz = bsm.sz;
    for ( int i = 0; i < sz; ++i)
    {
        for ( int j = 0; j < sz; ++j)
            os << (bsm.isSet( i, j) ? '#' : '-') << " ";
        os << std::endl;
    }   // end for
    return os;
}   // end operator<<


