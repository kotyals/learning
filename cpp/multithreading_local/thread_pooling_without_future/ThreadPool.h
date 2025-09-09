#include<iostream>
#include<thread>
#include<vector>
#include<functional>
#include<queue>
#include<condition_variable>
#include<mutex>

using namespace std;

class ThreadPool {
public:
    ThreadPool(size_t s);
    ~ThreadPool();
    template <typename T>
    void enqueue(T&& t){
        {
            std::unique_lock<mutex> lock(queueMutex);
            tasks.emplace(std::forward<T>(t));
        }
        cv.notify_one();
    }
    
private:
    vector<std::thread> workers;
    queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable cv;
    size_t numThreads;
    bool stop = false;
    
    void worker();

};