#pragma once
#ifndef RLIB_TCP_CLIENT_H
#define RLIB_TCP_CLIENT_H

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include <boost/array.hpp>
#include <string>
using std::string;
#include <vector>


namespace rlib
{

class TCPClient
{
public:
    // Throws boost::asio::error::host_not_found if can not connect.
    TCPClient( const string &host, const string &serviceName, boost::asio::io_service &io);

    // Reads data into provided vector (returning number of bytes read in)
    // or throws an error if data could not be read.
    size_t read( std::vector<char> &vbuf);

    // Writes the given data to the socket.
    void write( const string &v);

private:
    tcp::socket socket_;
};  // end class

}   // end namespace

#endif
