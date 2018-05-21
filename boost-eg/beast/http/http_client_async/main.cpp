#include <iostream>
#include <memory>                     // std::make_shared<T> || std::enable_shared_from_this<T>
#include <functional>                   // std::placeholders
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

using       tcp  = boost::asio::ip::tcp;
namespace http = boost::beast::http;

const      std::string host     = "www.reidblog.cn";
const      std::string target   = "/blog/";
constexpr int         port     = 80;
constexpr int         version  = 11;

namespace exception_happened{
    void fail(boost::system::error_code e, char const* what){
        std::cerr<< what << ": " << e.message() <<std::endl;
    }
}

class Session: public std::enable_shared_from_this<Session>
{
public:
    explicit Session(boost::asio::io_context& io, const int id)
        : ID(id),
          resolver_(io),
          socket_(io) {}


    void run(const std::string& host, const std::string& port = "80", const std::string& target = "/", const int version = 11){
        request_.version(version);                                                                                                                                    // request.version(version)
        request_.method(http::verb::get);                                                                                                                            // request.method(http::verb::method)
        request_.target(target);                                                                                                                                      // request.target(target)
        request_.set(http::field::host, host);
        request_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        resolver_.async_resolve(tcp::resolver::query(host, port),                                                                                                    // void tcp::resolver::async_resolve(tcp::resolver::query, handle)
                                 std::bind(&Session::on_resolve, shared_from_this(), std::placeholders::_1, std::placeholders::_2));                               // T* std::enable_shared_from_this<T>::shared_from_this()
    }


    void on_resolve(boost::system::error_code e, tcp::resolver::results_type endpoints){                                                                          // void async_resolve_handle(boost::system::error_code e, tcp::resolver::results_type endpoints)
        if(e){ return exception_happened::fail(e, "resolve"); }

        boost::asio::async_connect(socket_, endpoints, std::bind(&Session::on_connect, shared_from_this(), std::placeholders::_1));                             // void boost::asio::async_connect(socket, endpoints, handle)
    }


    void on_connect(boost::system::error_code e){                                                                                                                 // void async_connect_handle(boost::system::error_code e)
        if(e){ return exception_happened::fail(e, "connect"); }

        http::async_write(socket_, request_, std::bind(&Session::on_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));                    // void http::async_write(stream, request, handle)
    }


    void on_write(boost::system::error_code e, std::size_t bytes_transferred){                                                                                    // void async_write_handle(boost::system::error_code e, std::size_t bytes_read)
        boost::ignore_unused(bytes_transferred);                                                                                                                  // void boost::ignore_unused(std::size_t bytes_read)

        if(e){ return exception_happened::fail(e, "write"); }

        http::async_read(socket_, buffer_, response_, std::bind(&Session::on_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));         // void http::async_read(stream, buffer, response, handle)
    }


    void on_read(boost::system::error_code e, std::size_t bytes_transferred){                                                                                   // void async_read_handle(boost::system::error_code e, std::size_t bytes_read)
        boost::ignore_unused(bytes_transferred);                                                                                                                 // void boost::ignore_unused(std::size_t bytes_read)

        if(e){ return exception_happened::fail(e, "read"); }

    // std::cout<< response_ <<std::endl;
        std::cout<< ID << "finished" <<std::endl;

        socket_.shutdown(tcp::socket::shutdown_both, e);
        if(e && e != boost::system::errc::not_connected){ return exception_happened::fail(e, "shutdown"); }
    }

private:
    int                                 ID;
    tcp::resolver                       resolver_;
    tcp::socket                         socket_;
    boost::beast::flat_buffer           buffer_;
    http::request<http::empty_body>  request_;
    http::response<http::string_body> response_;
};

int main()
{
    boost::asio::thread_pool pool(4);

    for(int i=0; i<100; i++)
        boost::asio::post(pool, [=](){                                                                                                                              // boost::asio::post(thread_pool, function)
            boost::asio::io_context io;
            std::make_shared<Session>(io, i)->run(host, boost::lexical_cast<std::string>(port), target, version);
            io.run();
        });

    pool.join();                                                                                                                                                    // boost::asio::thread_pool::join();
    return 0;
}
