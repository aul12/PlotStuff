//
// Created by paul on 15.01.18.
//

#include <cmath>
#include "Point3d.hpp"

double Point3d::norm2() {
    return sqrt(x*x + y*y /*+ z*z*/);
}
