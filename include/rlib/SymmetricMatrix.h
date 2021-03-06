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

#ifndef RLIB_SYMMETRIC_MATRIX_H
#define RLIB_SYMMETRIC_MATRIX_H

using uint = unsigned int;
#include <ostream>
#include <iomanip>

namespace rlib {

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
    friend std::ostream &operator<<( std::ostream &os, const SymmetricMatrix<R> &sm);
};  // end class

#include "SymmetricMatrix.cpp"

}   // end namespace

#endif
