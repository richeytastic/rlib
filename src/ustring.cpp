#include <ustring.h>
using namespace rlib;

#include <cstdio>
#include <cstring>



ustring::ustring() : bs( NULL), len( 0)
{
	bs = new basic_string< uchar>();
}	// end ustring ctor


ustring::ustring( const char *str) : bs( NULL), len( strlen( str))
{
	bs = new basic_string< uchar>( (const uchar*)str);
}	// end ustring ctor


ustring::ustring( const char *buff, uint ln) : bs( NULL), len( ln)
{
	bs = new basic_string< uchar>( (const uchar*)buff, ln);
}	// end ustring ctor


ustring::ustring( const uchar *buff, uint ln) : bs( NULL), len( ln)
{
	bs = new basic_string< uchar>( buff, ln);
}	// end ustring ctor


ustring::ustring( const string &s) : bs( NULL), len( s.length())
{
	bs = new basic_string< uchar>( (const uchar*)s.data(), len);
}	// end ustring ctor



ustring::ustring( const ustring &us) : bs( NULL), len( 0)
{
	copy( us);
}	// end ustring ctor



ustring::~ustring()
{
	delete bs;
	bs = NULL;
}	// end ustring d'tor



const ustring &ustring::operator=( const ustring &us)
{
	if ( &us != this)
	{
		delete bs;
		copy( us);
	}	// end if

	return *this;
}	// end op=



// Private function used by operator= and copy constructor
void ustring::copy( const ustring &us)
{
	len = us.len;
	uchar *buff = (uchar*)malloc( len);
	us.to_buffer( buff);
	bs = new basic_string< uchar>( buff, len);
    free(buff);
}	// end copy



void ustring::reserve( uint sz)
{
	bs->reserve( sz);
}	// end reserve


string ustring::to_hex() const
{
	char *hx = (char*)malloc( 2 * len);
	for ( uint i = 0; i < len; ++i)
		sprintf( hx + 2*i, "%02x", bs->data()[ i]);
    
    free(hx);
	return string( hx, 2 * len);
}	// end to_hex


string ustring::to_ascii() const
{
	return string( (const char*)this->data(), len);
}	// end to_ascii


void ustring::to_buffer( uchar *buff) const
{
	memcpy( buff, bs->data(), len);
}	// end to_buffer


const uchar *ustring::data() const
{
	return bs->data();
}	// end data


bool ustring::operator==( const ustring &us) const
{
	return *bs == *us.bs;
}	// end op==


bool ustring::operator!=( const ustring &us) const
{
	return *bs != *us.bs;
}	// end op!=



ostream &rlib::operator<<( ostream &os, const ustring &us)
{
	os << us.to_hex();
	return os;
}	// end op<<



const ustring rlib::operator+( const ustring &us1, const ustring &us2)
{
	uint us1_len = us1.size();
	uint us2_len = us2.size();
	uchar *buff = (uchar*)malloc( us1_len + us2_len);
	memcpy( buff, us1.data(), us1_len);
	memcpy( buff + us1_len, us2.data(), us2_len);
    free(buff);
	return ustring( buff, us1_len + us2_len);
}	// end op+
