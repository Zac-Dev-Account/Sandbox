#include "deleg_constr.h"

//Static cast examples
class Dad {
    public:
        void speak() {
            std::cout << "parent!" << std::endl;
        }
        virtual ~Dad() {

        }
};
class Brother: public Dad {

};
class Sister: public Dad {
    
};

class Test {
    private:
        static const int SIZE = 100;
        int* m_pBuffer{nullptr};

    public:
        Test() {
            std::cout << "constructor" << std::endl;
            m_pBuffer = new int[SIZE]{};
            //allocating memory to object
            //std::memset( m_pBuffer, 0, sizeof(int)*SIZE);
        }

        Test(int i) {
            std::cout << "parameterized constructor" << std::endl;
            m_pBuffer = new int[SIZE]{};

            for(int i=0; i<SIZE; i++) {
                m_pBuffer[i] = 7*i;
            }
        }

        Test(const Test &other) {
            std::cout << "copy constructor" << std::endl;
            m_pBuffer = new int[SIZE]{};
            memcpy(m_pBuffer, other.m_pBuffer, SIZE*sizeof(int));

        }

        //Move constructor
        //needs to change other
        Test(Test &&other) {
            std::cout << "Move constructor" << std::endl;
            //grab resources from other and steal them for new obj
            m_pBuffer = other.m_pBuffer;
            //do not call destructor, don't want to deallocate memory
            other.m_pBuffer = nullptr;
            //safe to call delete after other is set to point to null
        }

        //override assignment operator
        Test &operator=(const Test &other) {
            std::cout << "assignment " << std::endl;
            m_pBuffer = new int[SIZE]{};

            memcpy(m_pBuffer, other.m_pBuffer, SIZE*sizeof(int));
            return *this;
        }

        Test &operator=(Test &&other) {
            std::cout << "Move assignmnent operator" << std::endl;
            delete [] m_pBuffer;
            m_pBuffer = other.m_pBuffer;
            other.m_pBuffer = nullptr;
            
            return *this;
        }

        ~Test() {
            std::cout << "Destructor" << std::endl;
            delete [] m_pBuffer;
        }

        //override << operator
        friend std::ostream &operator<<(std::ostream &out, const Test &test){
            out << "Hello from test" << std::endl;
            return out;
        };
};

//copy elision optimisation, gcc does this automatically
//obj returned by vlue inefficient
Test getTest() {
    return Test();
}

void check(const Test &value) {
    std::cout << "LValue function!" << std::endl;
}

//can change objects or steal resources
void check(Test &&value) {
    std::cout << "RValue function!" << std::endl;
}

class Parent {
    private:
        int dogs {5};
        std::string text {"hello"};
    public:
        //delegated constructor. call one constructor first
        //other approach is to have an init method
        Parent(): Parent("hello") {
            dogs = 5;
            std::cout << "No parameter parent constructor" << std::endl;
        }

    Parent( std::string text ) {
        dogs = 5;
        this->text = text;
        std::cout << "string parent constructor" << std::endl;
    }
};
//delegated constructor
//must run parent in super class when constructed
//cant call them directly 
class Child: public Parent {
    public:
    //default now calls string prm constructor
        Child(): Parent("Hello") {

        }
};

int init_deleg() {
    //Parent parent("hello");
    //Child child;
    //L values are named values that we can take the address of
    //Test test1 = getTest();
    //std::cout << test1;

    //another inefficiency solved with move constructors
    //std::vector<Test> vec{Test()};

    //L values and R values
    //value1 = L, 7 = R
    //int value1 = 7;
    //only works with L values
    //int *pValue1 = &value1;
    //Test *pTest1 = &test1;

    //cannot do this as the return val is an R value
    //Test *pTest2 = &getTest();
    //prefixes work, post fixes do not
    //int *pValue3 = &++value1;
    //R values are tmp values mostly  returned from functions
    //Can always take the address of L values

    //& Lvalue reference
    //Test &rTest1 = test1;
    //R values are tmp values without a name
    //req const to bind R values
   // const Test &rTest2 = getTest();
    //const  L value refs can bind to R values
    //Test test2(Test(1));

    //Test &ltest1 = test1;
    //&& for R value references.
    //binds to R tmp values
    //Test &&rtest1 =  getTest();
    //Test &&rtest2 = Test();
    //check(Test());
    //check(getTest());
    //check(test1);
    //alot more efficient than copy consatructors
    //remember && for Rvalue references

    //calling the move constructor
    std::vector<Test> vec2;
    //vec2.push_back(Test());

    //move assignment operator
    Test testNew;
    testNew = getTest();
    std::cout << "Test: This will run after tmp obj is destroyed" << std::endl;
    //Okay so move constructors create a new object and move the temp data t othe new object
    //Then they delete the tmp data

    //casting in C++
    float value = 3.23;
    std::cout << static_cast<int>(value) << std::endl;

    Dad dad;
    Brother brother;
    //polymorphism
    //pointer or reference to a subclass in any situation and then call the overriden methods from the subclass

    Dad *pp = &brother;
    //cast parent to child
    //very unsafe, lot sof issues with virtual functions, methods in brother that are not in parent, etc
    Brother *db = static_cast<Brother*>(&dad);
    Dad *ppb = &brother;
    Brother *pbb = static_cast<Brother *>(ppb);

    //R value reference
    Dad &&p = static_cast<Dad &&>(dad);
    p.speak();

    //Dynamic cast
    //detect at runtime whether or not this makes sense
    //reqs a virtual deconstructor for this to work
    Brother *pbb2 = dynamic_cast<Brother *>(ppb);

    //reinterpret cast
    //same level as Brother, subclass of dad
    Sister sister;
    Sister *ptt = dynamic_cast<Sister *>(ppb);
    //reinterpret_cast pretty much cast anything to anything, no checking.


    std::cout << pbb2 << std::endl;
    return 0;
}