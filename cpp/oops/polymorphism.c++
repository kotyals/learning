#include<iostream>
#include<string>
using namespace std;


class Person {
public: 
    string name;
    int age;
    virtual void printInfo(){
        cout<<" Persons getinfo()"<<endl;
    }

    void printInfo1() {
        cout << "Person's printInfo1()" << endl;
    }
    Person(string n,int a) {
        name = n;
        age =a;
    }
};

class Student : public Person {
public:
    int roll;
    void printInfo(){
        cout<<" Students  getinfo()"<<endl;
    }
    void printInfo1() {
        cout << "Student's printInfo1()" << endl;
    }
    Student(string n, int a, int r):Person(n,a) {
        roll = r;  
    }
};
int main() {


    Student s1("Rahul",20,3);
    s1.printInfo(); // Calls Student's printInfo()
    s1.printInfo1(); // Calls Student's printInfo1()

    Person p1("PPP",22);
    p1.printInfo(); // Calls Person's printInfo()
    p1.printInfo1(); // Calls Person's printInfo1()

    Person *p = new Student("Manish", 21, 4);
    p->printInfo(); // Calls Student's printInfo() due to polymorphism
    p->printInfo1(); // Calls Person's printInfo1() since it's not virtual 

    Student *s = new Student("Rahul", 20, 3);
    s->printInfo(); // Calls Student's printInfo()
    s->printInfo1(); // Calls Student's printInfo1()

    return 0;
}