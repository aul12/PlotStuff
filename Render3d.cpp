//
// Created by paul on 15.01.18.
//

#include <cmath>
#include <algorithm>
#include "Render3d.hpp"

void Render3d::addPoint(Point3d point) {
    /*for(auto iterator = points.begin(); iterator != points.end(); iterator++) {
        if(point.norm2() > iterator->norm2()) {
            points.insert(iterator, point);
            return;
        }
    }*/
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

        return (aDist > bDist);
    });

    writer->clear();

    double cosRot = cos(config.rotation);
    double sinRot = sin(config.rotation);
    double sinTilt = sin(config.zTilt);
    double cosTilt = cos(config.zTilt);

    for(auto iterator = points.begin(); iterator != points.end(); iterator++) {
        double x,y,z;

        // Rotate around z-Axis
        x = (cosRot * iterator->x - sinRot * iterator->y);
        y = (sinRot *  iterator->x + cosRot * iterator->y);
        z = iterator->z;

        // Scale
        x *= config.xScale;
        y *= config.yScale;
        z *= config.zScale;

        // Center on image
        x += writer->width/2;
        y += writer->height/2;

        // Tilt
        y = z * cosTilt + y * sinTilt;

        // Offset
        x += config.offsetX;
        y += config.offsetY;

        if(x >= 0 && y >= 0 && x < writer->width &&  y < writer->height) {
            auto r = (uint8_t)((iterator->color & 0xFF0000) >> 16);
            auto g = (uint8_t)((iterator->color & 0xFF00) >> 8);
            auto b = (uint8_t)(iterator->color & 0xFF);

            writer->set((uint32_t)x, (uint32_t)y, RED, r);
            writer->set((uint32_t)x, (uint32_t)y, GREEN, g);
            writer->set((uint32_t)x, (uint32_t)y, BLUE, b);
        }
    }
    writer->write();
}
