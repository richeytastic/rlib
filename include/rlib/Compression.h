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
#ifndef RLIB_COMPRESSION_H
#define RLIB_COMPRESSION_H

#include <Exceptions.h>
using namespace rlib;
#include <zlib.h>
typedef unsigned char byte;


namespace rlib
{
// Decompress byte array src of length srcSz into buffer dest. Out parameter destSz
// holds number of bytes written to dest on return. The destination buffer must be
// large enough to hold the total number of uncompressed bytes!
extern void decompress( byte *dest, size_t &destSz, const byte *src, size_t srcSz) throw (CompressException);

// Find a nicely sized memory allocated buffer to decompress the src data into and return it.
// Parameter sz is the total size of the returned decompressed data.
extern byte* new_decompress( size_t &sz, const byte *src, size_t srcSz) throw (CompressException);

// Find a nicely sized memory allocated buffer to compress the src data into and return it.
// Parameter sz is the total size of the returned compressed data.
extern byte* new_compress( size_t &sz, const byte *src, size_t srcSz) throw (CompressException);
}   // end namespace rlib


#endif
