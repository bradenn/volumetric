//
// Created by Braden Nicholson on 12/23/22.
//

#include "simulation.h"

Simulation::Simulation(double timeStep) {
    matter.push_back(new Quanta({(double) 0, (double) 0, 0}, {0, 0, 0}, {0, 0, 0}, 0, 0.0001));
    matter.push_back(new Quanta({(double) 100, (double) 0, 0}, {0, 0, 0}, {0, 0, 0}, 0, -0.0001));
}

void Simulation::updateWindow() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Simulation::updateRenderer() {

    glPushMatrix();
    renderer_.render(matter);
    glPopMatrix();
    for (Quanta *i: matter) {
        i->update(dt);
    }
}

void Simulation::step(double delta) {
    dt += delta;

    for (auto i: matter) {
        for (auto j: matter) {
            if (!i->operator==(*j)) {
                i->addForce(electromagnetic_.updateForce(*i, *j));
                i->addForce(gravity_.updateForce(*i, *j));
            }
        }
    }


}
