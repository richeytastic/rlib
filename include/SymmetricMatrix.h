#pragma once
#ifndef RLIB_SYMMETRIC_MATRIX_H
#define RLIB_SYMMETRIC_MATRIX_H

typedef unsigned int uint;
#include <ostream>
using std::ostream;
#include <iomanip>

namespace rlib
{

template <typename T>
class SymmetricMatrix
{
public:
    SymmetricMatrix( size_t sz, size_t width=3);
    virtual ~SymmetricMatrix();

    inline size_t size() const { return sz;}
    T get( uint i, uint j) const;
    void set( uint i, uint j, T val);

    inline void setElementPrintWidth( size_t w)
    {
        width = w;
        if ( width < 1)
            width = 1;
    }   // end setElementPrintWidth

    // Returns the number of bytes used to store this matrix.
    size_t byteSize() const;

private:
    size_t sz;
    T *buffer;
    size_t width;   // Width of matrix elements when printed

    uint calcBufferIdx( uint, uint, uint) const;

    template <typename R>
    friend ostream &operator<<( ostream &os, const SymmetricMatrix<R> &sm);
};  // end class

#include "template/SymmetricMatrix_template.h"

}   // end namespace

#endif
