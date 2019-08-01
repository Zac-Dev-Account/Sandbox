#include "forwarding.h"

class Test {

};

//template type
//call right version based on rvalue or lvalue of a function
template<typename T>
void call(T &&arg){
    checkNew(std::forward<T>(arg));
}

void checkNew(Test &Test) {
    std::cout << "lvalue" << std::endl;
}
//method overloading
void checkNew(Test &&test) {
    std::cout << "rvalue" << std::endl;
}

int init_forwarding() {

    //t is an lvalue here
    //reference collapsing rule
    auto &&t = Test();

    call(Test());
    call(t);
    checkNew(t);

    return 0;
}