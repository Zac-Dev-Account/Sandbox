#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_
#include<cstdint>

//makes c++ allign all structs on 2 byte boundaries, rather than putting extra padding in

    //two bytes containinng letters B and M for bitmap file
    //must be 32 bit for file format
    //guaranteed to be 32bits, written directly to the file
namespace bitTest{

#pragma pack(push, 2)

    struct BitmapFileHeader {
        char header[2] { 'B', 'M' };
        int32_t fileSize;
        int32_t reserved { 0 };
        int32_t dataOffset;
    };

#pragma pack(pop)

}

#endif