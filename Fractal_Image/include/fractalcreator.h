#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include<string>
#include <zoom.h>
#include <zoomList.h>
#include <mandelbrot.h>
#include <bitmap.h>

namespace bitTest {
    class FractalCreator {
    private:
        int m_width;
        int m_height;
        std::unique_ptr<int[]> m_histogram;
        std::unique_ptr<int[]> m_fractal;
        Bitmap m_bitmap;
        ZoomList m_zoomList;
        int m_total{0};

    public:
        FractalCreator(int width, int height);
        virtual ~FractalCreator();

        void calculateIteration();
        void calculateTotalIterations();
        void drawFractal();
        void addZoom(const Zoom& zoom);
        void writeBitmap(std::string name);
    };

}

#endif