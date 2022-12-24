//
// Created by Braden Nicholson on 12/23/22.
//

#ifndef FLUX_RENDERER_H
#define FLUX_RENDERER_H

#include <vector>
#include "quanta.h"

using std::vector;

class Renderer {

public:
    Renderer() = default;

    void render(const vector<Quanta *> &quanta);

};


#endif //FLUX_RENDERER_H
