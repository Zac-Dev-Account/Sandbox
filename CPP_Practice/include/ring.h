#ifndef _RING_H_
#define _RING_H_

#include <iostream>

template<typename T>
class ring {
    public:
        ring();
        virtual ~ring();
        class iterator;
};

//Inner class declaration
template<typename T>
class ring<T>::iterator {
            public:
                void print();
        };
        
#endif