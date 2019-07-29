#include "ring.h"
#include <string>

template<typename T>
ring<T>::ring() {

};

template<typename T>
ring<T>::~ring() {

};

template<typename T>
void ring<T>::iterator::print() {
    std::cout << "Hello from iterator" << T() << std::endl;
}

//Not entirely sure why this is needed, but i couldn'get it to link or build without it
template class ring<int>;
template class ring<std::string>;

//	
// Instead of creating temporary function a cleaner way is to use template class definition as below.

// Instead of =>
// void TemporaryFunction ()
// {
// TestTemp<int> TempObj;
// }


// Use =>
// template class TestTemp<int>;

