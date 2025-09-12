#include<iostream>
#include<sdbus-c++/sdbus-c++.h>
#include<thread>
#include<chrono>
using namespace std;

int main()
{
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
    try {
        proxy->callMethod("Add")
            .onInterface(interfaceName)
            .withArguments(10, 20)
            .storeResultsTo(result);

        cout << "Result: " << result << endl;
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Wait for signal

    } catch (const sdbus::Error& e) {
        cerr << e.getMessage() << endl << e.getName() << endl << e.what() << endl;
    }
    connection_ -> leaveEventLoop();
    return 0;
}