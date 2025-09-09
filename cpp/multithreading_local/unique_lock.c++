#include"header.h"

using namespace std;

/*
why use unique_lock
- it gives us more flexibility 
- unlike lock_guard it allows us to lock and unlock whenever and however it is reuired 
- and it also allows to used timed mutexes and wait for some time/ until to get the lock 
- ownership can be moved 
Locking strategies are 
- defer_lock ( do not lock immediately, just create the lock object and later lock with .lock or std::lock()) 
- adopt_loc ( take ownerhip of the lock that is already locked)
- try_lock ( only this supports try lock)
*/

mutex m;
void simpleLock(string thread) {
    unique_lock<mutex> lock (m);
    if(lock.owns_lock()) cout<<"Lock obtained by " << thread << endl;

    //automatically unlock after the scope is over
}

mutex m1;
void deferedLock(string thread) {
    unique_lock<mutex> lock (m1,std::defer_lock);
    if(lock.owns_lock()){
        cout<<"Lock obtained by " << thread << endl;
    } else {
        cout<< "Lock not obtained / mutex is not locked by " << thread << endl;

    }
    lock.lock(); // or std::lock(lock) 
    m1.lock(); // cant use it like this, because lock will not know the state , avoid this
    //if using like this, then first lock the raw mutex and use adopt lock.

    if(lock.owns_lock()){
        cout<<"second time Lock obtained by " << thread << endl;
    } else {
        cout<< "second time Lock not obtained / mutex is not locked by " << thread << endl;
        
    }

    //automatically unlock after the scope is over
}

mutex m3;
void adoptLock(string thread) {
    m3.lock();//lock raw mutex
    cout<<thread<<" lock acuired by raw mutex \n";

    unique_lock<mutex> lock(m3,adopt_lock); //adopt the lock 
    lock.owns_lock() ? cout<<"Lock obtained \n" : cout<<"Lock not obtained\n";

    //also unlock wherever it is reuired like this 
    lock.unlock();


}

mutex m4;
void tryToLock(string thread) {

    unique_lock<mutex> lock(m4,try_to_lock);
    if(!lock.owns_lock()){
        cout<< thread << " couldnt attain lock of mutex \n";
    }
    
    this_thread::sleep_for(chrono::seconds(5));

        lock.try_lock();

    if(lock.owns_lock()){
        cout<< thread << "  attained lock of mutex \n";
    }

    
}
void lockMutex(string thread) {
    lock_guard<mutex> lock(m4);
    cout<<thread << "attained lock of mutex \n";

    this_thread::sleep_for(chrono::seconds(2));

    cout<<thread << "unlokced mutex \n";

}
int main() {
    // thread t1(simpleLock,"thread1");
    // t1.join();

    // thread t2(deferedLock,"Thread2");
    // t2.join();

    // thread t3(adoptLock,"Thread3");
    // t3.join();

    thread t5(lockMutex,"Thread5");

    thread t4(tryToLock,"Thread4");

    t4.join(); t5.join();

    this_thread::sleep_for(chrono::seconds(5));

    return 0;
}