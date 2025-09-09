#include<iostream>
#include<string>

using namespace std;
class Student {
    public:
        string name;
        int marks;
        Student(string s, int m): 
        name(s),marks(m){};
        void printInfo() {
            cout<<"Name: " <<name<<endl;
            cout<<"Marks: " <<marks <<endl;
        }
};
class Teacher {
    public:
        string name;
        float *salary;
        Teacher(string n, float s): name(n),salary(&s){
            name = n;
            salary = new float;
            *salary = s; 

        }
        void printInfo() {
            cout<<"Name: " << name << endl;
            cout<<"Salary: " << *salary<< endl;
        }
        Teacher(Teacher &obj) { //deep copy
            this->name = obj.name;
            salary = new float;
            *salary = *obj.salary;
            
        }
};
int main() {
    Student s1("Rahul Yadav", 230);
    s1.printInfo();
    Student s2(s1); // default shallow copy
    s2.printInfo();

    Teacher t1("Ramesh ", 3000.0);
    t1.printInfo();
    Teacher t2(t1); // deep copy
    *(t2.salary) = 2000.0;
    t1.printInfo();
    t2.printInfo();




    return 0;

}