//
// Created by paul on 16.01.18.
//

#include "Pcd.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

Pcd::Pcd(bool axisEnabled, float axisLength) : axisEnabled{axisEnabled}, axisLength{axisLength} {}

void Pcd::draw(Render3d *renderer, std::string fname) {
    renderer->clear();
    this->drawAxis(renderer, false);

    std::ifstream ifstream{fname};

    std::string version, fields, size, type, count, width, height, viewpoint, numPoints, data;
    std::getline(ifstream, version);
    std::getline(ifstream, fields);
    std::getline(ifstream, size);
    std::getline(ifstream, type);
    std::getline(ifstream, count);
    std::getline(ifstream, width);
    std::getline(ifstream, height);
    std::getline(ifstream, viewpoint);
    std::getline(ifstream, numPoints);
    std::getline(ifstream, data);

    for (std::string line; std::getline(ifstream, line); ) {
        std::stringstream stringstream{line};
        Point3d point{};
        stringstream >> point.x >> point.y >> point.z;
        point.color = 0xFF0000;
        renderer->addPoint(point);
    }
}


void Pcd::drawAxis(Render3d *renderer, bool negEnabled) {
    Point3d point{};
    if(axisEnabled) {
        point.color = 0xFFFFFF;
        for(double c=-axisLength; c<axisLength; c+=0.001) {
            point.x = c;
            point.y = 0;
            point.z = 0;
            renderer->addPoint(point);
            point.x = 0;
            point.y = c;
            point.z = 0;
            renderer->addPoint(point);
            if(negEnabled || c >= 0) {
                point.x = 0;
                point.y = 0;
                point.z = c;
                renderer->addPoint(point);
            }
        }
        for(double c=axisLength*0.97; c<axisLength; c+=0.001) {
            for(int a = 0; a<64; a++) {
                point.x = c;
                point.y = sin(a/64.0 * 2 * M_PI) * (axisLength-c);
                point.z = cos(a/64.0 * 2 * M_PI) * (axisLength-c);
                renderer->addPoint(point);
                point.z = c;
                point.y = sin(a/64.0 * 2 * M_PI) * (axisLength-c);
                point.x = cos(a/64.0 * 2 * M_PI) * (axisLength-c);
                renderer->addPoint(point);
                point.y = c;
                point.x = sin(a/64.0 * 2 * M_PI) * (axisLength-c);
                point.z = cos(a/64.0 * 2 * M_PI) * (axisLength-c);
                renderer->addPoint(point);
            }
        }
    }
}
