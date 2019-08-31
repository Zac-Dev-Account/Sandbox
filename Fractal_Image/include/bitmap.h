#ifndef BITMAP_H_
#define BITMAP_H_

#include<string>
#include <fstream>
#include <cstdint>
#include <memory>
namespace bitTest{
    class Bitmap {
        private:
            int m_width{0};
            int m_height{0};
            std::unique_ptr<std::uint8_t[]> m_pPixels{nullptr};


        public:
            Bitmap(int width, int height);
            //specify colours int he bitmap
            //2D pixels, x & y coords with an RGB value 0-255 
            void setPixel(int x, int y, std::uint8_t red, std::uint8_t green, std::uint8_t blue);
            virtual ~Bitmap();
            //Write to disk with filename for bitmap
            bool write(std::string fileName);
    };
}

#endif