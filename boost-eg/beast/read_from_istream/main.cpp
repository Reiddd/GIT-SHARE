#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#define BUFFER_SIZE 1024

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

constexpr short port = 80;
constexpr short version = 100;
const std::string target = "/";

template<bool isRequest, class Body>
void read_istream(std::istream& is, boost::beast::flat_buffer& buffer, http::message<isRequest, Body, http::fields>& message, boost::system::error_code& e){
    http::parser<isRequest, Body> parser{std::move(message)};

    do{
        if(is.rdbuf()->in_avail() > 0){
            auto const b = buffer.prepare(static_cast<std::size_t>(is.rdbuf()->in_avail()));
            buffer.commit(static_cast<std::size_t>(is.read_some(reinterpret_cast<char*>(b.data()),
                                                                  b.size())));
        }
        else if(buffer.size() == 0){
            if(!is.eof()){
                auto const b = buffer.prepare(BUFFER_SIZE);
                is.read(reinterpret_cast<char*>(b.data()), b.size());
                if(is.fail() && !is.eof()){
                    e = http::make_error_code(boost::system::errc::io_error);
                    return;
                }
            }
            else{
                parser.put_eof(e);
                if(e)
                    return;
                break;
            }
        }

        auto const bytes_used = parser.put(buffer.data(), e);
        if(e == http::error::need_more)
            e = {};
        if(e)
            return;

        buffer.consume(bytes_used);
    }while(!p.is_done());

    message = parser.release();
}

int main()
{


    return 0;
}
