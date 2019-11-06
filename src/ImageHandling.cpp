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

/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Textures" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */



#include <assert.h>
#include <fstream>
using namespace std;

#include "ImageHandling.h"
using namespace ImageHandling;


Image::Image( char *ps, int w, int h) : pxls(ps), wd(w), ht(h)
{  // empty body
}  // end constructor


Image::~Image()
{
   delete[] pxls;
}  // end destructor


namespace
{
	// Convert a four-character array to an integer, using little-endian form
	int toInt( const char *bytes)
   {
		return ( int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					 (unsigned char)bytes[0]);
	}  // end toInt

	
	// Convert a two-character array to a short, using little-endian form
	short toShort( const char *bytes)
   {
		return (short)(((unsigned char)bytes[1] << 8) |
					   (unsigned char)bytes[0]);
	}  // end toShort

	
	// Read the next four bytes as an integer, using little-endian form
	int readInt( ifstream &input)
   {
		char buffer[4];
		input.read( buffer, 4);
		return toInt( buffer);
	}  // end readInt

	
	// Read the next two bytes as a short, using little-endian form
	short readShort( ifstream &input)
   {
		char buffer[2];
		input.read( buffer, 2);
		return toShort( buffer);
	}  // end toShort

	
	// Just like auto_ptr, but for arrays
	// (explicit constructor used to disable implicit type conversion)
	template< class T>
	class auto_array
   {
	   private:
			T* array;
			mutable bool isReleased;
		public:
			explicit auto_array( T* array_ = NULL) :
				array(array_), isReleased(false) {
			}  // end default constructor

			auto_array( const auto_array<T> &aarray)
         {
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}  // end copy constructor
			
			~auto_array()
         {
				if ( !isReleased && array != NULL)
					delete[] array;
			}  // end destructor

			
			inline T* get() const { return array; }

			inline T &operator*() const { return *array; }
			
			void operator=( const auto_array<T> &aarray)
         {
				if ( !isReleased && array != NULL)
					delete[] array;

				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}  // end operator=
			
			inline T* operator->() const { return array; }
			
			T* release()
         {
				isReleased = true;
				return array;
			}  // end release

			
			void reset( T* array_ = NULL)
         {
				if ( !isReleased && array != NULL)
					delete[] array;

				array = array_;
			}  // end reset


			inline T* operator+(int i) { return array + i; }
			
			inline T &operator[](int i) { return array[i]; }
	}; // end class auto_array
}  // end namespace


Image *ImageHandling::loadBMP( const char* filename)
{
	ifstream input;
	input.open( filename, ifstream::binary);
	assert( !input.fail() || !"Could not find file");
	char buffer[2];
	input.read( buffer, 2);
	assert( buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
	input.ignore( 8);
	int dataOffset = readInt( input);
	
	// Read the header
	int headerSize = readInt( input);
	int width;
	int height;
	switch( headerSize)
   {
		case 40:
			// V3
			width = readInt( input);
			height = readInt( input);
			input.ignore( 2); 
			assert( readShort(input) == 24 || !"Image is not 24 bits per pixel");
			assert( readShort(input) == 0 || !"Image is compressed");
			break;
		case 12:
			// OS/2 V1
			width = readInt( input);
			height = readInt( input);
			input.ignore( 2);
			assert( readShort(input) == 24 || !"Image is not 24 bits per pixel");
			break;
		case 64:
			// OS/2 V2
			assert( !"Can't load OS/2 V2 bitmaps");
			break;
		case 108:
			// Windows V4
			assert( !"Can't load Windows V4 bitmaps");
			break;
		case 124:
			// Windows V5
			assert( !"Can't load Windows V5 bitmaps");
			break;
		default:
			assert( !"Unknown bitmap format");
         break;
	}  // end swtich
	
	// Read the data
	int bytesPerRow = (( width * 3 + 3) / 4) * 4 - ( width * 3 % 4);
	int size = bytesPerRow * height;
	auto_array<char> pixels( new char[ size]);
	input.seekg( dataOffset, ios_base::beg);
	input.read( pixels.get(), size);
	
	// Get the data into the right format
	auto_array<char> pixels2( new char[ width * height * 3]);
	for ( int y = 0; y < height; ++y)
		for ( int x = 0; x < width; ++x)
			for ( int c = 0; c < 3; ++c)
				pixels2[ 3 * (width * y + x) + c] =
					pixels[ bytesPerRow * y + 3 * x + (2 - c)];
	
	input.close();

	return new Image( pixels2.release(), width, height);
}  // end loadBMP
