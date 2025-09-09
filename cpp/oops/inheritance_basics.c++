#include<iostream>
#include<string>
using namespace std;

class Person {
    public:
        string name;
        int age;
        Person(){
            cout<<"Person default constructor\n";
        }
        Person(string s, int a) : name(s),age(a)  {
                        cout<<"Person constructor\n";

        }
};
class Student : public Person{
    public:
        int rollno;
        Student(string n,int a, int r):Person(n,a){
            cout<<"Student constructor\n";
            rollno = r;
        }
        void printInfo() {
            cout<<"Name: " << name <<endl;
            cout<<"Age: " << age << endl;
            cout<<"Roll no: " << rollno <<endl;
        }
};

int main() {
    Student s1("Rahul",22,01);
    s1.printInfo();
    return 0;
}