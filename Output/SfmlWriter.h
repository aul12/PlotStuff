//
// Created by paulnykiel on 23.04.19.
//

#ifndef KOMISCHESPLOTTINGDINGS_SFMLWRITER_H
#define KOMISCHESPLOTTINGDINGS_SFMLWRITER_H

#include <SFML/Graphics.hpp>

#include "ImageWriter.hpp"

class SfmlWriter : public ImageWriter {
public:
    SfmlWriter(uint32_t width, uint32_t height);

    void set(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) override;
    void write() override;
    void clear() override;
private:
    sf::RenderWindow renderWindow;
    sf::Image buffer;
};


#endif //KOMISCHESPLOTTINGDINGS_SFMLWRITER_H
