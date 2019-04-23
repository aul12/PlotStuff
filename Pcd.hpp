//
// Created by paul on 16.01.18.
//

#ifndef KOMISCHESPLOTTINGDINGS_PCD_HPP
#define KOMISCHESPLOTTINGDINGS_PCD_HPP

#include "Render3d.hpp"

class Pcd {
public:
    explicit Pcd(bool axisEnabled = true, float axisLength = 1);

    void draw(Render3d* renderer, std::string fname);

private:
    void drawAxis(Render3d* renderer, bool negEnabled = true);
    bool axisEnabled;
    float axisLength;
};


#endif
