#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_
#include<cstdint>

//makes c++ allign all structs on 2 byte boundaries, rather than putting extra padding in
#pragma pack(2)

    //two bytes containinng letters B and M for bitmap file
    //must be 32 bit for file format
    //guaranteed to be 32bits, written directly to the file
namespace bitTest{

    struct BitmapFileHeader {
        char header[2]{ 'B', 'M' };
        int32_t fileSize;
        int32_t reserved { 0 };
        int32_t dataOffset;
    };
}


#endif