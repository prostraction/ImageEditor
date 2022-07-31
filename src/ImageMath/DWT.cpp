#include "DWT.h"

DWT::DWT() {
    data = nullptr;
    channels = 0;
    dataOneChannelSize = 0;
}
DWT::DWT(const uint32_t &_channels, const uint32_t &_dataOneChannelSize) {
    channels = _channels;
    dataOneChannelSize = _dataOneChannelSize;
    data = (double*)malloc(2 * channels * dataOneChannelSize);
}
DWT::~DWT() {
    if (data)
        free(data);
}
void DWT::setChannels(const uint32_t &_channels) {
    channels = _channels;
}
void DWT::setDataOneChannelSize(const uint32_t &_dataOneChannelSize) {
    dataOneChannelSize = _dataOneChannelSize;
}
void DWT::allocData() {
    if (data == nullptr)
        data = (double*)malloc(2 * channels * dataOneChannelSize);
}
void DWT::freeData() {
    if (data) {
        free(data);
        data = nullptr;
    }
}
void DWT::doFWT97(const uint8_t* input) {

}
void DWT::doFWT53(const uint8_t* input) {
    double a = -0.5;
    for (int i = 1 + channels; i < dataOneChannelSize * channels - (2 * channels); i+= 2 * channels) {
        for (int j = i; j < channels; j++)
            data[j] += a * (data[j-channels] + data[j+channels]);
    }
    data[]
}