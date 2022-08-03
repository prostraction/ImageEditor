#include <iostream>
#include <cmath>
#include <cstring>

class DWT {
public:
    DWT();
    DWT(const uint32_t &_channels, const uint32_t &_dataOneChannelSize);
    ~DWT();

    void setChannels(const uint32_t &_channels);
    void setDataOneChannelSize(const uint32_t &_dataOneChannelSize);
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
    uint32_t channels;
    uint32_t dataOneChannelSize;
};