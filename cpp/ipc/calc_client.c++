#include<iostream>
#include<sdbus-c++/sdbus-c++.h>
using namespace std;

int main()
{
    std::unique_ptr<sdbus::IConnection> connection_ = sdbus::createSessionBusConnection();


    auto proxy = sdbus::createProxy(*connection_,"org.example.Calculator","/org/example/Calculator");

    int result;
    proxy->callMethod("Add")
        .onInterface("org.example.Calculator")
        .withArguments(10,20)
        .storeResultsTo(result);

    cout<<"Result: "<< result;

    return 0;
}