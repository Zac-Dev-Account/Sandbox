#include <iostream>
//#include "deleg_constr.h"
//#include "initializer_tests.h"
//#include "ring_test.h"
//#include "lambda_tests.h"
#include "forwarding.h"

int main(int argc, char const *argv[])
{
    //Remember to clear out build files each time otherwise cmake will not rebuild correctly

    //ring_test();
    //init_test();
    //init_lambda();
    //init_deleg();
    init_forwarding();
    return 0;
}
