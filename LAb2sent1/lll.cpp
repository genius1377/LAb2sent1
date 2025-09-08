#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

class Class1 {
public: virtual ~Class1() {}
      virtual Class1* clone() const {
          return new Class1(*this);
      }
};

class Class2 : public Class1 {
public: Class1* clone() const override {
    return new  Class2(*this);
}
};

void my_copy(const vector<Class1*>& source, vector<Class1*>& destination) {
    for (const Class1* obj : source) {
        destination.push_back(obj->clone());
    }
}
int main() {
    Class1 obj1;
    Class2 obj2;
    Class2 obj3;
    vector<Class1*> orig = { &obj1, &obj2, &obj3 };
    vector<Class1*> database;
    my_copy(orig, database);
    for (Class1* obj : database) {
        cout << "Type: " << typeid(*obj).name() << endl;
    }
    for (Class1* obj : database) {
        delete obj;
    }
}