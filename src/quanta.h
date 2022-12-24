//
// Created by Braden Nicholson on 12/23/22.
//

#ifndef FLUX_QUANTA_H
#define FLUX_QUANTA_H


#include "utilities/Vector3D.h"

class Quanta {

public:


    Quanta(Vector3D position, Vector3D velocity, Vector3D force, double mass, double charge);

    double getMass() const;
    double getCharge() const;

    Vector3D getPosition() const;

    Vector3D getForce() const;

    void addForce(Vector3D force);
    double getRadius();

    void resetForce();

    void update(double dt);

    bool operator==(const Quanta &q) const {
        return (getMass() == q.getMass()) && (getPosition() == q.getPosition());
    }

    Vector3D getVelocity() const;

private:

    Vector3D position_;
    Vector3D velocity_;
    Vector3D force_;

    double mass_;

    double charge_;

    double density_ = 0.1;



};


#endif //FLUX_QUANTA_H
