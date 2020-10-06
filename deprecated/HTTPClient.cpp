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

#include "HTTPClient.h"
using rlib::HTTPClient;
#include <vector>
#include <iostream>
#include <sstream>


HTTPClient::HTTPClient( const string &host, const string &path, boost::asio::io_service& io)
    : TCPClient( host, "http", io)
{
    // Connected - so make the request
    std::ostringstream oss;
    oss << "GET " << path << " HTTP/1.0\r\n";
    oss << "Host: " << host << "\r\n";
    oss << "Accept: */*\r\n";
    oss << "Connection: close\r\n\r\n";
    TCPClient::write( oss.str()); // write request to the TCP socket
}   // end ctor


int HTTPClient::read( string& content, string* contentType)
{
    std::vector<char> vbuf;
    size_t len = TCPClient::read( vbuf);

    string response( vbuf.begin(), vbuf.end());
    std::istringstream iss( response);

    // Get the header data from the response
    string httpVersion;
    uint statusCode;
    string statusMsg;
    iss >> httpVersion >> statusCode;
    std::getline( iss, statusMsg);

    if ( !iss || httpVersion.substr(0,5) != "HTTP/")
    {
        std::cerr << "Not a valid HTTP response!" << std::endl;
        return -1;
    }   // end if

    if ( statusCode != 200)
    {
        std::cerr << "HTTP server responded with status code " << statusCode << std::endl;
        return -statusCode;
    }   // end if

    string hdrLn;
    if ( contentType != NULL)
    {
        string contentTypeTag;
        iss >> contentTypeTag;
        string contentTemp;
        iss >> contentTemp;
        *contentType = contentTemp.substr(0,contentTemp.size()-1);   // Remove trailing ;
    }   // end if
    std::getline( iss, hdrLn);// Dump rest of the line (charset)

    // Read in the rest of the HTTP header until we get a blank line, then stick
    // the rest of the content into the content parameter for return.
    while ( std::getline( iss, hdrLn) && hdrLn.size() > 1);

    int nxtPos = iss.tellg();
    if ( nxtPos >= 0)
        content = string( &vbuf[nxtPos], vbuf.size() - nxtPos);
    return content.size();
}   // end read
