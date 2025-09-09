#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
int counter = 0;
mutex m;
void incrementCounterBy(int x){
    m.lock();
    while(--x >= 0) {
        counter++;
    }
    if(!m.try_lock()) cout<<"Couldnt get the lock";
    m.unlock();
}
int main() {
    thread t1 (incrementCounterBy,10000000);
    thread t2 (incrementCounterBy,20000000);
    t1.join();
    t2.join();
    cout<<"Counter value: " << counter<< endl;
    return 0;
}