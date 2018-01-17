//
// Created by paul on 15.01.18.
//

#ifndef KOMISCHESPLOTTINGDINGS_BMPWRITER_HPP
#define KOMISCHESPLOTTINGDINGS_BMPWRITER_HPP

#include <cstdint>
#include <string>

#include "ImageWriter.hpp"

class BmpWriter : public ImageWriter{
public:
    BmpWriter(uint32_t width, uint32_t height, std::string fname);
    void set(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) override;
    void write() override;
    void clear() override;
private:
    static void write16(uint8_t* data, int16_t val);
    static void write32(uint8_t* data, int32_t val);
    uint8_t* data;
    std::string fname;
};


#endif //KOMISCHESPLOTTINGDINGS_BMPWRITER_HPP
