#include<iostream>
#include<sdbus-c++/sdbus-c++.h>
#include<thread>
#include<chrono>

using namespace std;
class CalculatorService{
    std::unique_ptr<sdbus::IConnection> connection_;
    std::unique_ptr<sdbus::IObject> object_;
    string busName;

public:
    CalculatorService(string busName, string ObjPath);
    void run();
    int add(int a, int b);
    int sub(int a, int b);
    int div(int a, int b);
    int mul(int a, int b);
};