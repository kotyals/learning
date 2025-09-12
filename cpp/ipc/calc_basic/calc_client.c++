#include<iostream>
#include<sdbus-c++/sdbus-c++.h>
#include<thread>
#include<chrono>
using namespace std;

int main()
{
    try {
        std::unique_ptr<sdbus::IConnection> connection_ = sdbus::createSessionBusConnection();

        const std::string busName  = "org.example.Calculator";
        const std::string interfaceName = "org.example.Calculator";
        auto proxy = sdbus::createProxy(*connection_, busName, "/org/example/Calculator");
        proxy->uponSignal("ResultReady")
            .onInterface("org.example.Calculator")
            .call([](int result){
                std::cout << "Result Ready signal caught, result: " << result << endl;
            });
        proxy -> finishRegistration();//on clients only strictly required only if receiving some signals
        /*
        Instead we can do like this
        proxy ->registerSignalHandler(interfaceName,"ResultReady",
        [&](sdbus::Signal &signal){
            int result{};
            signal  >> result;
            std::cout << "Result Ready signal caught, result: " << result << endl;
        });
        proxy -> finishRegistration();    */

        connection_ -> enterEventLoopAsync();

        int result;
        proxy->callMethod("Add")
            .onInterface(interfaceName)
            .withArguments(10, 20)
            .storeResultsTo(result);

        cout << "Result: " << result << endl;
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Wait for signal

        connection_ -> leaveEventLoop();
    }catch (const sdbus::Error& error) {
        cerr<< "Sdbus Exception: "<< error.what()<<endl;
    } catch(const std::exception& e ){
        cerr<< "Exception: "<< e.what()<<endl;
    }
    
    return 0;
}