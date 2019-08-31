#include "bitmap.h"
#include "bitmapFileHeader.h"
#include "bitmapInfoHeader.h"

namespace bitTest {
    //1 byte for each colour channel for each pixel in area of width & height
    //init array mem to all 0s with {}
    Bitmap::Bitmap(int width, int height): m_width(width), m_height(height), m_pPixels(new std::uint8_t[width * height * 3]{0}) {

    }

    Bitmap::~Bitmap() {

    }

    bool Bitmap::write(std::string filename) {
        BitmapFileHeader fileHeader;
        BitmapInfoHeader infoHeader;

        fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + m_width*m_height*3;
        //data starts after these headers where the bitmp data is located
        fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

        infoHeader.width = m_width;
        infoHeader.height = m_height;

        std::ofstream file;
        file.open(filename, std::ios::out | std::ios::binary);
        //check if opened correctly
        if( !file ) {
            return false;
        }
        
        file.write((char *)&fileHeader, sizeof(fileHeader));
        file.write((char *)&infoHeader, sizeof(infoHeader));
        file.write((char *)m_pPixels.get(), m_width*m_height*3);

        file.close();
        //check if closed correctly
        if( !file ) {
            return false;
        }

        return true;
    }

    void Bitmap::setPixel(int x, int y, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
        std::uint8_t *pPixel = m_pPixels.get();
        pPixel += (y* 3) * m_width + (x *3);

        pPixel[0] = blue;
        pPixel[1] = green;
        pPixel[2] = red;

    }
    
}