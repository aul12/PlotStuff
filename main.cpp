#include <iostream>
#include <cmath>
#include "Render3d.hpp"
#include "Output/BmpWriter.hpp"
#include "Output/XWriter.hpp"

#define STEP 0.05

double val(double x, double y) {
    return fabs(x)*x*cos(y/2);
}

int main() {
    RenderConfig config{};
    config.zTilt = M_PI/4;
    config.xScale = config.yScale = 20;
    config.zScale = 5;
    config.rotation = M_PI/4;
    config.offsetX = 0;
    config.offsetY = +200;


    Render3d render3d;
    Point3d point3d{};
    point3d.color = 0xFFFFFF;
    for(int c=-10; c<10; c++) {
        point3d.x = c;
        point3d.y = 0;
        point3d.z = 0;
        render3d.addPoint(point3d);
        point3d.x = 0;
        point3d.y = c;
        point3d.z = 0;
        render3d.addPoint(point3d);
        point3d.x = 0;
        point3d.y = 0;
        point3d.z = c;
        render3d.addPoint(point3d);
    }

    for(double x=-5; x<=5; x+=STEP) {
        for(double y=-5; y<=5; y+=STEP) {
            double v = val(x, y);
            if(v >= 4) {
                point3d.color = 0xFF0000;
            } else if(v >= 2) {
                point3d.color = 0xFF00;
            } else {
                point3d.color = 0xFF;
            }
            point3d.x = x;
            point3d.y = y;
            point3d.z = v;

            render3d.addPoint(point3d);
        }
    }

   // BmpWriter writer(400, 400);
    BmpWriter::fname = "test.bmp";

    XWriter writer(200, 200);

    bool renderReq = true;

    while(true) {
        if(renderReq) {
            render3d.render(&writer, config);
        }
        renderReq = true;

        switch (getc(stdin)) {
            case 'q':
                return 0;
            case 'd':
                config.rotation += M_PI/8.0;
                break;
            case 'a':
                config.rotation -= M_PI/8.0;
                break;
            case 'w':
                config.zTilt += M_PI/8.0;
                break;
            case 's':
                config.zTilt -= M_PI/8.0;
                break;
            case '+':
                config.xScale *= 1.2;
                config.yScale *= 1.2;
                config.zScale *= 1.2;
                break;
            case '-':
                config.xScale /= 1.2;
                config.yScale /= 1.2;
                config.zScale /= 1.2;
                break;
            default:
                renderReq = false;
                break;
        }
    }
}