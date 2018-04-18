/*
boost::asio::io_context

boost::system::error_code
boost::system::system_error
    throw boost::system::system_error(boost::system::error_code)
boost::asio::error

boost::lexical_cast

boost::asio::buffer
boost::asio::connect

boost::asio::ip::address::from_string
boost::asio::ip::tcp::endpoint
boost::asio::ip::tcp::resolver
boost::asio::ip::tcp::resolver::query
boost::asio::ip::Tcp::resolver::resolve

boost::asio::ip::tcp::socket
boost::asio::ip::tcp::socket::remote_endpoint::address
boost::asio::ip::tcp::socket::receive

-------

std::exception::what
*/

#define BOOST_ERROR_CODE_HEADER_ONLY

#include <iostream>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>

using namespace std;

typedef boost::asio::ip::tcp TCP;
typedef boost::asio::io_context IO;
typedef boost::system::error_code ERROR;

int main(int argc, char* argv[])
{
    try{
        IO io_context;
        ERROR connection_error;

        // host -> ip address
        TCP::resolver resolver(io_context);
        TCP::resolver::results_type endpoints = resolver.resolve(
                    TCP::resolver::query("localhost", boost::lexical_cast<string>(8088)),
                    connection_error);
        if(connection_error){
            cout<<"host resolve fails."<<endl;
            return 0;
        }

        TCP::socket socket(io_context);
        boost::asio::connect(socket, endpoints, connection_error);
        if(connection_error){
            cout<<"connection fails."<<endl;
            return 0;
        }
        else
            cout<<socket.remote_endpoint().address()<<endl;

        vector<char> buf(socket.available()+1,0);

        socket.receive(boost::asio::buffer(buf));
        for(char c:buf)
            cout<<c;
        cout<<'\n';
    }
    catch(exception& e){
        cout<<e.what()<<endl;
    }
    return 0;
}

