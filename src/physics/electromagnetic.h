//
// Created by Braden Nicholson on 12/23/22.
//

#ifndef FLUX_ELECTROMAGNETIC_H
#define FLUX_ELECTROMAGNETIC_H

#include <iostream>
#include <vector>
#include "quanta.h"

using std::vector;


class Electromagnetic {

public:
    Electromagnetic() = default;

    Vector3D updateForce(const Quanta &from, const Quanta &to) const {
        // Calculate the distance between the two quanta.
        Vector3D r = to.getPosition() - from.getPosition();
        double r2 = r.magnitudeSquared();

        // Calculate the electromagnetic force using Coulomb's law.
        return (r.normalize()) * ((k * from.getCharge() * to.getCharge()) / r2);
    }

private:

    double k = 8.9875517873681764e9;


};


#endif //FLUX_ELECTROMAGNETIC_H
