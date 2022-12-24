//
// Created by Braden Nicholson on 12/23/22.
//

#include "window.h"

Window::Window(int width, int height, const string &name) {
    // Initialize the GLFW
    if (!glfwInit()) {
        // Exit the program if init fails
        exit(1);
    }
    // Create a GLFW window
    window_ = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (!window_) {
        // Terminate the instance
        glfwTerminate();
        // Exit the program with an error
        exit(1);
    }
    // Set the initial context of the window
    glfwMakeContextCurrent(window_);
    // Configure the swap interval
    glfwSwapInterval(1);
    // Configure the projection
    glMatrixMode(GL_PROJECTION);
    // Load the identity matrix to start
    glLoadIdentity();
    // Set an orthographic view mode
    glOrtho(-(double)width/2.0, (double)width/2.0, (double)height/2.0, -(double)height/2.0, 0, -1000);
    // Move into model view
    glMatrixMode(GL_MODELVIEW);
    // Load the identity matrix
    glLoadIdentity();
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffer() {
    glfwSwapBuffers(window_);
}
