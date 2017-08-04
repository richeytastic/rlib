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

/**
 * HTTP client written using cURL.
 *
 * Richard Palmer
 * 28 May 2011
 */

#pragma once

#ifndef RLIB_HTTP_CLIENT_H
#define RLIB_HTTP_CLIENT_H

#include <curl/curl.h>
#include <cstdlib>
#include <exception>
#include <string>
using std::string;
typedef unsigned char byte;


namespace rlib
{

/**
 * Exception class for HTTP errors.
 */
class HttpException: public std::exception
{
public:
    HttpException( int errCode, const char* err);
    ~HttpException() throw(){};
    virtual const char* what() const throw();
    int errorCode() const;
private:
    int m_errCode;
    string m_err;
}; // end HttpException



class HttpClient
{
public:
    // Server responses are received in Response structs.
    struct Response
    {
        byte* buffer;
        size_t nmemb;

        // Reset the members of this Response object to zero WITHOUT freeing memory!
        inline void reset(){ buffer = NULL; nmemb = 0;}

        // Free the memory pointed to by the Response buffer and reset.
        inline void free(){ if (buffer != NULL) delete[] buffer; reset();}
        //inline void free(){ if (buffer != NULL) free(buffer); reset();}

        Response() : buffer(NULL), nmemb(0){}
        ~Response(){ free();}
    };    // end struct

    // Client code must call this when no more cURL resources are required.
    static void shutdown();

    HttpClient();
    HttpClient( const string& url);
    ~HttpClient();

    /**
     * Request a page from the server. Contents is written into the provided
     * Response struct (which is also returned). The buffer within this struct Response
     * is expanded as required to hold the received data.
     */
    Response& doGet( Response& output) const throw (HttpException);

    /**
     * Send qry to the server as a POST HTTP request. The server's response is
     * written into the provided struct Response (which is also returned). The buffer within
     * this struct Response is expanded as required to hold the received data.
     */
    Response& doPost( const char* qry, Response& output) const throw (HttpException);
    

    /**
     * Set the HTTP header in the form "header field: value"
     */
    void setHeader( const string& header);
    void setUrl( const string& url);
    inline string getUrl() const { return m_url;}

private:
    CURL* m_handle;
    struct curl_slist* m_headers;
    string m_url; // Server url

    // No copy constructors!
    HttpClient( const HttpClient &hc);
    const HttpClient& operator=( const HttpClient& hc);

    void init();    // Constructor init

    Response& sendRequest( Response& output) const throw (HttpException);    // Called by doPost and doGet methods
}; // end HttpClient

}    // end namespace

#endif
