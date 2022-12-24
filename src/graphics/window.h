//
// Created by Braden Nicholson on 12/23/22.
//

#ifndef FLUX_WINDOW_H
#define FLUX_WINDOW_H

#import <iostream>
#import <string>
#include <GLFW/glfw3.h>

using std::string;


class Window {

public:
    Window() = default;

    Window(int width, int height, const string &name);

    ~Window() {
        if (isRunning()) {
            glfwTerminate();
        }
    }

    bool isRunning() {
        return !glfwWindowShouldClose(window_);
    }

    void pollEvents();

    void swapBuffer();

private:

    GLFWwindow *window_{};

};


#endif //FLUX_WINDOW_H
