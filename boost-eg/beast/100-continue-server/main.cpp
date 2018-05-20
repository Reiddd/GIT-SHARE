#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

template<class SyncStream, class DynamicBuffer>
void receive_except_100_continue(SyncStream& stream, DynamicBuffer& buffer, boost::system::error_code& e){
    static_assert(boost::beast::is_sync_stream<SyncStream>::value, "SyncStream requirement not met.");
    static_assert(boost::asio::is_dynamic_buffer<DynamicBuffer>::value, "DynamicBuffer requirement not met.");

    http::request_parser<http::string_body> parser;

    http::read_header(stream, buffer, parser, e);
    if( e ){ return; }

    if(parser.get()[http::field::expect] == "100-continue"){
        http::response<http::empty_body> response;
        response.version(11);
        response.result(http::status::continue_);
        response.set(http::field::server, BOOST_BEAST_VERSION_STRING);

        http::write(stream, response, e);
        if( e ){ return; }
    }

    http::read(stream, buffer, parser.base(), e);
}

int main()
{
    boost::asio::io_context io;

    tcp::acceptor acceptor{io};
    tcp::socket socket{io};
    acceptor.accept(socket);

    boost::beast::flat_buffer buffer;
    boost::system::error_code e;
    receive_expect_100_continue(socket, buffer, e);

    return 0;
}
