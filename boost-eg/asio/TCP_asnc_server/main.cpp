/*
boost::enable_shared_from_this
boost::shared_ptr
boost::bind

boost::system::error_code

boost::asio::io_context
boost::asio::connect
boost::asio::buffer
boost::asio::placeholders
    boost::asio::placeholders::error
    boost::asio::placeholders::bytes_transferred

boost::ip::tcp::resolver
boost::asio::ip::tcp::endpoint
boost::asio::ip::address::from_string
boost::asio::ip::tcp::acceptor::async_accept
*/
#define BOOST_ERROR_CODE_HEADER_ONLY

#include <iostream>
#include <ctime>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using namespace std;

typedef boost::asio::ip::tcp TCP;
typedef boost::asio::io_context IO;
typedef boost::system::error_code ERROR;

// -------

string make_datetime_string(){
    time_t now = time(0);
    return ctime(&now);
}

class tcp_connection:
        public boost::enable_shared_from_this<tcp_connection>
{
public:
    static boost::shared_ptr<tcp_connection> create(IO& io_context){
        return boost::shared_ptr<tcp_connection>(new tcp_connection(io_context));
    }

    TCP::socket& socket(){
        return socket_;
    }

    void start(){
        message_ = make_datetime_string();

        boost::asio::async_write(socket_,
                                 boost::asio::buffer(message_),
                                 boost::bind(&tcp_connection::handle_write,
                                             shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }

private:
    TCP::socket socket_;
    string message_;

    tcp_connection(IO& io_context): socket_(io_context){}

    void handle_write(const ERROR& , size_t){}
};

class tcp_server
{
public:
    tcp_server(IO& io_context):
        acceptor_(io_context, TCP::endpoint(TCP::v4(), 8088))
    {
        start_accept();
    }

private:
    TCP::acceptor acceptor_;

    void start_accept(){
        boost::shared_ptr<tcp_connection> new_connection = tcp_connection::create(acceptor_.get_executor().context());

        acceptor_.async_accept(new_connection->socket(),
                               boost::bind(&tcp_server::handle_accept,
                                           this,
                                           new_connection,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(boost::shared_ptr<tcp_connection> new_connection, const ERROR& error){
        if(!error){
            new_connection->start();
        }
        start_accept();
    }
};

int main()
{
    try{
        IO io_context;
        tcp_server server(io_context);
        io_context.run();
    }
    catch(exception& e){
        cout<<e.what()<<endl;
    }
    return 0;
}

