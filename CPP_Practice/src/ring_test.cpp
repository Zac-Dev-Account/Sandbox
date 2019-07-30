//Ring buffer, area of memory you can write to,but when it completes
//The read/write pointers will cycle on around the same bit of memory
#include "ring_test.h"
#include "ring.h"
int ring_test() {

    //ring buffer, size of mem it is using
    //constructor arg, 3, maximum of 3 strings in the buffer
    ring<std::string> textring(3);

    //four should overwrite one
    //ring buffer example
    textring.add("one");
    textring.add("two");
    textring.add("three");

    for (int i=0; i<textring.size(); i++) {
        std::cout << textring.get(i) << std::endl;
    }

    //98 approach
    //overrides ++ & * operators, required to use new style
    // for(ring<std::string>::iterator it=textring.begin(); it != textring.end(); it++) {
    //     std::cout << *it << std::endl;
    // }

    //2011 approach
    for(auto value: textring) {
        std::cout << value << std::endl;
    }
    //referencing an inner class.static accessor
    //Accessors
    //::
    //->
    //.

    return 0;
}
