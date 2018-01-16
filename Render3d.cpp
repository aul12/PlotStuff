//
// Created by paul on 15.01.18.
//

#include <cmath>
#include <algorithm>
#include "Render3d.hpp"

void Render3d::addPoint(Point3d point) {
    points.push_back(point);
}

void Render3d::render(ImageWriter* writer, RenderConfig config) {
    double xCam, yCam, zCam;

    xCam = cos(config.rotation) * 1000;
    yCam = sin(config.rotation) * 1000;
    zCam = sin(config.zTilt) * 1000;

    std::sort(points.begin(), points.end(), [xCam, yCam, zCam](Point3d a, Point3d b) {
        double aDist = SQR(a.x - xCam) + SQR(a.y - yCam) + SQR(a.z - zCam);
        double bDist = SQR(b.x - xCam) + SQR(b.y - yCam) + SQR(b.z - zCam);

        return (aDist < bDist);
    });

    writer->clear();

    double cosRot = cos(config.rotation);
    double sinRot = sin(config.rotation);
    double sinTilt = sin(config.zTilt);
    double cosTilt = cos(config.zTilt);

    for (auto &point : points) {
        double x,y,z;

        // Rotate around z-Axis
        x = (cosRot * point.x - sinRot * point.y);
        y = (sinRot * point.x + cosRot * point.y);
        z = point.z;

        // Scale
        x *= config.xScale;
        y *= config.yScale;
        z *= config.zScale;

        // Tilt
        y = z * cosTilt + y * sinTilt;

        // Center on image
        x += writer->width/2;
        y += writer->height/2;

        // Offset
        x += config.offsetX;
        y += config.offsetY;

        if(x >= 0 && y >= 0 && x < writer->width &&  y < writer->height) {
            auto r = (uint8_t)((point.color & 0xFF0000) >> 16);
            auto g = (uint8_t)((point.color & 0xFF00) >> 8);
            auto b = (uint8_t)(point.color & 0xFF);

            writer->set((uint32_t)x, (uint32_t)y, r, g, b);
        }
    }
    writer->write();
}

void Render3d::clear() {
    points.clear();
}
