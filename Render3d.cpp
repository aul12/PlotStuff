//
// Created by paul on 15.01.18.
//

#include <cmath>
#include <algorithm>
#include "Render3d.hpp"

void Render3d::addPoint(Point3d point) {
    double r = sqrt(point.x * point.x + point.y + point.y);
    if(r > rMax) {
        rMax = r;
    }

    if(fabs(point.z) > zMax) {
        zMax = point.z;
    }
    points.push_back(point);
}

void Render3d::render(ImageWriter* writer, RenderConfig config) {
    double xCam, yCam, zCam;

    xCam = cos(config.rotation) * 100;
    yCam = sin(config.rotation) * 100;
    zCam = -sin(config.zTilt) * 100;

    std::sort(points.begin(), points.end(), [xCam, yCam, zCam](Point3d a, Point3d b) {
        double aDist = SQR(a.x - xCam) + SQR(a.y - yCam) + SQR(a.z - zCam);
        double bDist = SQR(b.x - xCam) + SQR(b.y - yCam) + SQR(b.z - zCam);

        return (aDist < bDist);
    });

    double rScale = writer->width/3 * 1/rMax;
    double zScale = writer->height/2 * 1/zMax;

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
        x *= rScale;
        y *= rScale;
        z *= zScale;

        // Tilt
        y = z * cosTilt + y * sinTilt;

        // Center on image
        x += writer->width/2;
        y += writer->height/2;

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

Render3d::Render3d() {
    zMax = rMax = 0;
}
