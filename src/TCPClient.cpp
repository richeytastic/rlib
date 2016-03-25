#include "TCPClient.h"
using rlib::TCPClient;
#include <iostream>


TCPClient::TCPClient( const string &host, const string &serviceName, boost::asio::io_service &io)
    : socket_(io)
{
    tcp::resolver resolver( io);

    tcp::resolver::query query( host.c_str(), serviceName.c_str());
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::resolver::iterator end;

    boost::system::error_code error = boost::asio::error::host_not_found;
    while ( error && endpoint_iterator != end)
    {
        socket_.close();
        socket_.connect( *endpoint_iterator, error);
        endpoint_iterator++;
    }   // end while
    if ( error)
        throw boost::system::system_error( error);
}   // end ctor


size_t TCPClient::read( std::vector<char> &vbuf)
{
    boost::array<char, 128> buf;
    for (;;)
    {
        boost::system::error_code error;
        size_t len = socket_.read_some( boost::asio::buffer(buf), error);
        if ( len > 0)
            vbuf.insert( vbuf.end(), buf.begin(), buf.begin() + len);

        if ( error == boost::asio::error::eof)
            break;  // Connection closed cleanly by peer
        else if ( error)
            throw boost::system::system_error( error);  // Some other error
    }   // end for

    return vbuf.size();
}   // end read 


void TCPClient::write( const string &v)
{
    boost::asio::streambuf req;
    std::ostream reqStrm( &req);
    reqStrm << v;
    boost::asio::write( socket_, req);
}   // end write
