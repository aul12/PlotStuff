//
// Created by paul on 15.01.18.
//

#include <cstdlib>
#include <iostream>
#include "BmpWriter.hpp"

std::string BmpWriter::fname = "out.bmp";

BmpWriter::BmpWriter(uint32_t width, uint32_t height) : ImageWriter(width, height) {
    data = (uint8_t*)calloc(sizeof(uint8_t), width*height*3+54);
}

void BmpWriter::set(uint32_t x, uint32_t y, uint8_t r, uint8_t b, uint8_t g) {
    data[54+3*(y*width + x)+0] = b;
    data[54+3*(y*width + x)+1] = g;
    data[54+3*(y*width + x)+2] = r;
}

void BmpWriter::write() {
    // Header
    data[0] = 'B';
    data[1] = 'M';
    write32(data+2, width*height*3+54);
    write32(data+6, 0);
    write32(data+10, 54);

    // Information
    write32(data+14, 40);
    write32(data+18, width);
    write32(data+22, height);
    write16(data+26, 1);
    write16(data+28, 24);
    write32(data+30, 0);
    write32(data+34, 0);
    write32(data+38, 0);
    write32(data+42, 0);
    write32(data+46, 0);
    write32(data+52, 0);

    FILE* file = fopen(fname.c_str(), "w");
    if(file == nullptr) {
        return;
    }

    for(int c=0; c<(width*height*3)+54; c++) {
        fputc(data[c], file);
    }
    fclose(file);
}

void BmpWriter::write16(uint8_t *data, int16_t val) {
    for(int c=0; c<4; c++) {
        data[c] = (uint8_t)((val & 0xFF << (c*8)) >> (c*8));
    }
}

void BmpWriter::write32(uint8_t *data, int32_t val) {
    for(int c=0; c<2; c++) {
        data[c] = (uint8_t)((val & 0xFF << (c*8)) >> (c*8));
    }
}

void BmpWriter::clear() {
    free(data);
    data = (uint8_t*)calloc(sizeof(uint8_t), width*height*3+54);
}
