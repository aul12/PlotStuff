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

    template<typename I, typename O> void draw(Render3d* renderer, std::function<O(I)> f,
              std::function<bool(I)> set = [](I z){
                  return true;
              });

private:
    double range, res;
    double axisEnabled;
    void drawAxis(Render3d* renderer);

    static double tri(double x, double w = 1);
    uint32_t getColor(std::complex<double> z);
    uint32_t getColor(double z);
};


#endif //KOMISCHESPLOTTINGDINGS_PLOT_HPP
