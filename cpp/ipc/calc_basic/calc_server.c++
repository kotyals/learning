#include"calc_server.h"

CalculatorService::CalculatorService(std::string busName, std::string objPath):
    busName(busName),
    connection_{sdbus::createSessionBusConnection()},
    object_{sdbus::createObject(*connection_,objPath)}
    {
        connection_ -> requestName(busName);
        object_ -> registerMethod("Add")
            .onInterface(busName) // keeping interface name same as bus name
            .implementedAs([this](int a,int b){
                return this -> add(a,b);
            });
        object_ -> registerMethod("Sub")
            .onInterface(busName)
            .implementedAs([this](int a,int b){
                return this -> sub(a,b);
            });
            object_ -> registerMethod("Div")
            .onInterface(busName)
            .implementedAs([this](int a,int b){
                return this -> div(a,b);
            });
    }
void CalculatorService::run(){
    object_->finishRegistration();
    std::cout<<"Calculator bus started "<<std::endl;
    connection_->enterEventLoop();
}

int CalculatorService::add(int a, int b){
    std::cout<<"Add a+b called"<<std::endl;
    auto signal = object_ -> createSignal(busName, "ResultReady"); // Use interface name here
    signal << a + b;
    object_ -> emitSignal(signal);
    return a + b;
}
int CalculatorService::sub(int a, int b){
    int result = a - b;
    auto signal = object_ -> createSignal(busName,"ResultReady");
    signal << result;
    object_ -> emitSignal(signal);
    return a + b;
}
int CalculatorService::div(int num, int den){
    if(den == 0){
        throw sdbus::Error("org.example.Calendar.InputError.InvalidInput","Denominator should not be zero");
    }
    int result = num/den;
    auto signal = object_ -> createSignal(busName,"ResultReady");
    signal << result;
    object_ -> emitSignal(signal);
    return result;
}

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