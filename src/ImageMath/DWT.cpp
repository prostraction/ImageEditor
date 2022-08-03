#include "DWT.h"

DWT::DWT() {
    data = nullptr;
    buffer = nullptr;
    channels = 0;
    dataOneChannelSize = 0;
}
DWT::DWT(const uint32_t &_channels, const uint32_t &_dataOneChannelSize) {
    channels = _channels;
    dataOneChannelSize = _dataOneChannelSize;
    data = (double*)malloc(channels * dataOneChannelSize * sizeof(double));
    buffer = (double*)malloc(2 * channels * dataOneChannelSize * sizeof(double));
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
    if (data == nullptr) {
        data = (double*)malloc(channels * dataOneChannelSize * sizeof(double));
        buffer = (double*)malloc(2 * channels * dataOneChannelSize * sizeof(double));
    }
}
void DWT::freeData() {
    if (data) {
        free(data);
        free(buffer);
        data = nullptr;
        buffer = nullptr;
    }
}
void DWT::doFWT97(const uint8_t* input) {

}
void DWT::doFWT53(const uint8_t* input) {
    // P1
    double a = -0.5;
    for (int i = channels; i < dataOneChannelSize * channels - (2 * channels); i+= 2 * channels) {
        for (int j = i; j < channels; j++) {
            data[j] += a * (data[j-channels] + data[j+channels]);
        }
    }
    for (int i = dataOneChannelSize * channels - (2 * channels), j = 1; i < dataOneChannelSize * channels; i++, j += 2) {
        data[i] += 2 * a * data[i-j];
    }
    // U1
    a = 0.25;
    for (int i = 2 * channels; i < dataOneChannelSize * channels; i += 2 * channels) {
        for (int j = i; j < channels; j++) {
            data[j] += a * (data[j-channels] + data[j+channels]);
        }
    }
    for (int i = 0; i < channels; i++) {
        data[i] += 2 * a * data[i + channels];
    }

    // S
    a = sqrt(2.d);
    for (int i = 0; i < dataOneChannelSize * channels; i++) {
        if (i % 2 == 1) {
            data[i] *= a;
        }
        else {
            data[i] /= a;
        }
    }

    // Pack
    for (int i = 0; i < dataOneChannelSize * channels; i++) {
        if (i % 2 == 0) {
            buffer[i/2] = data[i];
        }
        else {
            buffer[(dataOneChannelSize * channels) / 2 + i / 2] = data[i];
        }
    }
    for (int i = 0; i < dataOneChannelSize * channels; i++) {
        data[i] = buffer[i];
    }

}