#include<iostream>
#include<sdbus-c++/sdbus-c++.h>
#include<thread>
#include<chrono>

class CalculatorService{
    std::unique_ptr<sdbus::IConnection> connection_;
    std::unique_ptr<sdbus::IObject> object_;

public:
    CalculatorService(std::string busName, std::string objPath):
        connection_{sdbus::createSessionBusConnection()},
        object_{sdbus::createObject(*connection_,objPath)}
        {
            connection_->requestName(busName);
            object_->registerMethod("Add")
                .onInterface("org.example.Calculator") // Use interface name here
                .implementedAs([this](int a, int b){
                    std::cout<<"Add a+b called"<<std::endl;
                    if(a < 0 || b < 0){
                        throw sdbus::Error("org.example.Calendar.InputError.InvalidInput","Numbers should be greater than or equal to 0");
                    }
                    auto resultReadySignal = object_->createSignal("org.example.Calculator", "ResultReady"); // Use interface name here

                    resultReadySignal << a + b;
                    object_->emitSignal(resultReadySignal);
                    return a + b;
                });
        }
        void run(){
            object_->finishRegistration();
            std::cout<<"Calculator bus started "<<std::endl;
            connection_->enterEventLoop();
        }
};

int main()
{
    try{
        CalculatorService service("org.example.Calculator","/org/example/Calculator");
        service.run();
    } catch (const sdbus::Error& error) {
        std::cerr << "Exception: " << error.what() << std::endl;
    }
    return 0;
}