#include<iostream>
#include<string>
using namespace std;


class Teacher {
    public:
        string name;
        void setDept(string s) {
            dept = s;
        }
        string getDept(){
            return dept;
        }
    private:
        string dept;
        
};
int main() {
    Teacher t1;
    t1.name = "Name1";
    t1.setDept("Maths");
    cout<< t1.name<< " "<<t1.getDept()<<endl;
    return 0;

}