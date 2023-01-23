//
// Created by Braden Nicholson on 12/23/22.
//

#ifndef FLUX_VECTOR3D_H
#define FLUX_VECTOR3D_H

#include <cmath>

class Vector3D {

public:
    Vector3D(double x, double y, double z) : x_(x), y_(y), z_(z) {}

    Vector3D() {}

    double getX() const { return x_; }

    double getY() const { return y_; }

    double getZ() const { return z_; }

    void setX(double x) { x_ = x; }

    void setY(double y) { y_ = y; }

    void setZ(double z) { z_ = z; }

    Vector3D normalize() const {
        double m = magnitude();
        return {x_ / m, y_ / m, z_ / m};
    }

    double magnitude() const {
        return sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
    }

    double magnitudeSquared() const {
        return pow(magnitude(), 2);
    }

    bool operator==(const Vector3D &target) const {
        return x_ == target.x_ && y_ == target.y_ && z_ == target.z_;
    }

    Vector3D operator+(const Vector3D &target) const {
        return {x_ + target.x_, y_ + target.y_, z_ + target.z_};
    }

    Vector3D operator-(const Vector3D &target) const {
        return {x_ - target.x_, y_ - target.y_, z_ - target.z_};
    }

    Vector3D operator*(double scalar) const {
        return {x_ * scalar, y_ * scalar, z_ * scalar};
    }

    Vector3D operator/(double scalar) const {
        return {x_ / scalar, y_ / scalar, z_ / scalar};
    }

private:

    double x_{}, y_{}, z_{};

};


#endif //FLUX_VECTOR3D_H
