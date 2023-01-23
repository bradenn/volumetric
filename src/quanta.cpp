//
// Created by Braden Nicholson on 12/23/22.
//

#include "quanta.h"

using std::string;

Quanta::Quanta(Vector3D position, Vector3D velocity, Vector3D force, double mass, double charge) :
        position_(position), velocity_(velocity), force_(force), mass_(mass), charge_(charge) {

}

Vector3D Quanta::getPosition() const {
    return position_;
}

void Quanta::addForce(Vector3D force) {
    force_ = force_ + force;

}

void Quanta::addNamedForce(const string &name, Vector3D force) {
    if (!forces.contains(name)) {
        forces.emplace(name, Vector3D{0, 0, 0});
    }
    forces.at(name) = forces.at(name) + force;
}

void Quanta::update(double dt) {

    Vector3D acceleration = force_ / mass_;

    // Update the velocity of the quanta based on the acceleration and time step.
    velocity_ = velocity_ + (acceleration * dt);

    // Update the position of the quanta based on the velocity and time step.
    position_ = position_ + velocity_ * dt;

    resetForce();

    tail.push_back(position_);
    if(tail.size() > 1000) {
        tail.pop_front();
    }

    forces.clear();
}

double Quanta::getMass() const {
    return mass_;
}

Vector3D Quanta::getForce() const {
    return force_;
}

Vector3D Quanta::getVelocity() const {
    return velocity_;
}

void Quanta::resetForce() {
    force_ = {0, 0, 0};
}

double Quanta::getCharge() const {
    return charge_;
}

double Quanta::getRadius() const {
    return pow((3.0 / 4.0) * (mass_ / (density_ * M_PI)), 1.0 / 3.0);
}
