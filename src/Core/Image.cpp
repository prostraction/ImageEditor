#include "Image.h"

Image::Image() {
    imageBitsOriginal = nullptr;
    imageBitsModified = nullptr;
    imageDCT = nullptr;
    imageX = 0; imageY = 0;
}

void Image::fromBits(uint8_t* bits, 
                        const uint32_t &_imageX, 
                        const uint32_t &_imageY) {
    imageX = _imageX;
    imageY = _imageY;
    imageBitsOriginal   = (uint8_t*) malloc(imageX * imageY * 3 * sizeof(uint8_t));
    imageBitsModified   = (uint8_t*) malloc(imageX * imageY * 3 * sizeof(uint8_t));
    imageDCT            = (double*) malloc(imageX * imageY * 3 * sizeof(double));
    memcpy(imageBitsOriginal,   bits, imageX * imageY * 3 * sizeof(uint8_t));
    memset(imageBitsModified,   0, imageX * imageY * 3 * sizeof(uint8_t));
    memset(imageDCT,            0, imageX * imageY * 3 * sizeof(double));
}

uint8_t* Image::getBitsModified() {
    return imageBitsModified;
}

uint8_t* Image::getBitsOriginal() {
    return imageBitsOriginal;
}

void Image::changeDCT(const int& DCT_Value) {
    for (uint32_t i = 0; i < imageX * imageY * 3; i++) {
        imageBitsModified[i] = imageDCT[i] + ((double)DCT_Value/5.d);
    }

}

void Image::doDCT() {
    doDCTchannel(3, 0);
    doDCTchannel(3, 1);
    doDCTchannel(3, 2);
}

void Image::doDCTchannel(const int32_t &channels, const int32_t &channelselected) {
    if (imageX <= 0 || imageY <= 0)
        return;
    if (imageBitsOriginal == nullptr)
        return;
    if (imageDCT == nullptr)
        return;

    double* dct8x8  = new double[64];
    double* idct8x8 = new double[64];
    memset(dct8x8, 0, 64 * sizeof(double));
    memset(idct8x8, 0, 64 * sizeof(double));
    
    for (uint32_t x = 0; x < imageX - imageX % 8 - 1; x += 8) {
        for (uint32_t y = 0; y < imageY - imageY % 8 - 1; y += 8) {
            DCT::doDCT(dct8x8, imageBitsOriginal, x, y, imageX, channels, channelselected);
            for (int32_t i = 0; i < 8; i++) {
                for (int32_t j = 0; j < 8; j++)
                    imageDCT[channelselected + (channels * ((j + x) + imageX * (i+y)))] = dct8x8[8*i + j];
            }
        }
    }

    delete[] dct8x8;
    delete[] idct8x8;
}

void Image::doIDCT() {
    
}