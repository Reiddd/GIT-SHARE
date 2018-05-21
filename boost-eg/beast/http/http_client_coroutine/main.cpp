#include <iostream>
#include <stdlib.h>
#include <functional>
#include <memory>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/yield.hpp>     // reenter yield
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

constexpr char host[] = "www.reidblog.cn";
constexpr char port[] = "80";
constexpr char target[] = "/blog/";
constexpr short version = 11;

namespace exception_happened{
void fail(boost::system::error_code e, const char* what){
    std::cerr<< what << ": " << e.message() <<std::endl;
}
}

class Session: public std::enable_shared_from_this<Session>, public boost::asio::coroutine
{
public:
    explicit Session(boost::asio::io_context& io)
        : resolver_(io),
          socket_(io) {}

    void operator()(const char* host, const char* port, const char* target, const int version){
        request_.method(http::verb::get);
        request_.target(target);
        request_.version(version);
        request_.set(http::field::host, host);
        request_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        reenter(this) for( ; ; )
        {
            yield resolver_.async_resolve(tcp::resolver::query(host, port), std::bind(&Session::async_resolve_handle, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
        }
    }

private:
    void async_resolve_handle(boost::system::error_code e, tcp::resolver::results_type endpoints){
        if(e){ return exception_happened::fail(e, "resolve"); }

        boost::asio::async_connect(socket_, endpoints, std::bind(&Session::async_connect_handle, shared_from_this(), std::placeholders::_1));
    }


    void async_connect_handle(boost::system::error_code e){
        if(e){ return exception_happened::fail(e, "connect"); }

        http::async_write(socket_, request_, std::bind(&Session::async_write_handle, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    }

    void async_write_handle(boost::system::error_code e, std::size_t bytes_read){
        boost::ignore_unused(bytes_read);

        if(e){ return exception_happened::fail(e, "write"); }

        http::async_read_header(socket_, buffer, response_parser_, std::bind(&Session::async_read_handle, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    }


    void async_read_handle(boost::system::error_code e, std::size_t bytes_read){
        boost::ignore_unused(bytes_read);

        if(e){ return exception_happened::fail(e, "read"); }

        std::cout<< response_parser_.get() <<std::endl;

        socket_.shutdown(tcp::socket::shutdown_both, e);
        if(e && e != boost::system::errc::not_connected)
            throw boost::system::system_error(e);
    }

    tcp::resolver resolver_;
    tcp::socket socket_;
    boost::beast::flat_buffer buffer;
    http::request<http::empty_body> request_;
    http::response_parser<http::string_body> response_parser_;
};

int main()
{
    boost::asio::io_context io;
    std::make_shared<Session>(io)->operator ()(host, port, target, version);

    io.run();
    return 0;
}
