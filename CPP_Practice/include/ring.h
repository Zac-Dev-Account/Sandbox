#ifndef _RING_H_
#define _RING_H_

#include <iostream>

template<typename T>
class ring {
    private:
        int m_pos;
        T *m_values;
        int m_size;
        
    public:
        ring();
        ring(int size);
        virtual ~ring();
        class iterator;
        int size();
        void add(T value);
        //return ref not pointer to what is in the container
        T &get(int pos);

        iterator begin() {return iterator(0, *this);}
        iterator end() {return iterator(m_size, *this);}
};

//Inner class declaration
template<typename T>
class ring<T>::iterator {
            private:
                int m_pos;
                ring m_ring;
            public:
                iterator(int pos, ring &ringBuf);
                void print();

                iterator &operator ++(int) { 
                    m_pos++; 
                    return *this;
                    }

                iterator &operator ++() { 
                    m_pos++; 
                    return *this;
                    }

                T& operator *() {
                    return this->m_ring.get(m_pos);
                }

                bool operator !=(const iterator &other) const {
                    return m_pos != other.m_pos;
                }

        };

#endif