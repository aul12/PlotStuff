//
// Created by paul on 15.01.18.
//

#ifndef KOMISCHESPLOTTINGDINGS_RENDER3D_HPP
#define KOMISCHESPLOTTINGDINGS_RENDER3D_HPP


#include <vector>
#include <cstdint>

#include "Output/ImageWriter.hpp"
#include "Point3d.hpp"

struct RenderConfig {
    double zTilt;
    double rotation;
};

class Render3d {
public:
    Render3d();
    void addPoint(Point3d point);
    void render(ImageWriter* writer, RenderConfig config);
    void clear();
private:
    std::vector<Point3d> points;
    double rMax, zMax;
};


#endif //KOMISCHESPLOTTINGDINGS_RENDER3D_HPP
