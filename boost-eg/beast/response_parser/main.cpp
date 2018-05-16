#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

const std::string host = "www.reidblog.cn";
constexpr short port = 80;
const std::string target = "/blog/profile/";
constexpr short version = 11;




template<class sync_read_socket>
void print_response(sync_read_socket& socket){
    /* 1. static_assert
       2. boost::beast::is_sync_read_stream<T>::value */
    static_assert(boost::beast::is_sync_read_stream<sync_read_socket>::value, "sync_read requirement not met.\n");
    boost::beast::flat_buffer buffer;                                                                                                       // reading needs boost::beast::flat_buffer

    std::cout<< "response parser : " <<std::endl;
    http::response_parser<http::string_body> response_parser;                                                                          // boost::beast::http::response_parser<boost::beast::http::string_body>
    http::read_header(socket, buffer, response_parser);                                                                                  // boost::beast::http::read_header(stream, buffer, response_parser)
    std::cout<< response_parser.get() <<std::endl;                                                                                        /* boost::beast::http::response_parser::get()
                                                                                                                                                    response can be std::cout<< directly, but response_parser need response_parse::get() */

    std::cout<< "response : " <<std::endl;
    http::read(socket, buffer, response_parser);
    std::cout<< response_parser.get() <<std::endl;
}

int main()
{
    try{
        boost::asio::io_context io;

        tcp::resolver resolver(io);
        tcp::resolver::results_type endpoints = resolver.resolve(tcp::resolver::query(host, boost::lexical_cast<std::string>(port)));
        tcp::socket socket(io);
        boost::asio::connect(socket, endpoints);

        http::request<http::string_body> request(http::verb::get, target, version);                                                       // boost::beast::http::request<boost::beast::http::string_body>(boost::beast::http::verb::get, target, version)
        request.set(http::field::host, host);
        request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);                                                          // boost::beast::http::request<boost::beast::http::string_body>::set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING)
        http::write(socket, request);                                                                                                      // writing doesn't need buffer

        print_response<tcp::socket>(socket);

        boost::system::error_code e;
        socket.shutdown(tcp::socket::shutdown_both, e);                                                                                // boost::asio::ip::tcp::socket::shutdown(boost::asio::ip::tcp::socket::shutdown_both, boost::system::error_code )
        if(e && e != boost::system::errc::not_connected)                                                                                // boost::system::errc::not_connected happens frequestly, ignore it
            throw boost::system::system_error(e);                                                                                       // throw boost::system::system_error(boost::system::error_code)
    }
    catch(std::exception& e){
        std::cerr<< e.what() <<std::endl;
    }
    return 0;
}
