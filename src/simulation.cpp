//
// Created by Braden Nicholson on 12/23/22.
//

#include <omp.h>
#include "simulation.h"

Simulation::Simulation(double timeStep) {

}

void Simulation::updateWindow() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    GLfloat ambientLight[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat diffuseLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat specularLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat position[] = {0.0f, 20.0f, -10.0f, 1.0f};
//
//    glRotatef(camera->pitch, 1, 0, 0);
//    glRotatef(camera->yaw, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void Simulation::updateRenderer() {

    glPushMatrix();
    renderer_.render(window_.camera);
    glPopMatrix();

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHT0);
    glDisable(GL_BLEND);

}

void Simulation::step(double delta) {
    dt += delta;

}
