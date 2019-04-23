//
// Created by paulnykiel on 23.04.19.
//

#include "SfmlWriter.h"

SfmlWriter::SfmlWriter(uint32_t width, uint32_t height) : ImageWriter(width, height),
    renderWindow{sf::VideoMode{width, height}, "Test"} {
    buffer.create(width, height, sf::Color::Black);
}

void SfmlWriter::set(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
    buffer.setPixel(x, y, sf::Color{r,g,b});
}

void SfmlWriter::write() {
    renderWindow.clear(sf::Color::Black);
    sf::Texture texture;
    texture.loadFromImage(buffer);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    renderWindow.draw(sprite);
    renderWindow.display();
}

void SfmlWriter::clear() {
    renderWindow.clear(sf::Color::Black);
    for (auto x = 0; x < width; x++) {
        for (auto y = 0; y < height; y++) {
            buffer.setPixel(x,y,sf::Color::Black);
        }
    }
}
