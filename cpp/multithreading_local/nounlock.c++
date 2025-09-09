#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex m;

void fun(string thread) {
    m.lock();
    cout<<"Inside thread " << thread << endl;
    return; // function returned early before lock is removed, deadlock situation for another thread
    m.unlock();
}
void fun1(string thread) {
    std::lock_guard<std::mutex>lock(m); // attains lock and removes once it is out of scope
    cout<<"Inside thread " << thread << endl;
    return; // function returned early before lock is removed
    //but lock_guard takes care to unlock it once gone outside the scope
}
int main()
{
    // thread t1(fun,"thread1");
    // thread t2(fun,"Thread2");

    thread t1(fun1,"thread1");
    thread t2(fun1,"Thread2");

    t1.join();
    t2.join();
    return 0;
}