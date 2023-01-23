//
// Created by Braden Nicholson on 1/22/23.
//

#ifndef FLUX_CAMERA_H
#define FLUX_CAMERA_H


#include "Vector3D.h"

class Camera {

public:

    Camera(Vector3D position, Vector3D rotation);

    Vector3D *getPosition();
    Vector3D *getRotation();
    double getZoom();
    void setZoom(double z);

private:

    Vector3D position, rotation;

    double zoom = 1;


};


#endif //FLUX_CAMERA_H
