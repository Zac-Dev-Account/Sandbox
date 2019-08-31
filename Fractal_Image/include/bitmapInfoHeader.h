#ifndef BITMAPINFOHEADER_H_
#define BITMAPINFOHEADER_H_

#include <cstdint>
#pragma pack(2)

//best for portability to use ints with there required bitSize, guaranteed to be the right number of bits
//pragma pack to remove padding from our struct
//headerSize, actual size of the struct 32 = 4 bytes, 16 = 2 bytes
//width /height = actual width of the bitmap
//planes layer feature of bitMap

//1 byte for each colour in the bit map, rgb, 24 = 3 bytes
//set dataSize to size of data that we write to the bitmap file
//
namespace bitTest{

    struct BitmapInfoHeader {
        int32_t headerSize{40};
        int32_t width;
        int32_t height;
        int16_t planes{1};
        int16_t bitsPerPixel{24};
        int32_t compression{0};
        int32_t dataSize{0};
        int32_t horizontalResolution{2400};
        int32_t verticalResolution{2400};
        int32_t colors{0};
        int32_t importantColors{0};
    };

}

#endif