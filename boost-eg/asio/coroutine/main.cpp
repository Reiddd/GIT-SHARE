#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/yield.hpp>                             //reenter yield
#include <boost/date_time/posix_time/posix_time.hpp>
#include <thread>

class Coroutine1: public boost::asio::coroutine
{
public:
    Coroutine1()
        : count_(0),
          loop_time(30),
          work(io),
          t1(new boost::asio::deadline_timer(io, boost::posix_time::seconds(2))),
          t2(new boost::asio::deadline_timer(io, boost::posix_time::seconds(2)))
    {
        t = new std::thread(boost::bind(&boost::asio::io_context::run, &io));                  // can't just io.run(), it will block the constructor function
    }

    ~Coroutine1(){
        io.stop();                                                                                // stop the io_context first, otherwise the thread will never join
        t->join();
        delete t;
        delete t1;
        delete t2;
        std::cout<< "finally, count_ == " << count_ << "\n" <<std::endl;
    }

    void operator()(boost::system::error_code e = boost::system::error_code()){
        if(!e)
        reenter(this) for( ; ; )
        {
            if(loop_time-- > 0){                                                                 // can't define local variables in for loop, they won't be reached.
                yield t1->async_wait(boost::bind(&Coroutine1::print, this, 1));                 // when asyncronous work is done, reenter is triggered, the next line is reached.
                yield t2->async_wait(boost::bind(&Coroutine1::print, this, 2));
            }
        }
    }
private:
    void print(int timer){
        std::cout<< "timer" << timer << " : " << count_ <<std::endl;
        count_++;
    }

    boost::asio::io_context io;
    boost::asio::io_context::work work;
    boost::asio::deadline_timer* t1 = nullptr;
    boost::asio::deadline_timer* t2 = nullptr;
    int count_;
    int loop_time;
    std::thread* t;
};


class Coroutine2: public boost::asio::coroutine
{
public:
    Coroutine2(){}
    ~Coroutine2(){ std::cout<< "\n" <<std::endl; }

    int operator()(const boost::system::error_code e = boost::system::error_code(), int i = 0){ // every argument must be assigned a default value
        if(!e) reenter(this) for( ; ; )
        {
            yield return i;
            yield return i+1;
        }
    }
};

class Coroutine3: boost::asio::coroutine
{
public:
    Coroutine3(){}
    ~Coroutine3(){}

    int operator()(const boost::system::error_code e = boost::system::error_code(), int i = 0){
        if(!e) reenter(this) for( ; ; )
        {
            yield std::cout<< "c3(" << i << ')' << i <<std::endl;
            fork(operator()(e, i-1));                                                                     // fork(function) blocks until function is done
            yield std::cout<< "c3(" << i << ')' << i+1 <<std::endl;                                   // fork's resume point is directly after the ;
        }
    }
};

int main()
{
/* Coroutine1 */
    {
        std::cout<< "Coroutine1 :" <<std::endl;
        Coroutine1 c1;
        for(int i=0; i<60; i++)
            c1();                                                                                   // one call one yield, like python's generator

        sleep(4);
    }

/* Coroutine2 */
    {
        std::cout<< "Coroutine2 :" <<std::endl;
        Coroutine2 c2;
        std::cout<< "c2(1) == " << c2(boost::system::error_code(), 1) <<std::endl;          // 1
        std::cout<< "c2(100) == " << c2(boost::system::error_code(), 100) <<std::endl;    // 101
        std::cout<< "c2(2) == " << c2(boost::system::error_code(), 2) <<std::endl;          // 2
        std::cout<< "c2(3) == " << c2(boost::system::error_code(), 3) <<std::endl;          // 4
    }

/* Coroutine3 */
    {
        std::cout<< "Coroutine3 : " << std::endl;
        Coroutine3 c3;
        c3(boost::system::error_code(), 1);      // c3(1) 1
        c3(boost::system::error_code(), 100);   // c3(99) 100 c3(100) 101
        c3(boost::system::error_code(), 2);     // c3(2) 2
        c3(boost::system::error_code(), 3);     // c3(2) 3 c3(3) 4
    }

    return 0;
}
