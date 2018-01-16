//
// Created by paul on 16.01.18.
//

#ifndef KOMISCHESPLOTTINGDINGS_PLOT_HPP
#define KOMISCHESPLOTTINGDINGS_PLOT_HPP


#include <functional>
#include <complex>
#include "Render3d.hpp"

class Plot {
public:
    explicit Plot(double range = 10, double res = 0.5, bool axisEnabled = true);
    void draw(std::function<std::complex<double>(std::complex<double>)> f, Render3d* renderer);

private:
    double range, res;
    double axisEnabled;

    static double tri(double x, double w = 1);
    static uint32_t getColor(std::complex<double> z);
};


#endif //KOMISCHESPLOTTINGDINGS_PLOT_HPP
