#pragma once
#ifndef RLIB_USTRING_H
#define RLIB_USTRING_H

#include "rlib_Export.h"
#include <cstdlib>
#include <ostream>
using std::ostream;

#include <string>
using std::string;
using std::basic_string;

typedef unsigned char uchar;
typedef unsigned int uint;


namespace rlib
{

class rlib_EXPORT ustring
{
public:
    ustring();	// Create an empty ustring
    ustring( const char *str);	// Null terminated c style string
    ustring( const char *buff, uint len);
    ustring( const uchar *buff, uint len);
    ustring( const string &s);	// Allow implicit conversions from string
    ~ustring();

    ustring( const ustring &us);	// Copy constructor
    const ustring &operator=( const ustring &us);	// Copy assignment

    uint length() const { return len;}
    uint size() const { return len;}
    bool empty() const { return len == 0;}
    void reserve( uint sz);	// Reserve sz bytes in this ustring

    /** Returns printable hex string of the bytes within this ustring.
        * Length of hex string is twice that of length of raw ustring. */
    string to_hex() const;

    /** Return an ascii version of the ustring terminated with a NULL.
        * WARNING - this string may contain non-printable characters! */
    string to_ascii() const;

    /** Copies the contents of the ustring into buff.
        * WARNING - buff is assumed to have adequate length. */
    void to_buffer( uchar *buff) const;

    /** Returns a pointer to the contents of bs. */
    const uchar *data() const;

    bool operator==( const ustring &us) const;
    bool operator!=( const ustring &us) const;


private:
    basic_string< uchar> *bs;
    uint len;

    void copy( const ustring &us);
};	// end class


// Prints us.to_hex() to os
rlib_EXPORT ostream &operator<<( ostream &os, const ustring &us);

rlib_EXPORT const ustring operator+( const ustring &us1, const ustring &us2);
}	// end namespace

#endif
