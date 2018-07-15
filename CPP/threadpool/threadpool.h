#ifndef THREADPOOL
#define THREADPOOL

#include <boost/asio.hpp>
#include <memory>
#include <thread>
#include <future>

#define BOOST_ERROR_CODE_HEADER_ONLY

using namespace std;

typedef shared_ptr<thread> thread_ptr;

class ThreadPool{
private:
    bool stopped;
    int thread_num;
    vector<thread_ptr> thread_vec;
    boost::asio::io_service io_;
    boost::asio::io_service::work work_;

public:
    ThreadPool(size_t n):
        thread_num(n),
        stopped(false),
        work_(io_)
    {
        for(size_t i=0;i<thread_num;i++)
            thread_vec.push_back(
                        make_shared<thread>([&](){io_.run();})
                        );
    }

    ~ThreadPool(){
        if(!stopped){
            io_.stop();
            for(auto t:thread_vec)
                t->join();
            stopped = true;
        }
    }

    template <typename F, typename... Args>
    auto post(F&& f, Args&&... args)
    ->future<typename result_of<F(Args...)>::type>{
        typedef typename result_of<F(Args...)>::type result_type;

        auto task = make_shared<packaged_task<result_type()>>(bind(forward<F>(f), forward<Args>(args)...));
        future<result_type> res = task->get_future();
        io_.post([task]{(*task)();});

        return res;
    }
};

#endif // THREADPOOL

