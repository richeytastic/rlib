#include <Compression.h>
using namespace rlib;

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 262144

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
using namespace std;



// Check the different return codes
void zerr( int ret)
{
    switch (ret)
    {
        case Z_ERRNO:   // Error reading / writing
            throw CompressException( "zlib error reading/writing to stream!");
            break;
        case Z_STREAM_ERROR:    // Invalid compression level
            throw CompressException( "zlib has an invalid compression level!");
            break;
        case Z_BUF_ERROR:
            throw CompressException( "zlib buffer size not large enough to contain data!");
            break;
        case Z_DATA_ERROR:  // Invalid or incomplete data
            throw CompressException( "zlib got invalid/incomplete data!");
            break;
        case Z_MEM_ERROR:   // Out of memory
            throw CompressException( "zlib is out of memory!");
            break;
        case Z_VERSION_ERROR:   // zlib version mismatch
            throw CompressException( "zlib version mismatch!");
            break;
        case Z_OK:  // Okay
            break;
        default:
            throw CompressException( "Unknown zlib error!");
    }   // end switch
}   // end zerr



void rlib::decompress( byte *udata, size_t &usz, const byte *cdata, size_t csz) throw (CompressException)
{
    cerr << "Compressed buffer size: " << csz << endl;
    cerr << "Buffer space:           " << usz << endl;
    int ret = uncompress( udata, (uLongf*)&usz, cdata, csz);
    cerr << "Buffer bytes written:   " << usz << endl;

    zerr(ret);
    if ( usz < 1)
        throw CompressException( "Decompressed segment length is zero!");
}  // end decompress



byte* rlib::new_decompress( size_t &sz, const byte *src, size_t srcSz) throw (CompressException)
{
    // Find a suitable buffer size to decompress src bytes into
    size_t dSz = srcSz * 2;
    while ( compressBound( dSz) < srcSz * 2)
        dSz *= 2;

    byte *buffer = (byte*)malloc(dSz);
    if ( buffer == NULL)
        throw CompressException( "Could not allocate enough memory to decompression buffer!");

    size_t actSz = dSz;
    decompress( buffer, actSz, src, srcSz);

    // Realloc to actual size
    sz = actSz;
    byte *data = new byte[sz];   // We want to returned a buffer allocated with new
    if ( data == NULL)
        throw CompressException( "Couldn't reallocate buffer size for decompressed data!");
    memcpy( data, buffer, sz);
    return data;
}   // end new_decompress



byte* rlib::new_compress( size_t &sz, const byte *src, size_t srcSz) throw (CompressException)
{
    size_t maxSz = compressBound(srcSz);    // Get maximum size of compression
    size_t actSz = maxSz; // Actual size
    byte *buffer = (byte*)malloc( maxSz);
    if ( buffer == NULL)
        throw CompressException( "Could not allocate enough memory for compression buffer!");

    int ret = compress( buffer, (uLongf*)&actSz, src, srcSz);
    zerr(ret);

    // Realloc to actual size
    sz = actSz;
    byte *data = new byte[sz];   // We want to returned a buffer allocated with new
    if ( data == NULL)
        throw CompressException( "Couldn't reallocate buffer size for compressed data!");
    memcpy( data, buffer, sz);
    return data;
}   // end new_compress
