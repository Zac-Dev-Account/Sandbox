#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include<complex>

namespace bitTest {
    class Mandelbrot {
        public:
            //The more iterations youdo for each pixel, the better quality you get for the image
            //Trade off with performance / rendering time
            static const int MAX_ITERATIONS = 1000;
            
        public:
            Mandelbrot();
            virtual ~Mandelbrot();
            static int getIterations(double x, double y );

    };
}
#endif