#include <iostream>
#include "time.h"

std::string readLine() {
    std::string s;
    std::cin >> s;
    return s;
}

void test() {
    char *str = new char[50];
    std::cin >> str;
    std::cout << str << std::endl;
    std::cout << sizeof(*str) << std::endl;

    std::string* s = new std::string("po");
    std::cin >> *s;
    std::cout << *s;

    std::string ss = readLine();
    std::cout << ss;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
class A {
public:
    virtual void a() = 0;
};

class B : A {
    void a() override {

    }
};
