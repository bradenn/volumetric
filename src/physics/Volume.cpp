//
// Created by Braden Nicholson on 1/22/23.
//

#include <GLFW/glfw3.h>
#include "Volume.h"
#include "compute/Simplex.h"

Volume::Volume(const vector<Vector3D> &footprint, int width, int height, int depth) : footprint(footprint), width
        (width), height(height), depth(depth) {

    double maxX = -INT_MAX, maxY = -INT_MAX;
    double minX = INT_MAX, minY = INT_MAX;

    for (const auto &item: footprint) {
        if (item.getX() > maxX) maxX = item.getX();
        if (item.getY() > maxY) maxY = item.getY();
        if (item.getX() < minX) minX = item.getX();
        if (item.getY() < minY) minY = item.getY();
    }

    this->width = (maxX - minX);
    this->depth = (maxY - minY);

    offsets = Vector3D((minX + maxX) / 2.0, (minY + maxY) / 2.0, 0);
}

double map_range(double value, double old_min, double old_max, double new_min, double new_max) {
    // Calculate the proportion of the value in the old range
    double proportion = (value - old_min) / (old_max - old_min);

    // Map the value to the new range using the proportion
    return new_min + proportion * (new_max - new_min);
}

void materialColor(float r, float g, float b) {

    GLfloat ambientLight[] = {(GLfloat) r, (GLfloat) g, (GLfloat) b, 0.50f};
    GLfloat diffuseLight[] = {(GLfloat) r, (GLfloat) g, (GLfloat) b, 1};
    glColor3f((GLfloat) r, (GLfloat) g, (GLfloat) b);
// Assign created components to GL_LIGHT0.
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientLight);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseLight);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}


/*
 *
 */
double rdod_r[14][3] =
        {
                {0.0,             0.0,             1.0},
                {0.707106781187,  0.000000000000,  0.5},
                {0.000000000000,  0.707106781187,  0.5},
                {-0.707106781187, 0.000000000000,  0.5},
                {0.000000000000,  -0.707106781187, 0.5},
                {0.707106781187,  0.707106781187,  0.0},
                {-0.707106781187, 0.707106781187,  0.0},
                {-0.707106781187, -0.707106781187, 0.0},
                {0.707106781187,  -0.707106781187, 0.0},
                {0.707106781187,  0.000000000000,  -0.5},
                {0.000000000000,  0.707106781187,  -0.5},
                {-0.707106781187, 0.000000000000,  -0.5},
                {0.000000000000,  -0.707106781187, -0.5},
                {0.0,             0.0,             -1.0}
        };
int rdod_v[12][4] =
        {
                {0, 1,  5,  2},
                {0, 2,  6,  3},
                {0, 3,  7,  4},
                {0, 4,  8,  1},
                {5, 10, 6,  2},
                {6, 11, 7,  3},
                {7, 12, 8,  4},
                {8, 9,  5,  1},
                {5, 9,  13, 10},
                {6, 10, 13, 11},
                {7, 11, 13, 12},
                {8, 12, 13, 9}
        };
double rdod_n[12][3] =
        {
                {0.353553390594,  0.353553390594,  0.5},
                {-0.353553390594, 0.353553390594,  0.5},
                {-0.353553390594, -0.353553390594, 0.5},
                {0.353553390594,  -0.353553390594, 0.5},
                {0.000000000000,  1.000000000000,  0.0},
                {-1.000000000000, 0.000000000000,  0.0},
                {0.000000000000,  -1.000000000000, 0.0},
                {1.000000000000,  0.000000000000,  0.0},
                {0.353553390594,  0.353553390594,  -0.5},
                {-0.353553390594, 0.353553390594,  -0.5},
                {-0.353553390594, -0.353553390594, -0.5},
                {0.353553390594,  -0.353553390594, -0.5}
        };

/*!
    \fn
    \brief    Draw a wireframe rhombic dodecahedron
    \ingroup  geometry

              This function draws a wireframe dodecahedron whose
              facets are rhombic and
              whose vertices are at unit radius.
              No facet lies normal to any coordinate axes.
              The polyhedron is centered at the origin.

    \see      glutSolidRhombicDodecahedron(), glutWireDodecahedron(),
              glutSolidDodecahedron()
*/
void drawRhombicDodecahedron(double r, double g, double b) {
    int i;
    for (i = 0; i < 12; i++) {
        glBegin(GL_QUADS);
        materialColor(r, g, b);
        glNormal3dv(rdod_n[i]);
        glVertex3dv(rdod_r[rdod_v[i][0]]);
        glVertex3dv(rdod_r[rdod_v[i][1]]);
        glVertex3dv(rdod_r[rdod_v[i][2]]);
        glVertex3dv(rdod_r[rdod_v[i][3]]);
        glEnd();
    }
}

void Volume::drawWalls(double h) {
    glPushMatrix();

    glBegin(GL_LINES);
    for (const auto &item: footprint) {
        glColor3d(1, 1, 1);
        glVertex3d(item.getX(), 0, item.getY());
        glVertex3d(item.getX(), h, item.getY());
    }
    glEnd();
    glPopMatrix();
}

void Volume::drawFootprint() {
    glPushMatrix();
    glBegin(GL_LINES);
    Vector3D last = footprint[footprint.size() - 1];
    for (const auto &item: footprint) {
        glColor3d(1, 1, 1);
        glVertex3d(last.getX(), 0, last.getY());
        glVertex3d(item.getX(), 0, item.getY());
        last = item;
    }
    glEnd();
    glPopMatrix();
}

#define CELL_WIDTH = sqrt(2)
#define CELL_HEIGHT = sqrt(2)
double dx = 0;

Vector3D Volume::getCellDimensions() {
    auto dims = Vector3D(0, 0, 0);


    return dims;
}


Vector3D pt(0,0,0);
int loop = 0;

void Volume::draw() {
//    loop = (loop+1)%100;
//
//    pt.setX(cos(((M_PI*2)/100.0) * loop) * 40);
//    pt.setY(sin(((M_PI*2)/100.0) * loop) * 40);



    glPushMatrix();
    glTranslated(-offsets.getX(), -height, -offsets.getY());
    glPointSize(10);

    drawWalls(height);
    drawFootprint();
    glTranslated(0, height, 0);

    drawFootprint();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-width / 2, 0, -depth / 2);

    int subdivide = 4;

    double mv = sqrt(2) / 4;

    auto *s = new SimplexNoise();


    double cellSizeX = (1.0) / subdivide;
    double cellSizeY = (mv * 1.5) / subdivide;
    double cellSizeZ = (mv * 4) / subdivide;


    int cellX = ceil(width / cellSizeX);
    int cellY = ceil(height / cellSizeY);
    int cellZ = ceil(depth / cellSizeZ);

    glBegin(GL_LINES);
    glColor3d(1, 0.5, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(width, 0, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3d(1, 0.5, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, -height, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3d(1, 0.5, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, depth);
    glEnd();



    double sliver = (mv * 2) / subdivide;

    glScaled(sliver, sliver, sliver);
    glTranslated(0, -cellSizeY / 2, cellSizeY / 2);
    // height draw plane vertically
    for (int i = 0; i < cellY; ++i) { // y
        glPushMatrix();
        glTranslated(i % 2 == 0 ? mv * 2 : 0, -i * mv * 2, i % 2 == 0 ? 1 : 0);
        // Right to left row
        for (int j = 0; j < cellX; ++j) { //x
            glPushMatrix();
            glTranslated(mv * 4 * j, 0, 0);
            // Front to back 1D row
            for (int k = 0; k < cellZ; ++k) { //z
                glPushMatrix();
                glTranslated(0, 0, k * 2);
                float n = s->fractal(3, j, k, i) * 0.2;
                drawRhombicDodecahedron(1 - n, 1 - n, n);
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
    delete s;

}
