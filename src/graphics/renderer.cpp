//
// Created by Braden Nicholson on 12/23/22.
//

#include "renderer.h"
#include "quanta.h"
#include "GLFW/glfw3.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "iostream"

void Renderer::render(const vector<Quanta *> &quanta) {

    renderGrid();

    drawOrigin();


    for (auto item: quanta) {
        auto rad = item->getRadius();
        glPointSize((float) rad);
        glBegin(GL_POINTS);
        auto pos = item->getPosition();

        glColor3d(1, 1, 1);
        glVertex3d(pos.getX(), pos.getY(), pos.getZ());
        glEnd();

//        glBegin(GL_LINES);
//        auto force = item->getForce().normalize();
//        glColor3d(1, 0, 1);
//        glVertex3d(pos.getX(), pos.getY(), pos.getZ());
//        auto p = pos + force * rad*4;
//        glVertex3d(p.getX(), p.getY(), p.getZ());
//        glEnd();

        int itr = 0;
        for (auto &fo: item->forces) {
            glBegin(GL_LINES);
            pos = item->getPosition();
            auto force = fo.second.normalize();
            glColor3d((double) itr / (double) (item->forces.size() - 1), 0.25,
                      1.0 - (double) itr / (double) (item->forces.size()
                                                     - 1));
            glVertex3d(pos.getX(), pos.getY(), pos.getZ());
            auto p = pos + force * rad * 2;
            glVertex3d(p.getX(), p.getY(), p.getZ());
            glEnd();
            itr++;
        }


    }
    drawLegend();
}

void Renderer::drawLegend() {
    double extent = 100.0;
    glPushMatrix();
    glTranslated(-width / 2 + 10, height / 2 - 10, 0);
    glBegin(GL_LINES);
    glColor3d(1, 1, 1);
    glVertex3d(0, 0, 0);
    glVertex3d(extent, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, -10, 0);
    glVertex3d(extent, 0, 0);
    glVertex3d(extent, -10, 0);
    glEnd();
    double w = fr.stringWidth("1 meter");
    text(std::to_string(w), extent/2 + w/4, -10, 0);
    glPopMatrix();
}

void Renderer::drawOrigin() {

    double extent = 25.0;
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3d(1, 0, 0);
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

}

void Renderer::text(const string &text, double x, double y, double z) {
   fr.renderText(text, x, y, z);
}

