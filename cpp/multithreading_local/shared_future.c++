#include"header.h"
#include<future>

using namespace std;

void producer(promise<int> p) {
    this_thread::sleep_for(chrono::seconds(3));
    p.set_value(20);
}
void consumer(shared_future<int> sf, int id){
    cout<<"Consumer " << id<<"  waiting for result"<<endl;
    int val = sf.get();
    cout<<"Consumer "<< id << " got value " << val << endl;
}
int main() 
{

    promise<int> p;
    shared_future<int> sf = p.get_future().share();
    thread p1(producer,std::move(p));

    thread c1(consumer,sf,1);
    thread c2(consumer,sf,2);
    thread c3(consumer,sf,3);

    p1.join();
    c1.join();
    c2.join();
    c3.join();



    return 0;
}