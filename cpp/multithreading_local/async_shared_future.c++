#include"header.h"
#include<future>
#include<vector>

using namespace std;

int producer( int n) {
    this_thread::sleep_for(chrono::seconds(3));
    return n *20;
}
void consumer(shared_future<int> sf, int id){
    cout<<"Consumer " << id<<"  waiting for result"<<endl;
    int val = sf.get();
    cout<<"Consumer "<< id << " got value " << val << endl;
}
int main() 
{

    shared_future<int> f = async(launch::async,producer,20).share();
    vector<thread> threads;
    for(int i=0; i<20; i++) {
        threads.emplace_back(consumer, f, i);
    }
    for(auto &t : threads) {
        t.join();
    }
    

    return 0;
}