#include <iostream>
#include <stdlib.h>
#include <memory>
#include <string>
#include <thread>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>     // boost::beast::iequals
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;


// return a reasonable mime type based on the extension of the file
boost::beast::string_view mime_type(boost::beast::string_view path){
    using boost::beast::iequals;

    const boost::beast::string_view ext = [&path]{
        auto const pos = path.rfind(".");                                   // boost::beast::string_view::rfind( target_string )
        if(pos == boost::beast::string_view::npos)                          // boost::beast::string_view::npos
            return boost::beast::string_view{};
        return path.substr(pos);
    }();

    if(iequals(ext, ".htm"))  return "text/html";                           // boost::beast::iequals( str1, str2 )
    if(iequals(ext, ".html")) return "text/html";
    if(iequals(ext, ".php"))  return "text/html";
    if(iequals(ext, ".css"))  return "text/css";
    if(iequals(ext, ".txt"))  return "text/plain";
    if(iequals(ext, ".js"))   return "application/javascript";
    if(iequals(ext, ".json")) return "application/json";
    if(iequals(ext, ".xml"))  return "application/xml";
    if(iequals(ext, ".swf"))  return "application/x-shockwave-flash";
    if(iequals(ext, ".flv"))  return "video/x-flv";
    if(iequals(ext, ".png"))  return "image/png";
    if(iequals(ext, ".jpe"))  return "image/jpeg";
    if(iequals(ext, ".jpeg")) return "image/jpeg";
    if(iequals(ext, ".jpg"))  return "image/jpeg";
    if(iequals(ext, ".gif"))  return "image/gif";
    if(iequals(ext, ".bmp"))  return "image/bmp";
    if(iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
    if(iequals(ext, ".tiff")) return "image/tiff";
    if(iequals(ext, ".tif"))  return "image/tiff";
    if(iequals(ext, ".svg"))  return "image/svg+xml";
    if(iequals(ext, ".svgz")) return "image/svg+xml";
    return "application/text";
}


// append an HTTP rel-path to a local filesystem path
std::string path_cat(boost::beast::string_view base, boost::beast::string_view path){
    if(base.empty())
        return path.to_string();                                                            // boost::beast::string_view::to_string()

    std::string result = base.to_string();
#ifdef BOOST_MSVC
    char constexpr path_seperator = '\\';
    if(result.back() == path_seperator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());                                                /* void std::string::append(char* , std::size_t )
                                                                                               char* std::string::data()                        */
    for(char& c : result)
        if(c == '/')
            c = path_seperator;
#else
    char constexpr path_seperator = '/';
    if(result.back() == path_seperator)
        result.resize(result.size() - 1);                                                     // std::string::resize(std::size_t )
    result.append(path.data(), path.size());
#endif
    return result;
}


template<class Body, class Allocator, class Send>
void handle_request(boost::beast::string_view doc_root, http::request<Body, http::basic_fields<Allocator>>&& request, Send&& send){

// std::function<http::response<http::string_body>(boost::beast::string_view)> bad_request = ...
    auto const bad_request =
    [&request](boost::beast::string_view why){
        http::response<http::string_body> response{http::status::bad_request, request.version()};
        response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        response.set(http::field::content_type, "text/html");
        response.keep_alive(request.keep_alive());
        response.body() = why.to_string();

        response.prepare_payload();
        return response;
    };

// std::function<http::response<http::string_body>(boost::beast::string_view)> not_found = ...
    auto const not_found =
    [&request](boost::beast::string_view target){
        http::response<http::string_body> response{http::status::not_found, request.vesion()};
        response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        response.set(http::field::content_type, "text/html");
        response.keep_alive(request.keep_alive());
        response.body() = "The resource '" + target.to_string() + "' was not found.";

        response.prepare_payload();
        return response;
    };

//std::function<http::response<http::string_body>(boost::beast::string_view)> server_error = ...
    auto const server_error =
    [&request](boost::beast::string_view what){
        http::response<http::string_body> response{http::status::internal_server_error, request.version()};
        response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        response.set(http::field::content_type, "text/html");
        response.keep_alive(request.keep_alive());
        response.body() = "An error occurred: '" + what.to_string() + "'";

        response.prepare_payload();
        return response;
    };

// filter out illegal method
    if(request.method() != http::verb::get && request.method() != http::verb::head)
        return send(bad_request("Unknown HTTP-method"));

// filter out illegal target
    if(request.target().empty() || request.target().front() != '/' || request.target().find("..") != boost::beast::string_view::npos)
        return send(bad_request("Illegal request-target"));

// build the path
    std::string path = path_cat(doc_root, request.target());
    if(request.target().back() == '/')
        path.append("index.html");

// attempt to open the file
    boost::beast::error_code e;
    http::file_body::value_type body;
    body.open(patn.c_str(), boost::beast::file_mode::scan, e);

// if the file doesn't exist
    if(e == boost::system::errc::no_such_file_or_directory)
        return send(not_found(request.target()));

// handle other errors
    if(e)
        return send(server_error(e.message()));

// cache the size of body
    auto const size = body.size();

// response to the HEAD request
    if(request.method() == http::verb::head){
        http::response<http::empty_body> response{http::status::ok, request.version()};
        response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        response.set(http::field::content_type, mime_type(path));
        response.prepare_payload();
        response.keep_alive(request.keep_alive());
        return send(std::move(response));
    }

// response to the GET request
    http::response<http::file_body> response{std::piecewise_construct, std::make_tuple(std::move(body)), std::make_tuple(http::status::ok, request.version())};
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_type, mime_type(path));
    response.prepare_payload();
    response.keep_alive(request.keep_alive());

    return send(std::move(response));
}


void fail(boost::system::error_code e, char const* what){
    std::cerr<< what << ": " << e.message() << std::endl;
}


template<class Stream>
struct Send_lambda{
    Stream& stream_;
    bool& close_;
    boost::system::error_code& e_;

    explicit Send_lambda(Stream& stream, bool& close, boost::system::error_code& e)
        : stream_(stream),
          close_(close),
          e_(e) {}

    template<bool isRequest, class Body, class Fields>
    void operator()(http::message<isRequest, Body, Fields>&& msg) const{
        close_ = msg.need_eof();

        http::serializer<isReuqest, Body, Fields> sr{msg};
        http::write(stream_, sr, e_);
    }
};


void do_session(tcp::socket& socket, std::string const& doc_root){
    bool close = false;
    boost::system::error_code e;

    boost::beast::flat_buffer buffer;

    send_lambda<tcp::socket> lambda{socket, close, e};

    for( ; ; ){
        http::request<http::string_body> request;
        http::read(socket, buffer, request, e);
        if(e == http::error::end_of_stream)
            break;
        if(e)
            return fail(e, "read");

        handle_request(doc_root, std::move(request), lambda);
        if(e)
            return fail(e, "write");
        if(close)
            break;
    }

    socket.shutdown(tcp::socket::shutdown_send, e);
}

int main()
{
    try{
        auto const address = boost::asio::ip::address("127.0.0.1");
        auto const port = static_cast<unsigned short>(std::atoi(8080));
        std::string const doc_root = "~/Documents/";

        boost::asio::io_context io{1};

        tcp::acceptor acceptor{io, {address, port}};
        for( ; ; ){
            tcp::socket socket{io};
            acceptor.accept(socket);

            std::thread{std::bind(&do_session, std::move(socket), doc_root)}.detach();
        }
    }
    catch(const std::exception& e){
        std::cerr<< "Error: " << e.what() <<std::endl;
    }

    return 0;
}
