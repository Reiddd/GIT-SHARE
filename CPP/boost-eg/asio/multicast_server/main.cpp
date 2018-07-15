#include <iostream>
#include <sstream>
#include <boost/asio.hpp>

constexpr short multicast_port = 30001;
constexpr int max_message_count = 100;

using boost::asio::ip::udp;

class Sender
{
public:
    Sender(boost::asio::io_context& io, const boost::asio::ip::address& multicast_address)
        : endpoint_(multicast_address, multicast_port),
          socket_(io, endpoint_.protocol()),
          timer_(io),
          message_count(0)
    {
        do_send();
    }

private:
    void do_send(){
        std::stringstream ss;
        ss << "Message " << message_count++;
        message_ = ss.str();

        socket_.async_send_to(boost::asio::buffer(message_),
                                endpoint_,
                                [this](boost::system::error_code e, std::size_t ){
                                    if(!e && message_count < max_message_count)
                                        do_timeout();
                                });
    }

    void do_timeout(){
        timer_.expires_after(std::chrono::seconds(1));
        timer_.async_wait([this](boost::system::error_code e){
                                if(!e)
                                    do_send();
                            });
    }

    udp::endpoint endpoint_;
    udp::socket socket_;
    boost::asio::steady_timer timer_;
    int message_count;
    std::string message_;
};

int main()
{
    try{
        boost::asio::io_context io;
        Sender s(io, boost::asio::ip::make_address("255.255.255.255"));
        io.run();
    }
    catch(std::exception& e){
        std::cerr<< "Exception: " << e.what() <<std::endl;
    }

    return 0;
}
