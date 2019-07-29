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
void tempFunction () {
    ring<int> ring_temp;
    ring<int>::iterator it_temp;
    it_temp.print();

    ring<std::string> ring_temp2;
    ring<std::string>::iterator it_temp2;
    it_temp2.print();
}

