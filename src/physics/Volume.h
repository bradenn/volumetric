//
// Created by Braden Nicholson on 1/22/23.
//

#ifndef FLUX_VOLUME_H
#define FLUX_VOLUME_H


#include "Vector3D.h"
#include "vector"

using std::vector;

class Volume {

public:

    Volume(const vector<Vector3D> &footprint, int width, int height, int depth);

    void draw();

    void getWidth();

    void getHeight();

private:

    double width, height, depth;

    Vector3D offsets;

    vector<Vector3D> footprint;

    void drawFootprint();

    void drawWalls();

    void drawWalls(double height);

    Vector3D getCellDimensions();
};


#endif //FLUX_VOLUME_H
