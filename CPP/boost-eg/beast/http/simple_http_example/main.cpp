#include <iostream>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

using       tcp  = boost::asio::ip::tcp;    // <boost/asio/ip/tcp.hpp>
namespace http = boost::beast::http;     // <boost/beast/http.hpp>

const      std::string host    = "www.reidblog.cn";
constexpr short      port    = 80;
const      std::string target  = "/blog/";
constexpr short      version = 11;

int main()
{
    try{
// io_context
        boost::asio::io_context io;

// resolve the host and build a connection
        tcp::resolver resolver(io);
        tcp::resolver::results_type endpoints = resolver.resolve(tcp::resolver::query(host, boost::lexical_cast<std::string>(port)));
        tcp::socket socket(io);
        boost::asio::connect(socket, endpoints);

// set up the request
        http::request<http::string_body> request(http::verb::get, target, version);
        request.set(http::field::host, host);
        request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

         std::cout<< request << std::endl;

// send the request
        http::write(socket, request);

// initialize a buffer, a response object to receive remote host's response
        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> response;
        http::read(socket, buffer, response);

// output the response
        std::cout<< response << std::endl;

// gracefully close the connection
        boost::system::error_code e;
        socket.shutdown(tcp::socket::shutdown_both, e);
        if(e && e != boost::system::errc::not_connected)
            throw boost::system::system_error(e);
    }
    catch(std::exception& e){
        std::cerr<< e.what() <<std::endl;
    }
    return 0;
}
