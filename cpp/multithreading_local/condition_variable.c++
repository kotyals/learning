#include"header.h"
#include<condition_variable>
#include<queue>
using namespace std;

std::condition_variable cv;
std::queue<int> data;
bool dataProduced = false;
mutex m;
void produceData(int n){
    unique_lock<mutex> lock(m);
    data.push(n);
    dataProduced = true;
    cv.notify_all();


}
void dataConsumer(){
    unique_lock<mutex> lock(m);
    cv.wait(lock,[]{return dataProduced;});
    cout<<"Data produced is obtained\n";
    cout<<"Data is : "<< data.front() <<endl;
    data.pop();

}
int main() 
{
    thread consumer(dataConsumer);
    this_thread::sleep_for(chrono::seconds(4));
    thread producer(produceData,1000);
    consumer.join();
    producer.join();
    return 0;
}