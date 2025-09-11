#include<iostream>
#include<sdbus-c++/sdbus-c++.h>
using namespace std;

int main()
{
    std::unique_ptr<sdbus::IConnection> connection_ = sdbus::createSessionBusConnection();


    auto proxy = sdbus::createProxy(*connection_,"org.example.Calculator","/org/example/Calculator");

    int result;
    try {
        proxy->callMethod("Add")
        .onInterface("org.example.Calculator")
        .withArguments(-5,20)
        .storeResultsTo(result);

    cout<<"Result: "<< result<<endl;
    } catch (const sdbus::Error& e){
        cerr<<e.getMessage() <<endl<<e.getName() <<endl << e.what()<<endl;
    }
    

    return 0;
}