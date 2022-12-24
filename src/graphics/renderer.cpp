//
// Created by Braden Nicholson on 12/23/22.
//

#include "renderer.h"
#include "quanta.h"
#include "GLFW/glfw3.h"
#include "iostream"

void Renderer::render(const vector<Quanta *> &quanta) {
    for (auto item: quanta) {
    glPointSize(item->getRadius());
        glBegin(GL_POINTS);
        auto pos = item->getPosition();

        glColor3d(1, 1, 1);
        glVertex3d(pos.getX(), pos.getY(), pos.getZ());
        glEnd();

        glBegin(GL_LINES);
        auto force = item->getForce().normalize();
        glColor3d(1, 0, 1);
        glVertex3d(pos.getX(), pos.getY(), pos.getZ());
        auto p = pos + force*log10(item->getForce().magnitude())*10;
        glVertex3d(p.getX(), p.getY(), p.getZ());
        glEnd();
    }
}

