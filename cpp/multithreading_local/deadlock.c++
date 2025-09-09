#include"header.h"

using namespace std;

mutex m1,m2;

void fun(string thread) {
    m1.lock();
    cout<<thread << " attained m1 lock  \n";
    this_thread::sleep_for(chrono::seconds(2));
    cout<<thread << " try to attain m2 lock  \n";
    m2.lock();
    cout<<thread << " attained m2 lock  \n";

    m1.unlock(); m2.unlock();
    cout<<thread << " Released both locks  \n";


}
void fun1(string thread){

    m2.lock();
    cout<<thread << " attained m2 lock  \n";
    this_thread::sleep_for(chrono::seconds(2));
    cout<<thread << " try to attain m1 lock  \n";
    m1.lock();
    cout<<thread << " attained m1 lock  \n";

    m1.unlock(); m2.unlock();
    cout<<thread << " Released both locks  \n";
    
}

void function(string thread) {
    this_thread::sleep_for(chrono::seconds(2));
    std::lock(m1,m2);// std::lock() tries to lock all the mutexes , and if any one of it fails it has a fallback mechanism and avoids deadlock 
    cout<<thread << " attained m1 and m2 lock  \n";


    m1.unlock(); m2.unlock();
    cout<<thread << " Released both locks  \n";


}
void function1(string thread){

    std::lock(m1,m2);
    cout<<thread << " attained m1 and m2 lock  \n";
    cout<<thread << " wait for 4 sec \n";

    this_thread::sleep_for(chrono::seconds(4));

    
    m1.unlock(); m2.unlock();
    cout<<thread << " Released both locks  \n";
    
}
int main()
{

    // thread t1(fun,"Thread1");
    // thread t2(fun1,"Thread2"); // will cause deadlock 

    //try to use std::lock();

    thread t3(function1,"Thread2");
    thread t4(function,"Thread1");
    t3.join(); t4.join();
    return 0;
}