//
// Created by paul on 16.01.18.
//

#include "Plot.hpp"

Plot::Plot(double range, double res, bool axisEnabled) {
    this->range = range;
    this->res = res;
    this->axisEnabled = axisEnabled;
}

template<typename I, typename O>
void Plot::draw(Render3d *renderer, std::function<O(I)> f, std::function<bool(I)> set) {
    renderer->clear();
    this->drawAxis(renderer);
}

template<>
void Plot::draw(Render3d *renderer, std::function<std::complex<double>(double)> f, std::function<bool(double)> set) {
    renderer->clear();
    this->drawAxis(renderer);

    Point3d point{};
    for(double x=-range; x<=range; x+=res) {
        if(set(x)) {
            std::complex<double> v = f(x);
            point.x = std::real(v);
            point.y = std::imag(v);
            point.z = x;
            if (std::abs(point.x) < range && std::abs(point.y) < range) {
                point.color = getColor(v);
                renderer->addPoint(point);
            }
        }
    }
}

template<>
void Plot::draw(Render3d *renderer, std::function<double(std::complex<double>)> f, std::function<bool(std::complex<double>)> set) {
    renderer->clear();
    this->drawAxis(renderer);

    Point3d point{};
    for(double x=-range; x<=range; x+=res) {
        for(double y=-range; y<=range; y+=res) {
            if(set(std::complex<double>(x,y))) {
                double v = f(std::complex<double>(x, y));
                point.x = x;
                point.y = y;
                point.z = v;
                if (point.z < range) {
                    point.color = getColor(v);
                    renderer->addPoint(point);
                }
            }
        }
    }
}

template<>
void Plot::draw(Render3d *renderer, std::function<std::complex<double>(std::complex<double>)> f, std::function<bool(std::complex<double>)> set) {
    renderer->clear();
    this->drawAxis(renderer);

    Point3d point{};
    for(double x=-range; x<=range; x+=res) {
        for(double y=-range; y<=range; y+=res) {
            if(set(std::complex<double>(x,y))) {
                std::complex<double> v = f(std::complex<double>(x, y));
                point.x = x;
                point.y = y;
                point.z = std::abs(v);
                if (point.z < range) {
                    point.color = getColor(v);
                    renderer->addPoint(point);
                }
            }
        }
    }
}


void Plot::drawAxis(Render3d *renderer) {
    Point3d point{};
    if(axisEnabled) {
        point.color = 0xFFFFFF;
        for(double c=-range; c<range; c+=res) {
            point.x = c;
            point.y = 0;
            point.z = 0;
            renderer->addPoint(point);
            point.x = 0;
            point.y = c;
            point.z = 0;
            renderer->addPoint(point);
            if(c >= 0) {
                point.x = 0;
                point.y = 0;
                point.z = c;
                renderer->addPoint(point);
            }
        }
        for(double c=range*0.97; c<range; c+=res) {
            for(int a = 0; a<64; a++) {
                point.x = c;
                point.y = sin(a/64.0 * 2 * M_PI) * (range-c);
                point.z = cos(a/64.0 * 2 * M_PI) * (range-c);
                renderer->addPoint(point);
                point.z = c;
                point.y = sin(a/64.0 * 2 * M_PI) * (range-c);
                point.x = cos(a/64.0 * 2 * M_PI) * (range-c);
                renderer->addPoint(point);
                point.y = c;
                point.x = sin(a/64.0 * 2 * M_PI) * (range-c);
                point.z = cos(a/64.0 * 2 * M_PI) * (range-c);
                renderer->addPoint(point);
            }
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

uint32_t Plot::getColor(double z) {
    const double TRI_WIDTH = range;

    auto r = (uint8_t)(tri(z - range, TRI_WIDTH)*255);
    auto g = (uint8_t)(tri(z, TRI_WIDTH)*255);
    auto b = (uint8_t)(tri(z + range, TRI_WIDTH) * 255);

    return r << 16 | g << 8 | b;
}

