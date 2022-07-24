#include <iostream>
#include <cstring>

#include "../ImageMath/DCT.h"

class Image {
public:
    Image();
    void fromBits(uint8_t* bits, 
                    const uint32_t &imageX, 
                    const uint32_t &imageY);
    uint8_t* getBitsModified();
    uint8_t* getBitsOriginal();
    uint32_t getImageX() {return imageX;}
    uint32_t getImageY() {return imageY;}

    void doDCT();
    void changeDCT(const int& DCT_Value);

private:
    void doDCTchannel(const int32_t &channels, const int32_t &channelselected);
    void doIDCT();

    uint32_t imageX;
    uint32_t imageY;

    uint8_t* imageBitsOriginal;
    uint8_t* imageBitsModified;
    uint8_t* imageDCT;
};