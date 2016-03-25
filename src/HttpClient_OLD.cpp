#define ndebug

#include <HttpClient.h>
using rlib::HttpClient;
using rlib::HttpException;
#include <curl/curl.h>
#include <curl/easy.h>

#include <sstream>
using std::ostringstream;
using std::stringstream;
#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstring>   // memcpy
#include <iomanip>



/**
 * Callback function for receiving data from the server.
 * Parameter buff is not null terminated and its total length is size * nmemb.
 * This total length is returned from the function.
 */
size_t cUrlServerResponseCallback( void* buff, size_t sz, size_t nmemb, void* userp)
{
   HttpClient::Response* response = (HttpClient::Response*)userp;

   size_t oldlen = response->nmemb;
   size_t thislen = sz * nmemb;
   size_t newlen = oldlen + thislen;

   // Create or grow the response buffer
   response->buffer = (byte*)realloc( response->buffer, newlen);

   // Copy in the contents of the function buffer to the static buffer
   memcpy( response->buffer + oldlen, buff, thislen);
   response->nmemb = newlen;   // Update response buffer length

   return thislen;
}  // end cUrlServerResponseCallback



/********************************************************
 ******************** HttpException *********************
 *******************************************************/
HttpException::HttpException( int errCode, const char* err) : m_errCode( errCode), m_err(err)
{}  // end ctor


const char* HttpException::what() const throw()
{
   return m_err.c_str();
}  // end what


int HttpException::errorCode() const
{
   return m_errCode;
}  // end errorCode



/********************************************************
 ******************** HttpClient ************************
 *******************************************************/
static bool cUrlInit = false;


void HttpClient::shutdown()
{
   if (cUrlInit)
   {
      curl_global_cleanup();
      cUrlInit = false;
   }  // end if
}  // end shutdown



void HttpClient::init()
{
   if ( !cUrlInit)
   {
      curl_global_init( CURL_GLOBAL_ALL);
      cUrlInit = true;
   }  // end if

   m_handle = curl_easy_init();
   m_headers = NULL;

   // Set the function that we want libcurl to call when the server responds with data
   curl_easy_setopt( m_handle, CURLOPT_WRITEFUNCTION, cUrlServerResponseCallback);
   curl_easy_setopt( m_handle, CURLOPT_HEADER, 0);   // Ensure HTTP header isn't returned in output
   curl_easy_setopt( m_handle, CURLOPT_VERBOSE, 1);   // Debugging on

#ifdef ndebug // Disable debugging if ndebug set
   curl_easy_setopt( m_handle, CURLOPT_VERBOSE, 0);
#endif
}  // end init



/**
 * Default constructor.
 */
HttpClient::HttpClient()
{
   init();
}  // end ctor



/**
 * Constructor with URL.
 */
HttpClient::HttpClient( const string &url)
{
   init();
   setUrl( url);
}  // end ctor



HttpClient::~HttpClient()
{
   curl_slist_free_all( m_headers);
   curl_easy_cleanup( m_handle);
}  // end dtor



void HttpClient::setHeader( const string& header)
{
   m_headers = curl_slist_append( m_headers, header.c_str());
   curl_easy_setopt( m_handle, CURLOPT_HTTPHEADER, m_headers);
}  // end setHeader



void HttpClient::setUrl( const string& url)
{
   m_url = url;
   curl_easy_setopt( m_handle, CURLOPT_URL, m_url.c_str());  // Set the server's url
}  // end setUrl



HttpClient::Response& HttpClient::doGet( HttpClient::Response& response) const throw (HttpException)
{
   curl_easy_setopt( m_handle, CURLOPT_HTTPGET, 1);
   sendRequest( response);
   return response;
}  // end doGet



HttpClient::Response& HttpClient::doPost( const char* qry, HttpClient::Response& response) const throw (HttpException)
{
   // Set the request data
   curl_easy_setopt( m_handle, CURLOPT_POSTFIELDS, qry);
   sendRequest( response);
   return response;
}  // end doPost



HttpClient::Response& HttpClient::sendRequest( HttpClient::Response& response) const throw (HttpException)
{
   // Ensure buffer is set for holding a possible error message.
   char errbuff[ CURL_ERROR_SIZE];
   curl_easy_setopt( m_handle, CURLOPT_ERRORBUFFER, errbuff);

   // Set where we want to write the server's response to
   response.free();
   curl_easy_setopt( m_handle, CURLOPT_WRITEDATA, &response);

   // Do the request
   CURLcode retCode = curl_easy_perform( m_handle);
   if ( retCode != 0)   // Check for error
      throw HttpException( retCode, errbuff);

   return response;
}  // end sendRequest
