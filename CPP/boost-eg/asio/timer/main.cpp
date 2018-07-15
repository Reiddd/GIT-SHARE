#include <iostream>
#include <future>                                           // packaged_task
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <boost/date_time/posix_time/posix_time.hpp>

#define BOOST_ERROR_CODE_HEADER_ONLY

using namespace std;

// function for block 3
void print(const boost::system::error_code& , boost::asio::deadline_timer* t, int* count){
    if(*count < 5){
        cout<< *count <<endl;
        (*count)++;

        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        t->async_wait(boost::bind(print, boost::placeholders::_1, t, count));
    }
}

// class for block 4
class Printer{
public:
    Printer(boost::asio::io_context& io)
        : strand_(io),
         timer1_(io, boost::posix_time::seconds(1)) ,
         timer2_(io, boost::posix_time::seconds(1)),
         count_(0)
    {
        timer1_.async_wait(boost::asio::bind_executor(strand_,
                                                         boost::bind(&Printer::print1, this)));
        timer2_.async_wait(boost::asio::bind_executor(strand_,
                                                         boost::bind(&Printer::print2, this)));
    }

    ~Printer(){
        cout<< "finally, count == " << count_ <<endl;
    }

    void print1(){
        if(count_ < 10){
            cout<< "Timer 1 : " << count_ <<endl;
            ++count_;
            timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
            timer1_.async_wait(boost::asio::bind_executor(strand_,
                                                             boost::bind(&Printer::print1, this)));
        }
    }

    void print2(){
        if(count_ < 10){
            cout<< "Timer 2 : " << count_ <<endl;
            ++count_;
            timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
            timer2_.async_wait(boost::asio::bind_executor(strand_,
                                                             boost::bind(&Printer::print2, this)));
        }
    }

private:
    boost::asio::io_context::strand strand_;
    boost::asio::deadline_timer timer1_;
    boost::asio::deadline_timer timer2_;
    int count_;
};

int main()
{
    boost::asio::deadline_timer* t;

// 1. basic usage of boost::asio::deadline_timer, synchronously
    {
        boost::asio::io_context io;
        t = new boost::asio::deadline_timer(io, boost::posix_time::seconds(5));
        t->wait();
        cout<< "synchronously wait for 5 seconds !\n" <<endl;

        delete t;
    }

// 2. boost::asio::deadline_timer, asynchronously, used with boost::asio::io_service::run
    {
        boost::asio::io_context io;
        // packaged_task<void(boost::system::error_code&)> task([](const boost::system::error_code& ){ cout<< "this shows second\n" <<endl; });
        t = new boost::asio::deadline_timer(io);
        t->expires_from_now(boost::posix_time::seconds(5));
        t->async_wait([](const boost::system::error_code& ){ cout<< "this shows second.\n" <<endl; });  // can't use packaged_task. It must be a function pointer or lambada function.
        cout<< "this shows first.\n" <<endl;

        io.run();                                                                                               /* io_service::run will not return if there are still works to do.
                                                                                                                  so make sure you start some async works before call io_service::run, or it will return immediately. */
        delete t;
    }

// 3. boost::asio::deadline_timer with boost::bind
    {
        boost::asio::io_context io;
        t = new boost::asio::deadline_timer(io, boost::posix_time::seconds(1));
        int count = 0;

        t->async_wait(boost::bind(&print, boost::placeholders::_1, t, &count));                          // boost::placeholders::error

        io.run();

        cout<< "finally, count == " << count <<endl;

        delete t;
    }

// 4. boost::asio::io_context::strand
    {
        boost::asio::io_context io;
        Printer p(io);
        thread T(boost::bind(&boost::asio::io_context::run, &io));
        io.run();
        T.join();
    }

    return 0;
}
