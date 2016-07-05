#include "Exceptions.h"
using rlib::Exception;

Exception::Exception( const string &err) : m_err(err){}
Exception::~Exception() throw(){}
const char* Exception::what() const throw(){ return m_err.c_str();}
string Exception::error() const throw(){ return m_err;}
string Exception::errStr() const throw(){ return m_err;}


rlib::InvalidVectorException::InvalidVectorException( const string &es) : Exception(es){}

rlib::IOException::IOException( const string &es) : Exception( es){}

rlib::OutOfBoundsException::OutOfBoundsException( const string &es) : Exception( es){}

rlib::OverflowException::OverflowException( const string &es) : Exception( es){}

rlib::OutOfMemoryException::OutOfMemoryException( const string &es) : Exception( es){}

rlib::ArithmeticException::ArithmeticException( const string &es) : Exception( es){}

rlib::TimeException::TimeException( const string &es) : Exception( es){}

rlib::VersionException::VersionException( const string &es) : Exception(es){}

rlib::CorruptionException::CorruptionException( const string &es) : Exception(es){}

rlib::JsonException::JsonException( const string &es) : Exception(es){}

rlib::ParseException::ParseException( const string &es) : Exception(es){}

rlib::SegmentException::SegmentException( const string &es) : Exception(es){}

rlib::CompressException::CompressException( const string &es) : Exception(es){}

rlib::InvalidImageException::InvalidImageException( const string &es) : Exception(es){}

rlib::PointCloudException::PointCloudException( const string &es) : Exception(es){}
