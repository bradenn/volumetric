//
// Created by Braden Nicholson on 12/23/22.
//

#include "simulation.h"

Simulation::Simulation(double timeStep) {
    for (int i = 0; i < 5; ++i) {
        double px = 200.0 - ((double) (random() % 1000) / 1000.0) * 400.0;
        double py = 200.0 - ((double) (random() % 1000) / 1000.0) * 400.0;
        matter.push_back(new Quanta({(double) px, (double) py, 0}, {0, 0, 0}, {0, 0, 0}, 100*(std::rand()%100/100.0),
                                    1e-9 - 2e-9*(std::rand()%100/100.0)));

    }

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
                auto em = electromagnetic_.updateForce(*i, *j);
                i->addForce(em);
                i->addNamedForce("em", em);
                auto gravity = gravity_.updateForce(*i, *j);
                i->addNamedForce("gravity", gravity);
                i->addForce(gravity);
            }
        }
    }


}
