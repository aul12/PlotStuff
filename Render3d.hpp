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
    double xScale, yScale, zScale;
    double rotation;
    double offsetX, offsetY;
};

class Render3d {
public:
    void addPoint(Point3d point);
    void render(ImageWriter* writer, RenderConfig config);
    void clear();
private:
    std::vector<Point3d> points;
};


#endif //KOMISCHESPLOTTINGDINGS_RENDER3D_HPP
