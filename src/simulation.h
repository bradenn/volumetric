//
// Created by Braden Nicholson on 12/23/22.
//

#ifndef FLUX_SIMULATION_H
#define FLUX_SIMULATION_H


#include "window.h"
#include "renderer.h"
#include "quanta.h"
#include "gravity.h"
#include "electromagnetic.h"
#include <vector>

using std::vector;

class Simulation {

public:

    Simulation(double timeStep);

    void setWindow(const Window &window) {
        window_ = window;
    }

    void setRenderer(const Renderer &renderer) {
        renderer_ = renderer;
    }

    void step(double delta);

    void updateWindow();

    void updateRenderer();

private:

    vector<Quanta*> matter;

    Window window_;

    Renderer renderer_;

    Gravity gravity_;
    Electromagnetic electromagnetic_;

    double dt = 0.0;

};


#endif //FLUX_SIMULATION_H
