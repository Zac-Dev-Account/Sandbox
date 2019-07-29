//Ring buffer, area of memory you can write to,but when it completes
//The read/write pointers will cycle on around the same bit of memory
#include "ring_test.h"
#include "ring.h"
int ring_test() {

    //ring buffer, size of mem it is using
    //constructor arg, 3, maximum of 3 strings in the buffer
    // ring<string> textring(3);

    // //four should overwrite one
    // textring.add("one");
    // textring.add("two");
    // textring.add("three");
    // textring.add("four");

    // for (int i=0; i<textring.size(); i++) {
    //     std::cout << textring.get(i) << std::endl;
    // }

    //referencing an inner class.static accessor
    //Accessors
    //::
    //->
    //.

    ring<std::string>::iterator it;
    it.print();
    return 0;
}
