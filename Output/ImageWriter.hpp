//
// Created by paul on 15.01.18.
//

#ifndef KOMISCHESPLOTTINGDINGS_IMAGEWRITER_HPP
#define KOMISCHESPLOTTINGDINGS_IMAGEWRITER_HPP

#include <cstdint>
#include <string>


class ImageWriter {
public:
    ImageWriter(int32_t width, int32_t height) {
        this->width = width;
        this->height = height;
    }
    virtual void set(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void write() = 0;
    virtual void clear() = 0;
    int32_t width, height;
};


#endif //KOMISCHESPLOTTINGDINGS_IMAGEWRITER_HPP
