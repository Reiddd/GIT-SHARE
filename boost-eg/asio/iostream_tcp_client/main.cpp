#include <iostream>
#include <string>                                           // std::getline(stream, container)
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::tcp;

int main()
{
    boost::asio::io_context io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));

    try{
        tcp::iostream stream(tcp::resolver::query("localhost",                                  // tcp::iostream(tcp::resolver::query(string host, string port))
                                                   boost::lexical_cast<std::string>(8100)));     // tcp::resolver::resolve(tcp::resolver::query )

        if(!stream)
            std::cerr<< stream.error().message() <<std::endl;
        else{
            std::string str;
            while(true){
                t.wait();
                std::getline(stream, str);
                std::cout<< str << std::endl;
                t.expires_at(t.expires_at() + boost::posix_time::seconds(1));
            }
        }
    }
    catch(std::exception& e){
            std::cerr<< e.what() <<std::endl;
    }

    return 0;
}
