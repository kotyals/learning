#include"header.h"
#include<future>

using namespace std;

int producer( int n) {
    this_thread::sleep_for(chrono::seconds(3));
    return n *20;
}
void consumer(future<int> sf, int id){
    cout<<"Consumer " << id<<"  waiting for result"<<endl;
    int val = sf.get();
    cout<<"Consumer "<< id << " got value " << val << endl;
}
int main() 
{

    future<int> f = async(launch::async,producer,20);

    
    thread c1(consumer,std::move(f),1);
    c1.join();

    return 0;
}