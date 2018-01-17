//
// Created by paul on 16.01.18.
//

#include "Plot.hpp"

Plot::Plot(double range, double res, bool axisEnabled) {
    this->range = range;
    this->res = res;
    this->axisEnabled = axisEnabled;
}

void Plot::draw(std::function<std::complex<double>(std::complex<double>)> f, Render3d *renderer) {
    renderer->clear();

    Point3d point3d{};
    if(axisEnabled) {
        point3d.color = 0xFFFFFF;
        for(double c=-range; c<range; c+=res) {
            point3d.x = c;
            point3d.y = 0;
            point3d.z = 0;
            renderer->addPoint(point3d);
            point3d.x = 0;
            point3d.y = c;
            point3d.z = 0;
            renderer->addPoint(point3d);
            if(c >= 0) {
                point3d.x = 0;
                point3d.y = 0;
                point3d.z = c;
                renderer->addPoint(point3d);
            }
        }
        for(double c=range-0.3; c<range; c+=res) {
            for(int a = 0; a<16; a++) {
                point3d.x = c;
                point3d.y = sin(a/16.0 * 2 * M_PI) * (range-c);
                point3d.z = cos(a/16.0 * 2 * M_PI) * (range-c);
                renderer->addPoint(point3d);
                point3d.z = c;
                point3d.y = sin(a/16.0 * 2 * M_PI) * (range-c);
                point3d.x = cos(a/16.0 * 2 * M_PI) * (range-c);
                renderer->addPoint(point3d);
                point3d.y = c;
                point3d.x = sin(a/16.0 * 2 * M_PI) * (range-c);
                point3d.z = cos(a/16.0 * 2 * M_PI) * (range-c);
                renderer->addPoint(point3d);
            }
        }
    }

    for(double x=-range; x<=range; x+=res) {
        for(double y=-range; y<=range; y+=res) {
            std::complex<double> v = f(std::complex<double>(x,y));

            point3d.x = x;
            point3d.y = y;
            point3d.z = std::abs(v);
            point3d.color = getColor(v);

            renderer->addPoint(point3d);
        }
    }
}

uint32_t Plot::getColor(std::complex<double> z) {
    double arg = std::arg(z);

    const double TRI_WIDTH = M_PI/1.5;

    auto r = (uint8_t)((tri(arg + M_PI, TRI_WIDTH) + tri(arg - M_PI, TRI_WIDTH)) * 255);
    auto g = (uint8_t)(tri(arg + M_PI/3, TRI_WIDTH)*255);
    auto b = (uint8_t)(tri(arg - M_PI / 3, TRI_WIDTH) * 255);

    return r << 16 | g << 8 | b;
}

double Plot::tri(double x, double w) {
    if (fabs(x/w) > 1) {
        return 0;
    } else {
        return 1 - fabs(x/w);
    }
}
