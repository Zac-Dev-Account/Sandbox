#include<iostream>

class Rectangle {
    protected:
        int width, height;

    public:
        Rectangle(int width, int height): width(width), height(height) {

        }

        int getWidth() const {
            return width;
        }

        int getHeight() const {
            return height;
        }

        virtual void setWidth(int width) {
            this->width = width;
        }

        virtual void setHeight(int height) {
            this->height = height;
        }

        int area() const { return width * height; }
};

void process(Rectangle& r) {
    int w = r.getWidth();
    r.setHeight(10);
    std::cout << "Expected area = " << (w*10) << ", got " << r.area() << std::endl;
}

//Better to use factories than break Liskov subsitution principle

struct RectangleFactory {
    static Rectangle create_rectangle(int w, int h);
    static Rectangle create_square(int size);

    //derived classes via polymorphism should be able to be
    //substituted effortlessly without error into any location
    //where a base class is being called
};

class Square : public Rectangle {
    public:
        Square(int size): Rectangle(size, size) {}

        //Liskov substitution principle
        //Any derived class should be ableto be substituted into this function
        //without any problems

        //Get 100 instead of 50 if 5 is passed in as width
        virtual void setWidth(int width) override {
            this->width = width;
            this->height = width;
        }

        virtual void setHeight(int height) override {
            this->height = height;
            this->width = height;
        }
};

int liskov_substitution() {
    Rectangle r{3, 4};
    process(r);

    Square sq{5};
    process(sq);
    return 0;
}