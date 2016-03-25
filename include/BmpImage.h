/***************************************************
 * BmpImage is place holder for bmp format images.
 *
 * Author: Richard Palmer
 * Date: September 2008
 * ************************************************/

#pragma once
#include <string>
#include <fstream>
using namespace std;

#include <string.h>
#include <cstdlib>
#include <sys/types.h>

typedef unsigned char uchar;
typedef unsigned int uint;


namespace rlib
{
	class ImageException
	{
		public:
			ImageException( const string &err) : err_str( err){}
			inline string getErrStr() const { return err_str;}
		private:
			string err_str;
	};	// end class ImageException



	// Represents a simple BMP image
	class BmpImage
	{
		public:
			BmpImage( const string &file_name) throw ( ImageException);
			BmpImage( const uchar *ps, uint w, uint h);
			virtual ~BmpImage();

			inline uint getWidth() const { return wd;}
			inline uint getHeight() const { return ht;}

			/**
			 * Copies at most len pixels from array pxls into the provided buffer.
			 */
			virtual void getPixels( uchar *buff, uint len) const;

		private:
			/**
			 * An array of the form (R1, G1, B1, R2, G2, B2, ...) indicating the
			 * color of each pixel in image.	Color components range from 0 to 255.
			 * The array starts the bottom-left pixel, then moves right to the end
			 * of the row, then moves up to the next column, and so on.	This is the
			 * format in which OpenGL likes images.
			 */
			uchar *pxls;
			uint wd;	// width of image
			uint ht;	// height of image

			BmpImage( const BmpImage&); // Not implemented
			void operator=( const BmpImage&);  // Not implemented
	}; // end class BmpImage


	extern int32_t to_int32( const char *bytes);	// Reads 4 characters into a 4 byte int
	extern int16_t to_int16( const char *bytes);	// Reads 2 characters into a 2 byte int
	extern int32_t read_int32( ifstream &input);	// Reads next 4 characters into a 4 byte int
	extern int16_t read_int16( ifstream &input);	// Reads next 2 characters into a 2 byte int
}	// end namespace rlib
