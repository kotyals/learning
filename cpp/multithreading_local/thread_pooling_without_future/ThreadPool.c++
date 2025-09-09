#include"ThreadPool.h"

ThreadPool::ThreadPool(size_t s) : numThreads(s) {
    stop = false;
    for(int i = 0; i< numThreads; i ++){
        workers.emplace_back([this] { 
            this -> worker();
        });
    }
}

ThreadPool::~ThreadPool(){
    stop = true;
    cv.notify_all(); 
    for(auto& worker : workers)
    { worker.join(); }

}

void ThreadPool::worker() {
    while(true){
        std::function<void()> task;
        {
            std::unique_lock<mutex> lock(queueMutex);
            cv.wait(lock,[this] { return stop || !tasks.empty(); });

            if( stop && tasks.empty()) return;
            task = std::move(tasks.front()); // moving is efficient, if tasks lambda has obtained some large value by copy then copying that large objects will be bottleneck
            tasks.pop();   
        }
        task();
    }
}

int main() {
    ThreadPool pool(3);

    for(int i=0; i<17; i++) {
        {
            pool.enqueue([i]{
                cout<<"Task: " <<i << " started execution be thread: " << std::this_thread::get_id()<<endl;
                std::this_thread
                ::sleep_for(std::chrono::seconds(10));
                cout<<"Task: " <<i << " finished execution be thread: " << std::this_thread::get_id()<<endl;
            });
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(100));
    return 0;
}