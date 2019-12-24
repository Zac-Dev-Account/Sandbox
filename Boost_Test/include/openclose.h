#include <string>
#include <vector>
#include <iostream>

enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product {
    std::string name;
    Color color;
    Size size;
};

//OpenClose Principle
//Your systems should be open to extension
//So that they can be extended by inheritance, but closed for modification
//We do not want to modify existing code
//Specification Pattern, a pattern related to data.

struct ProductFilter {
    std::vector<Product*> by_color(std::vector<Product*> items, Color color) {
        std::vector<Product*> result;
        for (auto& i : items ) {
            if ( i->color == color) {
                result.push_back(i);
            }
        }
        return result;
    }
};

//Does item meet specification? Defined by inheritance
template <typename T> struct Specification {
    virtual bool is_satisified(T* item) = 0;
};

template <typename T> struct Filter {
    virtual std::vector<T*> filter(std::vector<T*> items, 
                              Specification<T>& spec) = 0;
};

//override is before implementation {}
struct BetterFilter : Filter<Product> {
    std::vector<Product *> filter(std::vector<Product*> items, Specification<Product> &spec) override {
        std::vector<Product*> result;
        for (auto& item : items) {
            if (spec.is_satisified(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

struct ColorSpecification : Specification<Product> {
    Color color;
    ColorSpecification(Color color) : color(color) {};
    bool is_satisified(Product* item) override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product> {
    Size size;

    explicit SizeSpecification(const Size size) : size(size) {

    }

    bool is_satisified(Product* item) override {
        return item->size == size;
    }
};

//Can combine these specifications with a combinator
//very generic, combine args of left & right specifications
//Can go further and make this a loop
template <typename T> struct AndSpecification : Specification<T>
{
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T> &first, Specification<T> &second) : first(first), second(second) {}

    bool is_satisified(Product* item) override {
        return first.is_satisified(item) && second.is_satisified(item);
    }
};

int openclose() {
    Product apple {"Apple", Color::green, Size::small};
    Product tree {"Tree",Color::green, Size::large};
    Product house {"House",Color::blue, Size::large};

    //addresses of values as args
    std::vector<Product*> items { &apple, &tree, &house };

    BetterFilter bf;
    ColorSpecification green(Color::green);
    for ( auto& item : bf.filter(items, green)) {
        std::cout << item->name << " is green\n";
    }

    SizeSpecification large(Size::large);
    //Specification combinator
    AndSpecification<Product> green_and_large(green, large);

    for (auto& item : bf.filter(items, green_and_large)) {
        std::cout << item->name << " is green & large\n";
    }

    return 0;
}