#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include<string>
#include <zoom.h>

namespace bitTest {
    class FractalCreator {
        public:
            FractalCreator(int width, int height);
            virtual ~FractalCreator();

            void calculateIteration();
            void drawFractal();
            void writeBitmap(std::string name);
            void addZoom(const Zoom& zoom);

    };
}

#endif