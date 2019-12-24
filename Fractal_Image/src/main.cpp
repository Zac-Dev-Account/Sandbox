#include<iostream>
#include<cmath>
#include "bitmap.h"
#include "mandelbrot.h"
#include "zoom.h"
#include "zoomList.h"
#include "fractalcreator.h"

using namespace bitTest;

    //mandelbrot m_fractal image
    //algorithm generated images

int main(int argc, char const *argv[])
{
	int height = 600;

	FractalCreator fractalCreator(800, 600);

	fractalCreator.addZoom(Zoom(295, height - 202, 0.1));
	fractalCreator.addZoom(Zoom(312, height - 304, 0.1));
	fractalCreator.calculateIteration();
	fractalCreator.calculateTotalIterations();
	fractalCreator.drawFractal();
	fractalCreator.writeBitmap("test.bmp");

	std::cout << "Finished." << std::endl;
	return 0;
}