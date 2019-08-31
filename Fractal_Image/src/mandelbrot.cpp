#include "mandelbrot.h"
namespace bitTest {
    Mandelbrot::Mandelbrot() {

    }

    Mandelbrot::~Mandelbrot() {

    }

    int Mandelbrot::getIterations(double x, double y) {
        std::complex<double> z = 0;
        std::complex<double> c(x, y);

        int iterations = 0;

        while( iterations < MAX_ITERATIONS) {
            //initially z is 0
             z = z*z + c;
             //squaring and add c to it for each iteration
             //magnitude of the complex number is the length of the line from the origin to that point
            //Mandelbrot set cannot exceed 2, below 2 part of set, not trending to infinity
             if( abs(z) > 2) {
                break;
             }

            iterations++;
        }

        return iterations;
    }

}