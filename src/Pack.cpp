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

#include <Pack.h>
#include <stdlib.h>
#include <string.h>


// pack754() -- pack a floating point number into IEEE-754 format
long long rlib::pack754( long double f, unsigned bits, unsigned expbits)
{
	long double fnorm;
	int shift;
	long long sign, exp, significand;
	unsigned significandbits = bits - expbits - 1; // -1 for sign bit

	if (f == 0.0) return 0; // get this special case out of the way

	// check sign and begin normalization
	if (f < 0) { sign = 1; fnorm = -f; }
	else { sign = 0; fnorm = f; }

	// get the normalized form of f and track the exponent
	shift = 0;
	while(fnorm >= 2.0) { fnorm /= 2.0; shift++; }
	while(fnorm < 1.0) { fnorm *= 2.0; shift--; }
	fnorm = fnorm - 1.0;

	// calculate the binary form (non-float) of the significand data
	significand = ( long long) ( fnorm * (( 1LL << significandbits) + 0.5f));

	// get the biased exponent
	exp = shift + ((1<<(expbits-1)) - 1); // shift + bias

	// return the final answer
	return (sign<<(bits-1)) | (exp<<(bits-expbits-1)) | significand;
}


// unpack754() -- unpack a floating point number from IEEE-754 format
long double rlib::unpack754( long long i, unsigned bits, unsigned expbits)
{
	long double result;
	long long shift;
	unsigned bias;
	unsigned significandbits = bits - expbits - 1; // -1 for sign bit

	if (i == 0) return 0.0;

	// pull the significand
    result = (long double)(i&((1LL<<significandbits)-1)); // mask
	result /= (1LL<<significandbits); // convert back to float
	result += 1.0f; // add the one back on

	// deal with the exponent
	bias = (1<<(expbits-1)) - 1;
	shift = ((i>>significandbits)&((1LL<<expbits)-1)) - bias;
	while(shift > 0) { result *= 2.0; shift--; }
	while(shift < 0) { result /= 2.0; shift++; }

	// sign it
	result *= (i>>(bits-1))&1? -1.0: 1.0;

	return result;
}


// packi16() -- store a 16-bit int into a char buffer (like htons())
void rlib::packi16( unsigned char *buf, uint16_t i)
{
	*buf++ = i>>8;
    *buf = (unsigned char)i;
}	// end packi16


// packi32() -- store a 32-bit int into a char buffer (like htonl())
void rlib::packi32( unsigned char *buf, uint32_t i)
{
	*buf++ = i>>24;
	*buf++ = i>>16;
	*buf++ = i>>8;
	*buf = i;
}	// end packi32


//unpacki16() -- unpack a 16-bit int from a char buffer (like ntohs())
uint16_t rlib::unpacki16( const unsigned char *buf)
{
	return ( buf[ 0] << 8) | buf[ 1];
}	// end unpacki16


//unpacki32() -- unpack a 32-bit int from a char buffer (like ntohl())
uint32_t rlib::unpacki32( const unsigned char *buf)
{
	return (buf[0]<<24) | (buf[1]<<16) | (buf[2]<<8) | buf[3];
}	// end unpacki32




size_t rlib::pack_buffer( unsigned char *buf, const char *form, ...)
{
	// Get length of the format string
	const size_t format_len = strlen( form);
	// Copy the format string into a local buffer
	char *format = (char*)malloc( format_len + 1);
	memcpy( format, form, format_len);
	format[ format_len] = '\0';

	size_t size = 0;	// The total size of the buffer that's packed

	va_list ap;
	va_start( ap, form);

	size_t i = 0;
	while ( i < format_len)
	{
		switch ( format[ i])
		{
			case 'h': // 16-bit
			{
				i++;
				int h = va_arg( ap, int);	// promoted
				packi16( buf + size, h);
				size += 2;
				break;
			}	// end case h
			case 'l': // 32-bit
			{
				i++;
				int l = va_arg( ap, int);
				packi32( buf + size, l);
				size += 4;
				break;
			}	// end case l
			case 'c': // 8-bit
			{
				i++;
				char c = (char)va_arg( ap, int); // promoted
				*(buf + size) = c & 0xff;
				size += 1;
				break;
			}	// end case c
			case 'f': // float
			{
				i++;
                float f = (float)va_arg( ap, double); // promoted
                uint32_t l = (uint32_t)pack754_32( f); // convert to IEEE 754
				packi32( buf + size, l);
				size += 4;
				break;
			}	// end case f
			case 's': // string
			{
				i++;
				char *s = va_arg( ap, char*);
                uint16_t len = (uint16_t)strlen( s);
				packi16( buf + size, len);
				size += 2;
				memcpy( buf + size, s, len);
				size += len;
				break;
			}	// end case s
			case 'u': // unsigned char* string
			{
				i++;
				unsigned char *u = va_arg( ap, unsigned char*);

				// Get the length of the uchar string from the format string
                uint16_t len = (uint16_t)strtol( format + i, NULL, 10); // Get the number of bytes that need to be read in from the unsigned char pointer
				packi16( buf + size, len);	// Pack length into the buffer
				size += 2;

				while ( isdigit( format[ i])) i++;	// Skip the digits giving the length in the format string

				// Copy the len bytes of the uchar byte string into the buffer
				memcpy( buf + size, u, len);
				size += len;
				break;
			}	// end case u
			default:
				i++;
				break;
		}	// end switch
	}	// end while

	va_end( ap);

    free( format);
	return size;
}	// end pack_buffer




void rlib::unpack_buffer( const unsigned char *buf, const char *form, ...)
{
	// Get length of the format string
	size_t format_len = strlen( form);
	// Copy the format string into a local buffer
	char *format = (char*)malloc( format_len + 1);
	memcpy( format, form, format_len);
	format[ format_len] = '\0';

	size_t offset = 0;	// Track buf offset

	va_list ap;
	short *h;
	int *l;
	char *c;
	float *f;
	long pf;
	char *s;
	int lenf, len, count;
	int *ln_ret;
	unsigned char *u;

	va_start( ap, form);

	size_t i = 0;
	while ( i < format_len)
	{
		switch ( format[ i])
		{
			case 'h': // 16-bit
				i++;
				h = va_arg( ap, short*);
				*h = unpacki16( buf + offset);
				offset += 2;
				break;
			case 'l': // 32-bit
				i++;
				l = va_arg( ap, int*);
				*l = unpacki32( buf + offset);
				offset += 4;
				break;
			case 'c': // 8-bit
				i++;
				c = va_arg( ap, char*);
				*c = (buf + offset)[0];
				offset += 1;
				break;
			case 'f': // float
				i++;
				f = va_arg( ap, float*);
				pf = unpacki32( buf + offset);
				offset += 4;
                *f = (float)unpack754_32( pf);
				break;
			case 's': // string
				i++;
				s = va_arg( ap, char*);

				lenf = strtol( format + i, NULL, 10); // Get the number of bytes that the caller is allowing buffer space for
				while ( isdigit( format[ i])) i++;

				len = unpacki16( buf + offset);

				offset += 2;
				count = ( len <= lenf) ? len : lenf;
				memcpy( s, buf + offset, count);
				s[ count] = '\0';
				offset += len;
				break;
			case 'u':	// unsigned char* string
				i++;
				ln_ret = va_arg( ap, int*);	// Will hold actual returned length of u (promoted)
				u = va_arg( ap, unsigned char*);	// Pointer to buffer to write in to

				lenf = strtol( format + i, NULL, 10); // Get the max number of bytes that can be written to the uchar buffer
				while ( isdigit( format[ i])) i++;

				len = unpacki16( buf + offset);	// Get the packed length
				offset += 2;

				count = ( len <= lenf) ? len : lenf;
				memcpy( u, buf + offset, count);
				*ln_ret = count;	// Provide the actual copied length back to the caller
				offset += len;
				break;
			default:
				i++;
				break;
		}	// end switch
	}	// end while

	va_end( ap);
    free(format);
}	// end unpack_buffer
