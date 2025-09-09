#include<iostream>
#include<thread>
using namespace std;
class A {
public:
    void operator()(int x, string identifier){
        while(x-- > 0 ) cout<<identifier << " " << x <<endl;
    }
    static void staticFun(int x,string identifier){
        while(x-- > 0 ) cout<<identifier << " " << x <<endl;
    }
    void fun(int x,string identifier){
        while(x-- > 0 ) cout<<identifier << " " << x <<endl;
    }
};



void fun(int x, string identifier) {
    while(x-- > 0 ) cout<<identifier << " " << x <<endl;
}
int main() {
    thread t1(fun,3,"Thread1");// using function pointer

    thread t2([](int x, string identifier){ //using lambda function
        while(x-- > 0 ) cout<<identifier<< " " <<x << endl;
    },10,"Thread2");
  
    thread t3(A(),10,"Thread3");//using functor

    thread t4(&A::staticFun,10,"thread4"); //using statin functions
    A a;
    thread t5(&A::fun,&a,10,"Thread5");//using non static functions



    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();




    return 0;
}