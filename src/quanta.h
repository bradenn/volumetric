//
// Created by Braden Nicholson on 12/23/22.
//

#ifndef FLUX_QUANTA_H
#define FLUX_QUANTA_H


#include "utilities/Vector3D.h"
#include <string>
#include <map>

using std::map;
using std::string;

class Quanta {

public:
    Quanta(Vector3D position, Vector3D velocity, Vector3D force, double mass, double charge);

    double getMass() const;

    double getCharge() const;

    Vector3D getPosition() const;

    Vector3D getForce() const;

    void addForce(Vector3D force);

    double getRadius() const;

    void resetForce();

    void update(double dt);

    bool operator==(const Quanta &q) const {
        return (getMass() == q.getMass()) && (getPosition() == q.getPosition());
    }

    Vector3D getVelocity() const;

    void addNamedForce(const string &name, Vector3D force);
    map<string, Vector3D> forces{};

private:

    Vector3D position_;
    Vector3D velocity_;
    Vector3D force_;


    double mass_;

    double charge_;

    double density_ = 0.01;


};


#endif //FLUX_QUANTA_H
