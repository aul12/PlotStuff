//
// Created by paul on 15.01.18.
//

#ifndef KOMISCHESPLOTTINGDINGS_POINT3D_HPP
#define KOMISCHESPLOTTINGDINGS_POINT3D_HPP


#include <cstdint>

class Point3d {
public:
    double x,y,z;
    uint32_t  color;
    double norm2();
};


#endif //KOMISCHESPLOTTINGDINGS_POINT3D_HPP
