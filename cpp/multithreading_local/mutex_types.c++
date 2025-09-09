#include"header.h"
using namespace std;


std::timed_mutex m;
void doSomething(string thread){
    if(m.try_lock_for(chrono::seconds(3))) {
        cout<<"Thread "<< thread <<" attained lock and doing something" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"Thread "<< thread <<" finished doing something" << endl;\
        m.unlock();
        
    } else {
            cout<<"Thread "<< thread <<" couldnt attain lock in time" << endl;
    }   

}

std::recursive_mutex rm;
void recursiveFun(int x, string thread) {
    if(x <= 0) return;
    rm.lock();
    cout<<thread << " acuired lock " << x <<endl;
    recursiveFun(x-1,thread);
    cout<<thread<<" unlocked lock " << x<< endl;
    rm.unlock();


}


int main()
{
    // thread t1(doSomething,"Thread1");
    // thread t2(doSomething,"Thread2"); //timed mutex
    // t1.join();
    // t2.join();

    thread t3(recursiveFun,10,"Thread3");//recurive mutex

    
    t3.join();
    return 0;
}