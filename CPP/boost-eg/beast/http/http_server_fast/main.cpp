#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <memory>
#include <chrono>
// #include <experimental/optional>  for std::optional
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/filesystem.hpp>

using     tcp  = boost::asio::ip::tcp;
namespace ip   = boost::asio::ip;
namespace http = boost::beast::http;

constexpr char host[]     = "127.0.0.1";
constexpr char port[]     = "8099";
constexpr char doc_root[] = "/";

// --------------

boost::beast::string_view
mime_type(boost::beast::string_view path)
{
    using boost::beast::iequals;

    auto const ext = [&path]
    {
        auto const pos = path.rfind(".");
        if(pos == boost::beast::string_view::npos)
            return boost::beast::string_view{};
        return path.substr(pos);
    }();

    if(iequals(ext, ".htm" )) return "text/html";
    if(iequals(ext, ".html")) return "text/html";
    if(iequals(ext, ".php" )) return "text/html";
    if(iequals(ext, ".css" )) return "text/css";
    if(iequals(ext, ".txt" )) return "text/plain";
    if(iequals(ext, ".js"  )) return "application/javascript";
    if(iequals(ext, ".json")) return "application/json";
    if(iequals(ext, ".xml" )) return "application/xml";
    if(iequals(ext, ".swf" )) return "application/x-shockwave-flash";
    if(iequals(ext, ".flv" )) return "video/x-flv";
    if(iequals(ext, ".png" )) return "image/png";
    if(iequals(ext, ".jpe" )) return "image/jpeg";
    if(iequals(ext, ".jpeg")) return "image/jpeg";
    if(iequals(ext, ".jpg" )) return "image/jpeg";
    if(iequals(ext, ".gif" )) return "image/gif";
    if(iequals(ext, ".bmp" )) return "image/bmp";
    if(iequals(ext, ".ico" )) return "image/vnd.microsoft.icon";
    if(iequals(ext, ".tiff")) return "image/tiff";
    if(iequals(ext, ".tif" )) return "image/tiff";
    if(iequals(ext, ".svg" )) return "image/svg+xml";
    if(iequals(ext, ".svgz")) return "image/svg+xml";
    return "application/text";
}


class http_work
{
public:
    http_work(http_work const&) = delete;
    http_work& operator=(http_work const&) = delete;

    http_work(tcp::acceptor& acceptor, std::string& doc_root)
        :acceptor_{acceptor},
          doc_root_{doc_root} {}

    void start(){
        accept();
        check_deadline();
    }

private:
typedef fields_alloc<char>                                                                               alloc_t;
typedef http::basic_dynamic_body< boost::beast::flat_static_buffer<1024 * 1024> >                        request_body_t;
typedef boost::optional< http::request_parser<request_body_t, alloc_t> >                                 optional_request_parser;
typedef boost::optional< http::response< http::string_body, http::basic_fields<alloc_t> > >              optional_string_response;
typedef boost::optional< http::response< http::file_body  , http::basic_fields<alloc_t> > >              optional_file_response;
typedef boost::optional< http::response_serializer< http::string_body, http::basic_fields<alloc_t> > >   optional_string_serializer;
typedef boost::optional< http::response_serializer< http::file_body  , http::basic_fields<alloc_t> > >   optional_file_serializer;
typedef boost::asio::basic_waitable_timer<std::chrono::steady_clock>                                     steady_timer;

    tcp::acceptor&                         acceptor_;
    tcp::socket                            socket_{acceptor_.get_executor().context()};
    std::string                            doc_root_;
    boost::beast::flat_static_buffer<8192> buffer_;
    alloc_t                                alloc_{8192};
    optional_request_parser                parser_;
    optional_string_response               string_response_;
    optional_string_serializer             string_serializer_;
    optional_file_response                 file_response_;
    optional_file_serializer               file_serializer_;
    steady_timer                           request_deadline_{acceptor_.get_executor().context(), std::chrono::steady_clock::time_point::max};

    void accept(){
    // clean previous connection.
        boost::system::error_code e;
        socket_.close(e);
        buffer_.consume(buffer_.size());

        acceptor_.async_accept(socket_,
                               [this](boost::system::error_code e){
            if(e)
                this->accept();
            else{
                request_deadline_.expires_after(std::chrono::seconds(60));
                this->read_request();
            }
        });
    }


    void read_request(){
    // on each read, the parser needs to be destroyed and reconstructed. boost::optional achieves that.
        parser_.emplace(std::piecewise_construct, std::make_tuple(), std::make_tuple(alloc_t));

        http::async_read(socket_, buffer_, parser_,
                         [this](boost::beast::error_code e, std::size_t bytes_transferred){
            if(e)
                this->accept();
            else
                this->process_request(p.get());
        });
    }


    void process_request(http::request<request_body_t, http::basic_fields<alloc_t>> const& request){
        switch(request.method()){
        case http::verb::get:
            this->send_file(request.target());
            break;
        default:
            this->send_bad_response(http::status::bad_request,
                                    "Invalid request-method '" + request.method_string().to_string() + "'.\r\n");
            break;
        }
    }


    void send_bad_response(http::status status, std::string const& error){
        string_response_.emplace(std::piecewise_construct,
                                 std::make_tuple(),
                                 std::make_tuple(alloc_t));
        string_response_.result(status);
        string_response_.keep_alive(false);
        string_response_.set(http::field::server      , BOOST_BEAST_VERSION_STRING);
        string_response_.set(http::field::content_type, "text/plain");
        string_response_.body() = error;
        string_response_.prepare_payload();

        string_serializer_.emplace(*string_response_);

        http::async_write( socket_,
                          *string_serializer_,
                          [this](boost::beast::error_code e, std::size_t bytes_transferred){
            socket_.shutdown(tcp::socket::shutdown_send, e);
            string_response_.reset();
            string_serializer_.reset();
            this->accept();
        });
    }


    void send_file(boost::beast::string_view target){
        if(target.empty() || target.front() != '/' || target.find("..") != std::string::npos){
            send_bad_response(http::status::not_found, "File not found\r\n");
            return;
        }

        std::string full_path = doc_root_;
        full_path.append(target.data(), target.size());

        http::file_body::value_type file;
        boost::beast::error_code    e;
        file.open(full_path.c_str(), boost::beast::file_mode::read, e);
        if(e){
            send_bad_response(http::status::not_found, "File not found\r\n");
            return;
        }

        file_response_.emplace(std::piecewise_construct,
                               std::make_tuple(),
                               std::make_tuple(alloc_t));
        file_response_.result(http::status::ok);
        file_response_.keep_alive(false);
        file_response_.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        file_response_.set(http::field::content_type, mime_type(target.to_string()));
        file_response_.body() = file;
        file_response_.prepare_payload();

        file_serializer_.emplace(*file_response_);

        http::async_write(socket_,
                          *file_serializer_,
                          [this](boost::system::error_code e, std::size_t bytes_transferred){
            socket_.shutdown(tcp::socket::shutdown_send, e);
            file_response_.reset();
            file_serializer_.reset();
            this->accept();
        });
    }


    void check_deadline(){
        if(request_deadline_.expiry() <= std::chrono::steady_clock::now()){
            boost::beast::error_code e;
            socket_.close(e);

            request_deadline_.expires_at(std::chrono::steady_clock::time_point::max);
        }

        request_deadline_.async_wait([this](boost::beast::error_code){
            this->check_deadline();
        });
    }
};

int main()
{
    try{
        int  num_workers = (int)(std::chrono::steady_clock::now().time_since_epoch().count()) % 10;
        bool spin        = (int)(std::chrono::steady_clock::now().time_since_epoch().count()) % 2 == 0;

        boost::asio::io_context io;
        tcp::acceptor           acceptor{io, {host, port}};

        std::list<http_work> workers;
        for(int i=0; i<num_workers; i++){
            workers.emplace_back(acceptor, doc_root);
            workers.back().start();
        }

        if(spin)
            for( ; ; ) io.poll();
        else
            io.run();
    }
    catch(std::exception& e){
        std::cerr<< e.what() <<std::endl;
    }

    return 0;
}
