#include<iostream>
#include<sdbus-c++/sdbus-c++.h>

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
                .onInterface(busName)
                .implementedAs([this](int a, int b){
                    if(a < 0 || b < 0){
                        throw sdbus::Error("org.example.Calendar.InputError.InvalidInput","Numbers should greater than or eual to 0");
                    }
                    std::cout<<"Add a+b called"<<std::endl;
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
    CalculatorService service("org.example.Calculator","/org/example/Calculator");
    service.run();

    return 0;
}