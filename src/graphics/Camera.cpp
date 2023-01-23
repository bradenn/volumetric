//
// Created by Braden Nicholson on 1/22/23.
//

#include <algorithm>
#include "Camera.h"

Vector3D *Camera::getRotation() {
    return &rotation;
}

Vector3D *Camera::getPosition() {
    return &position;
}

Camera::Camera(Vector3D position, Vector3D rotation): position(position), rotation(rotation) {

}

void Camera::setZoom(double z) {
    zoom = z;
}

double Camera::getZoom() {
    return zoom;
}
