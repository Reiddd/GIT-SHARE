#ifndef THREADPOOL
#define THREADPOOL

#include <vector>
#include <queue>
#include <memory>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <utility>

using namespace std;

class ThreadPool{
public:
    inline ThreadPool(size_t threads):
        stop(false)
    {
        for(size_t i=0;i<threads;i++)
            workers.emplace_back(thread([this](){
                for(;;){
                    function<void()> task;

                    {
                        unique_lock<mutex> lock(this->queue_mutex);

                        this->condition.wait(lock, [this]{return this->stop || this->tasks.empty();});

                        if(this->stop && this->tasks.empty())
                            return;

                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
            }));
    }


    inline ~ThreadPool(){
        {
            unique_lock<mutex> lock(queue_mutex);

            stop = true;
        }

        condition.notify_all();

        for(thread& worker: workers)
            worker.join();
    }


    template<class F, class... Args>
    future<typename result_of<F(Args...)>::type> enqueue(F&& f, Args&&... args)
    {
        using return_type = typename result_of<F(Args...)>::type;

        auto task = make_shared<packaged_task<return_type()>>(bind(forward<F>(f),
                                                                   forward<Args>(args)...));
        future<return_type> res = task->get_future();

        {
            unique_lock<mutex> lock(queue_mutex);
            if(stop)
                throw runtime_error("enqueue on stopped ThreadPool");

            tasks.emplace([task]{(*task)();});
        }

        condition.notify_one();
        return res;
    }

private:
    vector<thread> workers;
    queue<function<void()>> tasks;

    mutex queue_mutex;
    condition_variable condition;

    bool stop;
};

#endif // THREADPOOL

