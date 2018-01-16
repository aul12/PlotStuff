//
// Created by paul on 15.01.18.
//

#ifndef KOMISCHESPLOTTINGDINGS_XWRITER_HPP
#define KOMISCHESPLOTTINGDINGS_XWRITER_HPP

#include "ImageWriter.hpp"

#include <X11/Xlib.h>

class XWriter : public ImageWriter{
public:
    XWriter(int32_t width, int32_t height);
    void set(uint32_t x, uint32_t y, uint8_t r, uint8_t b, uint8_t g) override;
    void clear() override;
    void write() override;
private:
    Display* display;
    Window  win;
    GC gc;
    int screen_num;
};


#endif //KOMISCHESPLOTTINGDINGS_XWRITER_HPP
