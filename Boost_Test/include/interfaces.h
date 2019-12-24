#include <iostream>

//Do not create interfaces which are too large
//And require inplementers to implement too much

struct Document {

};

// struct IMachine {
//     virtual void print(Document& doc) = 0;
//     virtual void scan(Document& doc) = 0;
//     virtual void fax(Document& doc) = 0;
// };

// struct MFP : IMachine {
//     virtual void print(Document& doc) override {}
//     virtual void scan(Document& doc) override {}
//     virtual void fax(Document& doc) override {}
// };

// struct Scanner : IMachine {
//     //leave as null if the scanner cannot print
//     //sending the client the wrong message.
//     //Telling them the scanner can print which isn't actually true
//     //defined interface is just too big
//     //no client would require to implement print, scan & fax
//     virtual void print(Document& doc) override { }
//     virtual void scan(Document& doc) override {}
//     virtual void fax(Document& doc) override {}
// };

struct IPrinter {
    virtual void print(Document& doc) = 0;
};

struct IScanner {
    virtual void scan(Document& doc) = 0;
};

struct IFax {
    virtual void fax(Document& doc) = 0;
};

struct Printer : IPrinter {
    void print(Document &doc) override {}
};

struct Scanner : IScanner {
    void scan(Document &doc) override {}
};

//segregate like this, good approach
//Remember interfaces just contain virtual methods to be implemented
//in class
struct IMachine : IPrinter, IScanner {

};

struct Machine : IMachine {
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}
    void print(Document &doc) override {
        printer.print(doc);
    }
    void scan(Document &doc) override {
        scanner.scan(doc);
    }
};

int interface_segregation() {
    return 0;
}