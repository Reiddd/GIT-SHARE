#include <iostream>
#include <boost/asio.hpp>

using namespace std;

typedef boost::asio::ip::tcp TCP;
typedef boost::asio::io_service IO;

int main()
{
    try{
        cout<<"server start"<<endl;

        IO io_service;

        TCP::acceptor acceptor(io_service, TCP::endpoint(TCP::v4(), 8000));

        while(true){
            TCP::socket socket(io_service);
            acceptor.accept(socket);

            cout<< "connection established with client: "
                << socket.remote_endpoint().address()
                << endl;

            string response = "you are communicating with " + socket.local_endpoint().address().to_string();
            socket.send(boost::asio::buffer(response));
        }
    }
    catch(exception& e){
            cout<<e.what()<<endl;
    }

    return 0;
}

