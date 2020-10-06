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

/*
 * This code taken from:
 * http://beej.us/guide/bgnet/output/html/multipage/advanced.html#serialization
 */

#ifndef RLIB_PACK_H
#define RLIB_PACK_H

#include "rlib_Export.h"
#include <cstdio>
#include <cctype>
#include <cstdarg>
#include <cstring>
#include <cstdint>

// macros for packing floats and doubles:
#define pack754_32(f) (pack754((f), 32, 8))
#define pack754_64(f) (pack754((f), 64, 11))
#define unpack754_32(i) (unpack754((i), 32, 8))
#define unpack754_64(i) (unpack754((i), 64, 11))

namespace rlib {
/*
** pack754() -- pack a floating point number into IEEE-754 format
*/ 
rlib_EXPORT long long pack754( long double f, unsigned bits, unsigned expbits);

/*
** unpack754() -- unpack a floating point number from IEEE-754 format
*/ 
rlib_EXPORT long double unpack754( long long i, unsigned bits, unsigned expbits);

/*
** packi16() -- store a 16-bit int into a char buffer (like htons())
*/ 
rlib_EXPORT void packi16( unsigned char *buf, uint16_t i);

/*
** packi32() -- store a 32-bit int into a char buffer (like htonl())
*/ 
rlib_EXPORT void packi32( unsigned char *buf, uint32_t i);

/*
** unpacki16() -- unpack a 16-bit int from a char buffer (like ntohs())
*/ 
rlib_EXPORT uint16_t unpacki16( const unsigned char *buf);

/*
** unpacki32() -- unpack a 32-bit int from a char buffer (like ntohl())
*/ 
rlib_EXPORT uint32_t unpacki32( const unsigned char *buf);

/**
* Store data dictated by the format string in the buffer returning
* the number of bytes written.
*
* h - 16-bit              l - 32-bit
* c - 8-bit char          f - float, 32-bit
* s - string (16-bit length automatically prepended) - null terminated.
* uN - unsigned char string (16-bit length is automatically prepended).
* N is the length of the ustring (missing N treated as zero)
*/
rlib_EXPORT size_t pack_buffer( unsigned char *buf, const char *format, ...);

/**
* Unpack data dictated by the format string from the provided buffer
* into the given variable references (must know format of buffer obviously)!
*
* h - 16-bit              l - 32-bit
* c - 8-bit char          f - float, 32-bit
* sN - string (16-bit length automatically prepended) - null terminated.
* N says to write no more than N bytes into s.
* uN - unsigned char string (16-bit length is automatically prepended).
* N says to write no more than N bytes into u.
* NB BEFORE the u parameter, a length reference must be given.
* This will hold the actual number of bytes written in to u.
*/
rlib_EXPORT void unpack_buffer( const unsigned char *buf, const char *format, ...);

}   // end namespace

#endif
