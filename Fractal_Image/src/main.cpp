#include<iostream>
#include<cmath>
#include "bitmap.h"
#include "mandelbrot.h"
#include "zoom.h"
#include "zoomList.h"
#include "fractalcreator.h"

using namespace bitTest;
int main(int argc, char const *argv[])
{
    //mandelbrot fractal image
    //algorithm generated images

    //bitmap file format, example code
    //write a bunch of bytes to top of bitmap file to make it a valid file
    int const WIDTH = 800;
    int const HEIGHT = 600;
    Bitmap bitmap(WIDTH, HEIGHT);
    //x is 0 at the left, y is 0 at the bottom, y bottom to top, x left to right
    //fractal values x/y range from -1 to +1
    //scaling is requicolor
    double min{999999};
    double max{-999999};

    ZoomList zoomList(WIDTH, HEIGHT);
    //as you zoom in it gets slower, more and more pixels with higher resolutions
    zoomList.add(Zoom(WIDTH/2, HEIGHT/2, 4.0/WIDTH));
    zoomList.add(Zoom(295, HEIGHT - 202, 0.1));
    zoomList.add(Zoom(312, HEIGHT - 304, 0.1));
    //histogram colouring algorithm
    //Try to avoid out by 1 errors, common in CPP
    //{0} or () to initialize values to 0
    int* histogram = new int [Mandelbrot::MAX_ITERATIONS]{0};
    int* fractal = new int [WIDTH*HEIGHT] {0};

    //BUILDING THE HISTOGRAM
    for (int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            //bitmap.setPixel(x, y, 255, 0, 0);
            //result in a scaled width value from -1 to 1

            //scalling by different resolutions here, squashes our mandelbrot image, as it should fit
            //in a perfectly square space
            std::pair<double, double> coords = zoomList.doZoom(x,y);

            //find out how many pixels have 100 iterations or have 1000, etc
            //A different number of pixels from every number of iterations that ahve that number of iterations for them
            int iterations = Mandelbrot::getIterations(coords.first, coords.second);
            //float point number up to a maxim of 256
            //don't write into mem we haven't allocated
            //smaller and smaller number of pixels aas iterations increase
            //Start at bottom lefthand corner for bitmaps
            //count pixels numbering from left to right and counting across, this is how we save each index for each pixel in our fractal array
            //Makes sense because you start at y = 0 :/
            fractal[y*WIDTH+x] = iterations;
            if (iterations != Mandelbrot::MAX_ITERATIONS) { histogram[iterations]++; }
        }
    }

    //get total iterations per pixel
    int total = 0;
    for ( int i=0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        total += histogram[i];
    }

    //num of iterations for each pixel
    for (int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {

            std::uint8_t red{0};
            //power will be some fractional number
            std::uint8_t green{0};
            std::uint8_t blue{0};
            //iteratons have been mapped against our fractal coordinates
            //Drawing code into a second nested loop now  
            int iterations = fractal[y * WIDTH + x];

            if( iterations != Mandelbrot::MAX_ITERATIONS) {
                double hue = 0.0f;
                //move from pixels from a low number to a high number of iterations we calculate a colour
                //increase the colour value by an amount proportional to the number of iterations
                for(int i=0; i <= iterations; i++) { 
                    //changing the colour by an amount proportional to the present number
                    hue += ((double) histogram[i]) / total; 
                }
                green = std::pow(255, hue);
            }

            bitmap.setPixel(x, y, red, green, blue);
        }
    }

    bitmap.write("test.bmp");
    std::cout << "Finished!" << std::endl;

    //Clean up memory on Heap
    delete [] histogram;
    delete [] fractal;
    return 0;
}
