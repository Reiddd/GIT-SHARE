#include <iostream>
#include <stdlib.h>
#include <string>
#include <memory>
#include <functional>                   // bind || placeholder
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

using     tcp       = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

constexpr char host[] = "www.leetcode.com";
constexpr char port[] = "80";
constexpr char text[] = "???";

// --------------

void fail(boost::system::error_code& e, const char* what){
    std::cerr<< what << ": " << e.message() <<std::endl;
}

class Session: public std::enable_shared_from_this<Session>
{
public:
    explicit Session(boost::asio::io_context& io)
        : resolver_{io},
          ws_{io} {}


    void run(const char* host, const char* port, const char* text){
        host_ = host;
        text_ = text;

        resolver_.async_resolve(tcp::resolver::query{host, port}, std::bind(&Session::resolve_handle,
                                                                            shared_from_this(),
                                                                            std::placeholders::_1,
                                                                            std::placeholders::_2));
    }


    void resolve_handle(boost::system::error_code e, tcp::resolver::results_type endpoints){
        if(e)
            return fail(e, "resolve");

        boost::asio::async_connect(ws_.next_layer(), endpoints, std::bind(&Session::connect_handle,
                                                                          shared_from_this(),
                                                                          std::placeholders::_1));
    }


    void connect_handle(boost::system::error_code e){
        if(e)
            return fail(e, "connect");

        ws_.async_handshake(host_, "/", std::bind(&Session::handshake_handle,
                                                  shared_from_this(),
                                                  std::placeholders::_1));
    }


    void handshake_handle(boost::system::error_code e){
        if(e)
            return fail(e, "handshake");

        ws_.async_write(boost::asio::buffer(text_), std::bind(&Session::write_handle,
                                                              shared_from_this(),
                                                              std::placeholders::_1,
                                                              std::placeholders::_2));
    }


    void write_handle(boost::system::error_code e, std::size_t bytes_transferred){
        boost::ignore_unused(bytes_transferred);

        if(e)
            return fail(e, "write");

        ws_.async_read(buffer_, std::bind(&Session::read_handle,
                                          shared_from_this(),
                                          std::placeholders::_1,
                                          std::placeholders::_2));
    }


    void read_handle(boost::system::error_code e, std::size_t bytes_transferred){
        boost::ignore_unused(bytes_transferred);

        if(e)
            return fail(e, "read");

        ws_.async_close(websocket::close_code::normal, std::bind(&Session::close_handle,
                                                                 shared_from_this(),
                                                                 std::placeholders::_1));
    }


    void close_handle(boost::system::error_code e){
        if(e)
            return fail(e, "close");

        std::cout<< boost::beast::buffers(buffer_.data()) <<std::endl;
    }

private:
    tcp::resolver                  resolver_;
    websocket::stream<tcp::socket> ws_;
    boost::beast::multi_buffer     buffer_;
    std::string                    host_;
    std::string                    text_;
};

int main()
{
    boost::asio::io_context io;

    std::make_shared<Session>(io)->run(host, port, text);

    io.run();
    return 0;
}
