//
// Created by Braden Nicholson on 12/23/22.
//

#include "renderer.h"
#include "quanta.h"
#include "GLFW/glfw3.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Volume.h"
#include "Camera.h"

void Renderer::render(Camera *camera) {
//    angle += M_PI / (M_E * 5);

    drawLegend();
    double s = std::max(camera->getZoom(),0.5);
    glScaled(s,s,s);
    glRotated(camera->getRotation()->getY(), 1,0,0);
    glRotated(camera->getRotation()->getX(), 0,1,0);
    glPushMatrix();

    auto vec = vector<Vector3D>({Vector3D{0.00007071067811865477, 0.00007071067811865474, 0},
                                 Vector3D{2.0364675298172563, -2.036467529817257, 0},
                                 Vector3D{2.0364675298172563, -2.3764444702117493, 0},
                                 Vector3D{3.1364428386310497, -2.3764444702117498, 0},
                                 Vector3D{3.1364428386310506, 1.993616858877351, 0},
                                 Vector3D{4.440892098500626e-16, 2.0199212311374914, 0}});

    auto v = new Volume(vec, 10, 2, 10);

    v->draw();
//    drawVolume(8, 16, 8);
    drawOrigin();

    glPopMatrix();

}

void Renderer::drawLegend() {
    double extent = unit * 5;
    glPushMatrix();
    glTranslated(-width / 2 + unit, height / 2 - unit, 0);
    glBegin(GL_LINES);
    glColor3d(1, 1, 1);
    glVertex3d(0, 0, 0);
    glVertex3d(extent, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, -unit / 2, 0);
    glVertex3d(extent, 0, 0);
    glVertex3d(extent, -unit / 2, 0);
    glEnd();
    text("5 units", extent / 2, -(unit) / 2, 0);
    glPopMatrix();
}

void Renderer::drawOrigin() {

    double extent = unit * 2;
    glPushMatrix();
    glColor3d(1, 0, 0);
    glBegin(GL_LINES);
    glVertex3d(0, 0, 0);
    glVertex3d(extent, 0, 0);
    glEnd();
    glBegin(GL_LINES);
    glColor3d(0, 1, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, -extent, 0);
    glEnd();
    glBegin(GL_LINES);
    glColor3d(0, 0, 1);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, extent);
    glEnd();
    glPopMatrix();
}

void Renderer::renderGrid() {

    glPushMatrix();
    glColor3d(0.25, 0.25, 0.25);
    glTranslated(-width / 2, -height / 2, 0);
    for (int i = 0; i < MULTIPLE; i++) {
        glBegin(GL_LINES);
        glVertex3d(0, unit * i, 0);
        glVertex3d(width, unit * i, 0);
        glEnd();
    }

    for (int j = 0; j < MULTIPLE; j++) {
        glBegin(GL_LINES);
        glVertex3d(unit * j, 0, 0);
        glVertex3d(unit * j, height, 0);
        glEnd();
    }
    glPopMatrix();
}

void Renderer::text(const string &text, double x, double y, double z) {
    fr.renderText(text, x, y, z);
}

