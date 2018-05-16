#include <iostream>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/version.hpp>

#define BUFFER_FIXED_SIZE 512

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

const std::string host = "www.reidblog.cn";
constexpr short port = 80;
const std::string target = "/blog/profile/";
constexpr short version = 11;

template<class SyncReadSocket, class DynamicBuffer>
void read_with_fixedSizeBuffer(SyncReadSocket& socket, DynamicBuffer& buffer){
    static_assert(boost::beast::is_sync_read_stream<SyncReadSocket>::value, "sync read stream requirement not met.\n");
    boost::system::error_code e;

    http::response_parser<http::buffer_body> response_parser;
    http::read_header(socket, buffer, response_parser, e);
    if(e){ return; }

    while(!response_parser.is_done()){
        char buf[BUFFER_FIXED_SIZE];
        response_parser.get().body().data = buf;
        response_parser.get().body().size = sizeof(buf);
        http::read(socket, buffer, response_parser, e);

        if(e == http::error::need_buffer)
            e.assign(0, e.category());
        if(e)
            return;

        std::cout.write(buf, sizeof(buf) - response_parser.get().body().size);
    }
}

int main()
{
    boost::asio::io_context io;

    tcp::resolver resolver(io);
    tcp::resolver::results_type endpoints = resolver.resolve(tcp::resolver::query(host, boost::lexical_cast<std::string>(port)));
    tcp::socket socket(io);
    boost::asio::connect(socket, endpoints);

    http::request<http::string_body> request(http::verb::get, target, version);
    request.set(http::field::host, host);
    request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    http::write(socket, request);

    boost::beast::flat_buffer buffer;
    read_with_fixedSizeBuffer<tcp::socket, boost::beast::flat_buffer>(socket, buffer);

    boost::system::error_code e;
    socket.shutdown(tcp::socket::shutdown_both, e);
    if(e && e != boost::system::errc::not_connected)
        throw boost::system::system_error(e);

    return 0;
}
