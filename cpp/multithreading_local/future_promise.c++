#include"header.h"
#include<future>

using namespace std;

void producer(int n, promise<int> promise)
{   try{
     if(n == 0){
        throw(runtime_error("Value is zero, value should be non-zero"));

        cout<<"Producer producing value" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout<<"produced value complete by producer" << endl;
    promise.set_value(n*30);
    }
    }catch(...){
        promise.set_exception(current_exception());

    }
   
    
}
int main()
{
    promise<int> promise;
    future<int> future = promise.get_future();
    thread t1(producer,0,std::move(promise));

    cout<<"Main thread waiting for result" << endl;
    try {
        auto result = future.get();
        cout<<"Got the value: " << result << endl;
    } catch (exception &e){
        cout<<"Error: " << e.what()<<endl;
    }
    t1.join();


    return 0;
}