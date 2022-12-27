//
// Created by Braden Nicholson on 12/23/22.
//

#ifndef FLUX_RENDERER_H
#define FLUX_RENDERER_H

#include <vector>
#include <GLFW/glfw3.h>
#include <freetype/freetype.h>
#include "quanta.h"
#include "fontRenderer.h"

using std::vector;

class Renderer {

public:
    Renderer(double width, double height) : width(width), height(height) {
        fr = FontRenderer("./IBMPlexSans-Regular.ttf");
    };

    Renderer() = default;

    void render(const vector<Quanta *> &quanta);

    void renderGrid();

    void drawOrigin();

    void drawLegend();

    void text(const string &text, double x, double y, double z);

private:
    double width, height;

    FontRenderer fr;
};


#endif //FLUX_RENDERER_H
