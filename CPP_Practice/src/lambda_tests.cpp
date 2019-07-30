#include "lambda_tests.h"

//function pointer to a func which
//has a void return type and takes no parameters
void test(void (*pFunc)()) {
    pFunc();
}

void testGreet(void (*greet)(std::string)) {
    greet("Bob");
}

void runDivide(double (*divide)(double, double)) {
    std::cout << divide(9, 3) << std::endl;
}

int init_lambda(){

    //valid lambda expression
    //inline anonymous function, not running code just defining it here
    //no name or return type
    //assign anonymous func to variable
    //what is the type? just use auto instead
    auto func = [](){std::cout << "Hello" << std::endl;};
    //put code in the {} 
    test(func);

    test( [](){std::cout << "Hello again" << std::endl;} );


    //lambda with parameters
    auto pGreet = [](std::string name){std::cout << "Hello " << name << std::endl;};
    pGreet("Mike"); 
    testGreet(pGreet);

    //lambda with return types
    //no need to specify return type in a lmbda expression
    //trailing return type syntax req for lamdas with ambig types
    auto pDivide = [](double a, double b) -> double {
        if (b == 0.0) {
            return 0;
        }
        return a/b;
    };

    std::cout << pDivide(10.0, 0) << std::endl;
    runDivide(pDivide);

    //lamda capture expressions
    int one = 1;
    int two = 2;
    int three = 3;
    //square brackets are used to capture local variables in scope of lamda exp
    //These are pass by val not ref. Beware Memory & performance
    [one, two](){std::cout << one << ", " << two << std::endl; }();
    //also works captures all local vars by value
    [=](){std::cout << one << ", " << two << std::endl; }();

    //capture variables by ref
    [&one, &two](){one=12; std::cout << one << ", " << two << std::endl; }();
    //capture all by ref
    [&](){one=12;two=64; std::cout << one << ", " << two << std::endl; }();
    std::cout << one << std::endl;
    std::cout << two << std::endl;
    return 0;
};