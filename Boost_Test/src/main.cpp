#include <boost/math/special_functions/sign.hpp>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

//Test modules
#include "liskov.h"
#include "openclose.h"
#include "dependencyInversion.h"
#include "builders.h"

struct Journal {
    std::string title;
    std::vector<std::string> entries;

    Journal(const std::string &title) : title(title) {}

    void add_entry(const std::string &entry) {
        static int count = 1;
        entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + entry);
    }
    //do not add load and save functionality to the Journal class
    //These re file writing and something different
    //Breaks the single responsibility principle

    //separate concern called persistence
    //persistence code being added to journal code
    //every one will have a function called save and load
    //This is not abstract, persistence is nested in each class, not a good idea


    //Want to use DB instead of Files, it should be abstracted
    //Separation of Concerns. Journal take care of journal entries & title
    //Persist thing have a separate component / class
    //Have a PersistenceManager

    //More robust / reliable way of implementing persistence in an application
    //Saving / loading functionality
    //Instead of Journal, could be a template parent class
};

struct PersistenceManager {
    static void save(const Journal& j, const std::string& filename) {
        std::ofstream ofs(filename);
        for (auto& e : j.entries) {
            ofs << e << std::endl;
        }
    }       
};


int main(int argc, char const *argv[])
{
    /* code */
    //single responsibility principle
    //a class should have a single reason to change
    Journal journal {"Dear Diary"};
    journal.add_entry("I ate a bug");
    journal.add_entry("I cried today");

    PersistenceManager::save(journal, "diary.txt");

    openclose();
    liskov_substitution();
    dependency_inversion();
    builder_example();
    groovy_builder();
    return 0;
}
