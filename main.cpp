#include <iostream>
#include <cmath>
#include <complex>
#include "Render3d.hpp"
#include "Plot.hpp"
#include "Output/BmpWriter.hpp"
#include "Output/XWriter.hpp"


std::complex<double> val(std::complex<double> z) {
    return z*z;
}

int main() {
    RenderConfig config{};
    config.zTilt = M_PI/4;
    config.xScale = config.yScale = 20;
    config.zScale = 20;
    config.rotation = M_PI/4;
    config.offsetX = 0;
    config.offsetY = 0;


    Render3d render3d;
    Plot plot(3,0.1);
    plot.draw([](std::complex<double> z){
        return z;
    }, &render3d);

    BmpWriter bwriter(400, 400);
    BmpWriter::fname = "test.bmp";

    XWriter xwriter(200, 200);

    bool renderReq = true;

    while(true) {
        if(renderReq) {
            render3d.render(&xwriter, config);
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
                config.zTilt = std::min(config.zTilt+M_PI/8.0, M_PI/2);
                break;
            case 's':
                config.zTilt = std::max(config.zTilt-M_PI/8.0, -M_PI/2);
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
            case 'b':
                render3d.render(&bwriter, config);
                renderReq = false;
                break;
            default:
                renderReq = false;
                break;
        }
    }
}