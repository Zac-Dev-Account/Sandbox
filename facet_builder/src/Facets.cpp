#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

int main__()
{
  Person p = Person::create()
    .lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
    .works().at("PragmaSoft").as_a("Consultant").earning(10e6);
//lives returns an address builder with the following methods that also return a reference to the address builder
//works returns a job builder with the following methods that also return a reference to the job builder

//<< is overridden to print out all of the person variables
//create() returns a PersonBuilder, but person builder has a Person cast defined so it can be cast back to a Person object with std::move
  cout << p << endl;
  return 0;
}