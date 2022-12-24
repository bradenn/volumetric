//
// Created by Braden Nicholson on 12/23/22.
//

#ifndef FLUX_GRAVITY_H
#define FLUX_GRAVITY_H

#include <iostream>
#include <vector>
#include "quanta.h"

using std::vector;


class Gravity {

public:
    Gravity() = default;

    Vector3D updateForce(const Quanta &from, const Quanta &to) const {
        Vector3D r = to.getPosition() - from.getPosition();
        double r2 = r.magnitudeSquared();
        return (r.normalize()) * ((G * from.getMass() * to.getMass()) / r2);
    }

private:

    double G = 6.674308676652884e-11;



};


#endif //FLUX_GRAVITY_H
