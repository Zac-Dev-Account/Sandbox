#include "lambda_tests.h"

class Test {
    private:
        int one{1};
        int two{2};
    
    public:
        void run() {
            int three{3};
            int four{4};
            //canot capture instance variables this way
            //need to capture this instead
            auto pLambda = [this, three, four](){
                //this alwways captures vars by reference not value
                one = 111;
                std::cout << one << std::endl;
                std::cout << two << std::endl;
                std::cout << three << std::endl;
                std::cout << four << std::endl;
            };               
            pLambda();
    }
};

class Check {
    public: 
        bool operator()(std::string &test) {
            return test.size() == 5;
    }
} check1;

void run(std::function<bool(std::string&)> check) {
    std::string test = "stars";
    std::cout << check(test) << std::endl;
}

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

bool check( std::string &test ){
    return test.size() == 3; 
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

    Test test;
    test.run();

    std::vector<std::string> vec{"one", "two", "three"};
    int size = 3;
    int count = std::count_if(vec.begin(), vec.end(), [size](std::string test){ return test.size() == size; });
    std::cout << count << std::endl;
    count = std::count_if(vec.begin(), vec.end(), check);
    std::cout << count << std::endl;

    count = std::count_if(vec.begin(), vec.end(), check1);
    std::cout << count << std::endl;

    auto lambda = [size](std::string test){return test.size() == size;};
    run(lambda);
    run(check1);

    std::function<int (int, int)> add = [](int one, int two){ return one + two; };
    std::cout << add (7, 3);

    //mutable lamdas
    int cats = 5;
    //capture by value but can mutate internally reqs mutable keyword
    [cats]() mutable {
        cats = 8;
        std::cout << cats << std::endl;
    }();

    return 0;
};