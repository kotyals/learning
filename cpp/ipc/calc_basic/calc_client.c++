#include<iostream>
#include<sdbus-c++/sdbus-c++.h>
#include<thread>
#include<chrono>
using namespace std;

void onAsyncResultReceive(const sdbus::Error* e,int result)
{
   if(e){
    std::cerr << "[Callback ErrorS] " << e -> getName() << " - " << e -> getMessage() << std::endl;
   } else {
    std::cout << "[Callback] Mul = " << result << std::endl;
   }
}

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
        while(true){
            int choice;
            cout<<"Please choose from below \n 1. Add two numbers\n 2. Substract two numbers\n 3. Divide two numbers\n 4.Multiply 5.Exit \n";
            cin >> choice;
            int a, b, result;
            cout<<"Enter two numbers \n";
            cin >> a;
            cin >> b;
            switch(choice){
                case 1 :{
                    proxy -> callMethod("Add")
                        .onInterface(busName)
                        .withArguments(a,b)
                        .storeResultsTo(result);
                        cout<<"Result Received: " << result << endl;
                        break;
                }
                case 2: {
                    proxy -> callMethod("Sub")
                        .onInterface(busName)
                        .withArguments(a,b)
                        .storeResultsTo(result);
                        cout<<"Result Received: " << result << endl;
                        break;
                }
                case 3: {
                    proxy -> callMethod("Div")
                        .onInterface(busName)
                        .withArguments(a,b)
                        .storeResultsTo(result);
                        cout<<"Result Received: " << result << endl;
                        break;
                }
                case 4: {
                    proxy -> callMethodAsync("Mul")
                        .onInterface(busName)
                        .withArguments(a,b)
                        .uponReplyInvoke(onAsyncResultReceive);
                        break;
                }
                default: {
                    cout<<"Exiting";
                }
            }
        }
        connection_ -> leaveEventLoop();
    }catch (const sdbus::Error& error) {
        cerr<< "Sdbus Exception: "<< error.what()<<endl;
    } catch(const std::exception& e ){
        cerr<< "Exception: "<< e.what()<<endl;
    }
    
    return 0;
}