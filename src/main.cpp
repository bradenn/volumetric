//
// Created by Braden Nicholson on 12/23/22.
//

#import "simulation.h"
#import "window.h"
#include "renderer.h"

int main() {

    Simulation simulation(0.1);

    Window window(1280, 720, "FLUX");
    Renderer renderer(1280, 720);

    simulation.setWindow(window);
    simulation.setRenderer(renderer);

    while (window.isRunning()) {

        simulation.updateWindow();
        simulation.step(10);

        simulation.updateRenderer();

        window.swapBuffer();

        window.pollEvents();
    }


    return 0;
}
