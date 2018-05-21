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

template<class SyncStream, class DynamicBuffer>
// can't convert std::string_view to boost::beast::string_view
http::response<http::empty_body> do_head_request(SyncStream& stream, DynamicBuffer& buffer, boost::beast::string_view target, boost::system::error_code& e)
{
    static_assert(boost::beast::is_sync_stream<SyncStream>::value, "SyncStream requirement not met.");
    static_assert(boost::asio::is_dynamic_buffer<DynamicBuffer>::value, "DynamicBuffer requirement not met.");

    if(target.empty())
        throw std::invalid_argument("target argument can't be empty.");

    http::request<http::empty_body> request;
    request.method(http::verb::head);
    request.target(target);
    request.version(version);
    request.set(http::field::host, host);
    request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(stream, request, e);
    if( e ){ return {}; }

    http::response_parser<http::empty_body> parser;
    parser.skip(true);                                                              // don't expect the body, finish after read the head.

    http::read(stream, buffer, parser, e);
    if( e ){ return {}; }

    return parser.release();
}

int main()
{
    boost::asio::io_context io;

    tcp::resolver resolver{io};
    tcp::resolver::results_type endpoints = resolver.resolve(tcp::resolver::query{host, port});
    tcp::socket socket{io};

    boost::asio::connect(socket, endpoints);

    boost::beast::flat_buffer buffer;
    boost::system::error_code e;
    http::response<http::empty_body> response = do_head_request(socket, buffer, boost::beast::string_view{target}, e);

    socket.shutdown(tcp::socket::shutdown_both, e);
    if(e && e != boost::system::errc::not_connected)
        throw boost::system::system_error{e};

    return 0;
}
