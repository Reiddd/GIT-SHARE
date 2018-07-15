#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

using     tcp       = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

constexpr char host[]   = "www.reidblog.cn";
constexpr char port[]   = "80";
constexpr char target[] = "/blog/";

int main()
{
    try{
        boost::asio::io_context io;

        websocket::stream<tcp::socket> ws{io};

        tcp::resolver resolver{io};
        tcp::resolver::results_type endpoints = resolver.resolve(tcp::resolver::query{host, port});
        boost::asio::connect(ws.next_layer(), endpoints);

        ws.handshake(host, target);

        ws.write(boost::asio::buffer("some messages"));

        boost::beast::flat_buffer buffer;
        ws.read(buffer);

        ws.close(websocket::close_code::normal);

        std::cout<< boost::beast::buffers(buffer.data()) <<std::endl;
    }
    catch(std::exception& e){
        std::cout<< e.what() <<std::endl;
    }

    return 0;
}
