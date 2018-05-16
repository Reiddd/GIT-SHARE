#include <iostream>
#include <time.h>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::tcp;

std::string make_datetime_string(){
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

int main()
{
    try{
        boost::asio::io_context io;
        boost::asio::deadline_timer t(io, boost::posix_time::seconds(2));
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8100));
        tcp::iostream stream;

        acceptor.accept(stream.socket());

        while(true){
            t.wait();
            stream << make_datetime_string() << std::endl;              // std::endl will flush the iostream
            t.expires_at(t.expires_at() + boost::posix_time::seconds(2));
        }
    }
    catch(std::exception& e){
            std::cerr<< e.what() <<std::endl;
    }

    return 0;
}
