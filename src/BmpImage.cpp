#include <BmpImage.h>
using namespace rlib;

#include <iostream>
using namespace std;



BmpImage::BmpImage( const uchar *ps, uint w, uint h) : pxls( NULL), wd( w), ht( h)
{
	pxls = new uchar[ w * h * 3];	// Times 3 because 24 bit pixels
	memcpy( pxls, ps, w * h * 3);
}  // end constructor



BmpImage::~BmpImage()
{
	if ( pxls != NULL)
		delete[] pxls;
}  // end destructor



BmpImage::BmpImage( const string &filename) throw ( ImageException)
{
	ifstream input( filename.c_str(), ifstream::binary);
	if ( input.fail())
		throw ImageException( "Couldn't find file!");

	char buffer[2];
	input.read( buffer, 2);

	if ( buffer[0] != 'B' || buffer[1] != 'M')
		throw ImageException( "Not bitmap file!");

	input.ignore( 8);
	uint data_offset = read_int32( input);

	// Read the header
	uint header_size = read_int32( input);
	switch( header_size)
	{
		case 40: // V3
			wd = read_int32( input);
			ht = read_int32( input);
			input.ignore( 2);
			if ( read_int16( input) != 24)
				throw ImageException( "Image is not 24 bits per pixel");
			if ( read_int16( input) != 0)
				throw ImageException( "Image is compressed");
			break;
		case 12: // OS/2 V1
			wd = read_int32( input);
			ht = read_int32( input);
			input.ignore( 2);
			if ( read_int16( input) != 24)
				throw ImageException( "Image is not 24 bits per pixel");
			break;
		case 64: // OS/2 V2
			throw ImageException( "Can't load OS/2 V2 bitmaps");
			break;
		case 108: // Windows V4
			throw ImageException( "Can't load Windows V4 bitmaps");
			break;
		case 124: // Windows V5
			throw ImageException( "Can't load Windows V5 bitmaps");
			break;
		default:
			throw ImageException( "Unknown bitmap format");
			break;
	}	// end swtich
	
	uint bytes_per_row = (( wd * 3 + 3) / 4) * 4 - ( wd * 3 % 4);
	uint size = bytes_per_row * ht;
	uchar pxls1[ size];

	// Read the data
	input.seekg( data_offset, ios_base::beg);
	input.read( (char*)pxls1, size);
	
	// Format the data
	pxls = new uchar[ wd * ht * 3];	// x3 multiplier since 24 bit pixel info
	for ( uint y = 0; y < ht; ++y)
		for ( uint x = 0; x < wd; ++x)
			for ( uint c = 0; c < 3; ++c)
				pxls[ 3 * ( wd * y + x) + c] = pxls1[ bytes_per_row * y + 3 * x + (2 - c)];
	
	input.close();
}  // end ctor



// Convert four-character array to integer assuming little-endian
int32_t rlib::to_int32( const char *bytes)
{
	return int32_t( ( uchar( bytes[3]) << 24) | ( uchar( bytes[2]) << 16) | ( uchar( bytes[1]) << 8) | ( uchar( bytes[0])));
}  // end to_int32


	
// Convert two-character array to short assuming little-endian
int16_t rlib::to_int16( const char *bytes)
{
	return int16_t( ( uchar( bytes[1]) << 8) | uchar( bytes[0]));
}  // end to_int16



// Read the next four bytes as a 4 byte integer assuming little-endian
int32_t rlib::read_int32( ifstream &input)
{
	char buffer[4];
	input.read( buffer, 4);
	return to_int32( buffer);
}  // end read_int32



// Read the next two bytes as a 2 byte integer assuming little-endian
int16_t rlib::read_int16( ifstream &input)
{
	char buffer[2];
	input.read( buffer, 2);
	return to_int16( buffer);
}  // end read_int16



void BmpImage::getPixels( uchar *buff, uint len) const
{
	uint num = len;
	if ( num > ( wd * ht * 3))
		num = wd * ht * 3;
	memcpy( buff, pxls, num);
}	// end getPixels
