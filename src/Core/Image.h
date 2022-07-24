#include <iostream>
#include <cstring>

#include "../ImageMath/DCT.h"

class Image {
public:
    Image();
    void fromBits(uint8_t* bits, 
                    const int32_t &imageX, 
                    const int32_t &imageY);
    uint8_t* getBitsModified();
    uint8_t* getBitsOriginal();

    void doDCT();
    void changeDCT(const int& DCT_Value);

private:
    void doDCTchannel(const int32_t &channels, const int32_t &channelselected);
    void doIDCT();

    int32_t imageX;
    int32_t imageY;

    uint8_t* imageBitsOriginal;
    uint8_t* imageBitsModified;
    uint8_t* imageDCT;
};