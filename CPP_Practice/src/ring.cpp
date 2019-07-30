#include "ring.h"
#include <string>

template<typename T>
ring<T>::ring() {}

template<typename T>
ring<T>::ring(int size): m_pos(0), m_size(size), m_values(nullptr) { this->m_values = new T[size]; }

template<typename T>
ring<T>::~ring() { delete [] this->m_values; }

template<typename T>
int ring<T>::size() { return this->m_size; }

template<typename T>
void ring<T>::add(T value) {
    //increment value after using it
   this->m_values[this->m_pos++] = value;
   if (this->m_pos == this->m_size) {
       this->m_pos = 0;
   }
}

template<typename T>
T& ring<T>::get(int pos) { return this->m_values[pos]; }

template<typename T>
ring<T>::ring::iterator::iterator(int pos, ring &ringBuf): m_pos(pos), m_ring(ringBuf) {

}


template<typename T>
void ring<T>::iterator::print() { std::cout << "Hello from iterator" << T() << std::endl; }

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

