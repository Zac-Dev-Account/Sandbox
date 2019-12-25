#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

#include <sstream>
#include <memory>

//Some objects are simple, can create in a single constructor call
//Other objects require a lot of ceremony to create
//WHen you are constructing something from a dozen different pieces
//Construct an object piece by piece
//10 constructor args is not productive, it's not a great way to go
//May mess up two of the arguments by misplacing them
//Massive constructor is poor code, opt for piece-wise construction
//provide a good api for actually doing it, builder pattern is all about this
//essentially a separate component, special api for doing it succinctly when piece-wise construction is complicated

//Works, but this approach does not really scale
//Such as a list of items or something

//Create oop structures representing different parts of html you are building

//utility class for modelling htmlElement in a PP{ way}
//forward

struct HtmlElement {
    std::string name, text;
    std::vector<HtmlElement> elements;

    const std::size_t indent_size = 2;

    HtmlElement() {};
    HtmlElement(const std::string& name, const std::string& text) : name(name), text(text) {}

    //recursive printing example
    //when called on the root HtmlElement which contains HtmlElements inside of itself
    //Interesting approach
    std::string str(int indent = 0) const {
        std::ostringstream oss;
        std::string i(indent_size*indent, ' ');
        oss << i << "<" << this->name << ">" << std::endl;

        if ( this->text.size() > 0 ) {
            oss << std::string(indent_size*(indent + 1), ' ') << this->text << std::endl;
        }

        for ( const auto& e : this->elements ) {
            oss << e.str(indent + 1);
        }

        oss << i << "</" << this->name << ">" << std::endl;
        return oss.str();
    } 

};

struct HtmlBuilder {
    HtmlElement root;

    HtmlBuilder(std::string root_name) {
        root.name = root_name;
    };
    HtmlBuilder& add_child(std::string child_name, std::string child_text) {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    //print entire html
    std::string str() const { return root.str(); };

    //override cast from HtmlBuilder to HtmlElement
    operator HtmlElement() const { return root; };

};

int builder_example() {

    /*
    auto text = "Hello";
    std::string output;
    output += "<p>";
    output += text;
    output += "</p>";
    std::cout << output << std::endl;

    //string stream / string building approach
    //better than concatenation
    std::string words[] = { "hello", "world" };
    std::ostringstream oss;
    oss << "<ul>" << std::endl;
    for (auto w : words) {
        oss << "    <li>" << w << "<li>" << std::endl;
    }

    oss << "</ul>";
    std::cout << oss.str();
    */

    HtmlBuilder builder{"ul"};
    //creating a fluent interface
    //from return *this with a <T>&
    builder.add_child("li", "hello").add_child("li", "world");

    std::cout << builder.str() << std::endl;

    //With a static auto builder
    //This does require public constructors however or via a friend class
    //specifying a friend, friend's have access to private members (properties & methods)

    auto new_builder = builder.add_child("li", "fluent").add_child("li", "builder");
    HtmlElement root = builder;
    
    return 0;
}

/*
Groovy Style
Builder

Uniform initialisation syntax
define a structure called a tag
*/

struct Tag {

    std::string name, text;
    std::vector<Tag> children;
    std::vector< std::pair<std::string, std::string> > attributes;

    //print all of the children and content correctly
    friend std::ostream& operator << (std::ostream& os, const Tag& tag) {
        os << "<" << tag.name;

        for (const auto& att : tag.attributes) {
            os << " " << att.first << "=\"" << att.second << "\"";
        }

        if (tag.children.size() == 0 && tag.text.length() == 0) {
            os << "/>" << std::endl;
        }

        else {
            os << ">" << std::endl;

            if(tag.text.length()) {
                os << tag.text << std::endl;
            }
            //should recursively reuse this code block as << is overriden for a Tag object
            for (const auto& child : tag.children) {
                os << child;
            }
            os << "</" << tag.name << ">" << std::endl;
        }
        return os;
    }
    protected:
        Tag(const std::string& name, const std::string& text) : name(name), text(text) {}
        Tag(const std::string& name, const std::vector<Tag>& children) : name(name), children(children) {}
};

//Paragraph Tag which inherits from Base class Tag
struct P : Tag {
    //always send "P" as a super call to parent constructor
    P(const std::string& text) : Tag("P", text) {};
    P(const std::initializer_list<Tag> children ) : Tag("p", children) {};

};

//Image tag. URL of image you want to show
//Unusual domain specific language, to construct html
struct IMG : Tag {
    explicit IMG(const std::string& url) : Tag("img", "") {
        attributes.emplace_back(std::make_pair("src", url));
    }
};

int groovy_builder() {
    /*
    sudo domain specific language
    define different constructors on these elements
    */
    
    std::cout << P{
        IMG{ "http://pokemon.com/pikachu.png"}
    } << std::endl;    

    return 0;
}