#pragma once
#ifndef RLIB_HTTP_CLIENT_H
#define RLIB_HTTP_CLIENT_H

#include "TCPClient.h"
using rlib::TCPClient;
#include <boost/asio.hpp>
#include <string>
using std::string;


namespace rlib
{

class HTTPClient : public TCPClient
{
public:
    HTTPClient( const string &host, const string &path, boost::asio::io_service& io);

    virtual ~HTTPClient(){}

    // Read in content from a received HTTP protocol response.
    // Returns size of content string on return or a negative value indicating
    // -1 for an invalid HTTP response or the negated HTTP status code received if not 200 (okay).
    // In addition, the content-type from the HTTP header is set in the provided string (if not NULL).
    int read( string& content, string* contentType=NULL);
};  // end class

}   // end namespace

#endif
