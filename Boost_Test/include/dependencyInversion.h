#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

//Specifyign the best way to form depen dewncies between different objects

//High level modules should not depend on low level modules. Instead each of them should depend on abstractions
//Abstractions should not dpeend on the details. Details should depend on abstractions

//Abstractions are interfaces or base clases. Instead of depending on a concrete type. Be as general as possible
//Do not depend on the implementation details

enum class Relationship {
    parent,
    child,
    sibling
};

struct Person {
    std::string name;
};

struct RelationshipBrowser {
    virtual std::vector<Person> find_all_children_of(const std::string& name) = 0;
};

//all it does is provides functionality for data storage and utility functions for populating that storage
//performing research on the other hand is a high level module
struct Relationships : RelationshipBrowser { //low-level module/construct in our design
    std::vector<std::tuple<Person, Relationship, Person>> relations;

    void add_parent_add_child(const Person& parent, const Person& child) {
        
        //{} instantiates a tuple, as this vector takes a tuple param
        //could also use new tuple
        this->relations.push_back({parent, Relationship::parent, child});
        this ->relations.push_back({child, Relationship::child, parent});
    };

    std::vector<Person> find_all_children_of(const std::string& name) {

        std::vector<Person> children;
        for (auto&& relation : this->relations ) {

            if (std::get<0>(relation).name == name && std::get<1>(relation) == Relationship::parent) {
                children.push_back(std::get<2>(relation));
            }

        }
        return children;
    };
};

//do not take a direct dependency on a low-level module (Relationships right now)
//dependency inversion protects yuou from changes in the implementation details
struct Research { //high-level
    Research(RelationshipBrowser& browser) {
        for(auto& child : browser.find_all_children_of("John")){
            std::cout << "John has a child called " << child.name << std::endl;
        };
    };
};

int dependency_inversion() {
    Person parent{"John"};
    Person child1{"Chris"};
    Person child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_add_child(parent, child1);
    relationships.add_parent_add_child(parent, child2);
    Research _(relationships);
    return 0;
}

//Depend on abstractions / interfaces. Do not depend on other concrete classes

//different concerns should be put in different classes
//class should be open for extension, but closed for modification

//Gamma categorization
//Split into several different categories, Gamma categorization, named after Erich Gamma, GoF Author

//Creational Patterns
//Dealing with the creation (Construction) of objects
//Explicit(constructor), implicit(DI, reflection, etc)
//Wolesale(singlestatement) vs piecewise (step-by-step)

//Structural Patterns
//Concerned with the structure (Class members, adhering to some interface or another)
//Wrappers which mimic the underlying interface, tries to mimic as much as possible, the underlying class
//stress the importance of good api design
//replicating the interface as much as possible, as conveinent to use as possible
//Make APIs useable for other people

//Behavioural patterns
//Do not follow a cetntral theme
//Do it using completely different OOP mechanisms
//Solve a particular problem in a particular way