#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

constexpr char host[] = "www.reidblog.cn";
constexpr char port[] = "80";
constexpr char target[] = "/blog/";
constexpr short version = 11;

template<class SyncStream, class DynamicBuffer, class Body, class Allocator>
void send_expect_100_continue(SyncStream& stream, DynamicBuffer& buffer, http::request<Body, http::basic_fields<Allocator>>& request, boost::system::error_code& e){
    static_assert(boost::beast::is_sync_stream<SyncStream>::value, "SyncStream requirements not met.");
    static_assert(boost::asio::is_dynamic_buffer<DynamicBuffer>::value, "DynamicBuffer requirements not met.");

    request.set(http::field::expect, "100-continue");

    http::request_serializer<Body, http::basic_fields<Allocator>> serializer{request};

    http::write_header(stream, serializer, e);
    if( e ){ return; }

    {
        http::response<http::string_body> response;
        http::read(stream, buffer, response, e);
        if( e ){ return; }

        if(response.result() != http::status::continue_){ return; }
    }

    http::write(stream, serializer, e);
}

int main()
{
    boost::asio::io_context io;

    tcp::resolver resolver{io};
    tcp::resolver::results_type endpoints = resolver.resolve(tcp::resolver::query(host, port));
    tcp::socket socket{io};
    boost::asio::connect(socket, endpoints);

    http::request<http::string_body> request{http::verb::get, target, version};
    request.set(http::field::host, host);
    request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    boost::beast::flat_buffer buffer;
    boost::system::error_code e;
    send_expect_100_continue(socket, buffer, request, e);

    http::response<http::string_body> response;
    http::read(socket, buffer, response);
    std::cout<< response <<std::endl;

    boost::system::error_code ec;
    socket.shutdown(tcp::socket::shutdown_both, ec);
    if(ec && ec != boost::system::errc::not_connected)
        throw boost::system::system_error(ec);

    return 0;
}
