#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

constexpr short version = 11;

template<class SyncStream, class DynamicBuffer>
void do_server_head(SyncStream& stream, DynamicBuffer& buffer, boost::system::error_code& e)
{
    static_assert(boost::beast::is_sync_stream<SyncStream>::value, "SyncStream requirement not met.");
    static_assert(boost::asio::is_dynamic_buffer<DynamicBuffer>::value, "DynamicBuffer requirement not met.");

    static const std::string payload = "Hello World";

    http::request<http::string_body> request;
    http::read(stream, buffer, request, e);
    if( e ){ return; }

    http::response<http::string_body> response;
    response.version(version);
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);

    switch(request.method()){
    case http::verb::head:
    case http::verb::get:
    {
        response.result(http::status::ok);
        response.set(http::field::content_length, payload.size());

        if(request.method() == http::verb::get)
            response.body() = payload;

        break;
    }
    default:
    {
        response.result(http::status::bad_request);
        response.set(http::field::content_type, "text/plain");
        response.body() = "invalid request method ' " + request.method_string().to_string() + "'.";
        response.prepare_payload();
        break;
    }
    }

    http::write(stream, response, e);
    if( e ){ return; }
}

int main()
{
    boost::asio::io_context io;

    tcp::acceptor acceptor{io};
    tcp::socket socket{io};

    acceptor.accept(socket);

    boost::beast::flat_buffer buffer;
    boost::system::error_code e;
    do_server_head(socket, buffer, e);

    boost::system::error_code ec;
    socket.shutdown(tcp::socket::shutdown_both, ec);
    if(ec && ec != boost::system::errc::not_connected)
        throw boost::system::system_error{ec};

    return 0;
}
