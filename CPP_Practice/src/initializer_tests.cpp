#include "initializer_tests.h"

int init_test() {
    
    int values[] = {1, 4, 5};
    std::cout << values[0] << std::endl;

    class C {
        public:
            std::string text;
            int id;
    };

    struct S{
            std::string text;
            int id;
    };

    //another way to initialize
    //Anonymous approach
    struct {
            std::string text;
            int id;
    } r1 = {"Hello", 7}, r2 = {"Hi", 9};

    //initialising a class. interesting style for classes
    //Morew commonly used with structs
    C c1 = {"Hello", 7};
    S s1 = {"Hello", 7};

    //C++ 11 has a better way to do this with {}
    std::vector<std::string> strings;
    strings.push_back("One");
    strings.push_back("Two");
    strings.push_back("Three");

    //C++ 11
    //generalises usage of braces
    int value{5};
    std::string text{"zhello"};
    int numbers[]{1, 2, 3};
    int *pInts = new int[3]{2, 4, 6};
    delete [] pInts;
    //empty {} to init to default value
    //nullptr
    int *pSomething{&value}; //eq to nullptr

    std::cout << value << std::endl;
    //C++11 no need for = sign
    struct {
        int value;
        std::string text;
    } s2{5, "Hi!"};
    std::cout << s2.text << std::endl;    
    //no need to push back in C++ 11
    std::vector<std::string> c_strings {"one", "two", "three"};
    
    //Initializer lists
    std::vector<int> vec_numbers {1, 3, 4, 6};
    std::cout << vec_numbers[2] << std::endl;

    class Test {
        public:
            Test(std::initializer_list<std::string> texts) {
                for(auto value : texts) {
                    std::cout << value << std::endl;
                }
            }

            void print(std::initializer_list<std::string> texts) {
                for(auto value : texts) {
                    std::cout << value << std::endl;
                }    
            }
    };

    Test test({"Hello", "Apple", "Orange", "Banana"});
    test.print({"x", "z", "two"});

    //Object initialisation
    class TestTwo {
        int id;
        std::string name{"John"};

        public:
            
            TestTwo(){};
            TestTwo(TestTwo& other) {
                id = other.id;
                name = other.name;
            }
            //Test &operator=(const Test &other) {}
            TestTwo(int id): id(id){}
            void print() {
                std::cout << id << ": " << name << std::endl;    
            }
    };
    TestTwo testTwo;
    testTwo.print();
    TestTwo testNew(77);
    testNew.print();
    TestTwo testCopy = testNew;
    testCopy.print();
    TestTwo* testPtr = &testNew;
    testPtr->print();
    return 0;
}       