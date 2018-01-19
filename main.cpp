#include <iostream>
#include <cmath>
#include <complex>
#include "Render3d.hpp"
#include "Plot.hpp"
#include "Output/BmpWriter.hpp"
#include "Output/XWriter.hpp"


int main() {
    RenderConfig config{};
    config.zTilt = M_PI/4;
    config.rotation = M_PI* 5/4;

    Render3d render3d;
    Plot plot(3,0.01, true);
    /*plot.draw<std::complex<double>, std::complex<double> >(&render3d, [](std::complex<double> z){
        //return z;
        //return z*z;
        //return (pow(z,3)-1.0)/z;
        return 1.0/(1.0+z*z);
        //return sin(z);
        //return exp(1.0/z);
    });*/
    plot.draw<std::complex<double>,double>(&render3d, [](std::complex<double> t){
        return std::real(t);
    });

    BmpWriter bmpWriter(800, 800, "bitmaps/test.bmp");

    XWriter xWriter(800, 800);

    bool renderReq = true;

    while(true) {
        if(renderReq) {
            render3d.render(&xWriter, config);
        }
        renderReq = true;

        switch (getc(stdin)) {
            case 'q':
                return 0;
            case 'd':
                config.rotation -= M_PI/8.0;
                break;
            case 'a':
                config.rotation += M_PI/8.0;
                break;
            case 'w':
                config.zTilt = std::min(config.zTilt+M_PI/8.0, M_PI/2);
                break;
            case 's':
                config.zTilt = std::max(config.zTilt-M_PI/8.0, 0.0);
                break;
           /* case '+':
                config.xScale *= 1.2;
                config.yScale *= 1.2;
                config.zScale *= 1.2;
                break;
            case '-':
                config.xScale /= 1.2;
                config.yScale /= 1.2;
                config.zScale /= 1.2;
                break;*/
            case 'b':
                std::cout << "Rendering ..." << std::endl;
                render3d.render(&bmpWriter, config);
                std::cout << "Finished" << std::endl;
                renderReq = false;
                break;
            default:
                renderReq = false;
                break;
        }
    }
}