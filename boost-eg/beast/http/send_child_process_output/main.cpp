#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

using     tcp  = boost::asio::ip::tcp;
namespace http = boost::beast::http;

template<class SyncReadStream, class SyncWriteStream>
void send_cgi_infomation(SyncReadStream& input, SyncWriteStream& output, boost::system::error_code& e)
{
    static_assert(boost::beast::is_sync_read_stream<SyncReadStream>::value  , "SyncReadStream requirement not met.");
    static_assert(boost::beast::is_sync_write_stream<SyncWriteStream>::value, "SyncWriteStream requirement not met.");

    http::response<http::buffer_body> response;
    response.result(http::status::ok);
    response.version(11);
    response.set(http::field::server           , BOOST_BEAST_VERSION_STRING);
    response.set(http::field::transfer_encoding, "chunked");
    response.body().data = nullptr;                                                                                     // buffer.data
    response.body().more = true;                                                                                        // buffer.more, true if there may be incoming data later.

    http::response_serializer<http::buffer_body, http::fields> serializer{response};
    http::write_header(output, serializer, e);
    if(e){ return; }

    do{
        char buffer[2048];
        auto bytes_transferred = input.read_some(boost::asio::buffer(buffer, sizeof(buffer)), e);

        if(e == boost::asio::error::eof){
            e = {};
            response.body().data = nullptr;
            response.body().more = false;
        }
        else{
            if(e){ return; }

            response.body().data = buffer;
            response.body().size = bytes_transferred;
            response.body().more = true;

            http::write(output, serializer, e);
            if(e == http::error::need_buffer){ e = {}; continue; }                                                      //
            if(e){ return; }
        }
    }while(!serializer.is_done())
}

int main()
{
    return 0;
}
