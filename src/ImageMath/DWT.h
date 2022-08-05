#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>

class DWT {
public:
    DWT();
    DWT(const uint32_t &_channels, const uint32_t &ImageX, const uint32_t &ImageY);
    ~DWT();

    void setChannels(const uint32_t &_channels);
    void setX(const uint32_t &ImageX);
    void setY(const uint32_t &ImageY);
    void allocData();
    void freeData();
    void doFWT97(const uint8_t* input);
    void doFWT53(const uint8_t* input);

    uint8_t* getAll();
    uint8_t* getHighFreq();
    uint8_t* getLowFreq();

private:
    void RowFWT53();
    void ColumnFWT53();

    double* data;
    double* buffer;
    uint8_t* dataImage;
    uint32_t channels;
    //uint32_t dataOneChannelSize;
    uint32_t x; uint32_t y;
};