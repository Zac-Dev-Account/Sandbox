#include "forwarding.h"
using namespace std::placeholders;

class Test {
    public:
        int add(int a, int b, int c) {
            std::cout << a << ", " << b << ", " << c << std::endl;
            return a + b + c;
    }
};
//Smart pointers handle deallocation of memory for you
class TestNew {
    public:
        TestNew() {
            std::cout << "Created" << std::endl;
        }

        void greet() {
            std::cout << "Hello " << std::endl;
        }

        virtual ~TestNew() {
            std::cout << "Destroyed" << std::endl;
        }
};

class Temp {
    private:
        std::unique_ptr<TestNew[]> pTest;
    public:
        Temp(): pTest(new TestNew[2]) {

        }
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

int add(int a, int b, int c) {
    std::cout << a << ", " << b << ", " << c << std::endl;
    return a + b + c;
}

int run(std::function<int(int, int)> func) {
    return func(7, 3);
}

int init_forwarding() {
    //t is an lvalue here
    //reference collapsing rule
    auto &&t = Test();
    //bind is used for creating an alias for a function, like a functor/function pointer

    call(Test());
    call(t);
    checkNew(t);
    std::cout << add(1, 2, 3) << std::endl;

    //pointer to function + arguments, bound to a fcallable alias
    Test test;
    auto calculate = std::bind(&Test::add, test, 500, _2, _1);
    
    std::cout << calculate(10, 20) << std::endl;
    std::cout << run(calculate) << std::endl;

    //unique ptrs, syntax
    //allocate memory, constructor is called
    //can do this to free up memory quicker in c++ reducing scope further within a method
    //std::unique_ptr<TestNew[]> pTest(new TestNew[2]);
    //pTest[1].greet();
    
    //Temp temp;


    //shared pointers example
    std::shared_ptr<TestNew> pTest2(nullptr);
    {
        std::shared_ptr<TestNew> pTest1 = std::make_shared<TestNew>();
        pTest2 = pTest1;
    }


    std::cout << "Finished!" << std::endl;

    return 0;
}