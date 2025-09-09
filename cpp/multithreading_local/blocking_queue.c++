#include"header.h"
#include<condition_variable>
#include<queue>

using namespace std;

class BlockingQueue {
    private:
        condition_variable not_full,not_empty;
        mutex m;
        queue<int> data;
                const size_t size;


    public:
    BlockingQueue(int s) : size(s){

    }
        void add(int item){
            unique_lock<mutex> lock(m);
            not_full.wait(lock,[this]{ return data.size() < size;});
            data.push(item);

            cout<<"Data: " << item <<" pushed "<< endl;
            not_empty.notify_one();
            cout<<"Notified to consumer" << endl;
        }
        void remove(){
            unique_lock<mutex> lock(m);
            not_empty.wait(lock,[this] { return !data.empty();});
            cout<<"Consumer got data: " << data.front()<< endl;
            
            data.pop();
            not_full.notify_one();
            cout<<"Notified to producer" << endl;

        } 

};


void producer(BlockingQueue &bq, int id) {
    for (int i = 0; i < 5; i++) {
        bq.add(id * 10 + i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Example consumer function
void consumer(BlockingQueue &bq) {
    for (int i = 0; i < 5; i++) {
        bq.remove();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main()
{
    BlockingQueue b(3);


    std::thread p1(producer, std::ref(b), 1);
    std::thread p2(producer, std::ref(b), 2);
    std::thread c1(consumer, std::ref(b));
    std::thread c2(consumer, std::ref(b));

    p1.join();
    p2.join();
    c1.join();
    c2.join();

    

    return 0;
}