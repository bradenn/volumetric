//
// Created by Braden Nicholson on 12/23/22.
//

#ifndef FLUX_WINDOW_H
#define FLUX_WINDOW_H

#import <iostream>
#import <string>
#include <GLFW/glfw3.h>
#include "Vector3D.h"
#include "Camera.h"

using std::string;
static Vector3D *MousePos = new Vector3D(0,0,0);
static Vector3D *MouseOrigin = new Vector3D(0,0,0);
static bool mouseDown = false;
static double scroll = 0.0;

class Window {

public:
    Window() = default;

    Window(int width, int height, const string &name);

    ~Window() {
        if (isRunning()) {
            glfwTerminate();
        }
    }

    static Vector3D getMousePos() {
        return *MousePos;
    }


    bool isRunning() {
        return !glfwWindowShouldClose(window_);
    }

    void pollEvents();

    void swapBuffer();

    double cx{}, cy{};
    Camera *camera;
private:
    Vector3D mouse_{0, 0, 0};
    GLFWwindow *window_{};

};


#endif //FLUX_WINDOW_H
