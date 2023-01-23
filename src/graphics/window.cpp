//
// Created by Braden Nicholson on 12/23/22.
//

#include "window.h"

#include <GLFW/glfw3.h>


static void scroll_callback(GLFWwindow *window, double xpos, double ypos) {
    scroll = ypos;
}


static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {
        if (!mouseDown) {
            MouseOrigin->setX(xpos);
            MouseOrigin->setY(ypos);
            MousePos->setX(0);
            MousePos->setY(0);
            mouseDown = true;
        } else {
            MousePos->setX(MouseOrigin->getX()-xpos);
            MousePos->setY(MouseOrigin->getY()-ypos);
        }
    } else {
        mouseDown = false;
    }
}


Window::Window(int width, int height, const string &name) {
    camera = new Camera(Vector3D(0, 0, 0), Vector3D(0, 0, 0));
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
    glOrtho(-(double) width / 2.0, (double) width / 2.0, (double) height / 2.0, -(double) height / 2.0, -1000, 1000);
//    glFrustum(-(double) width / 2.0, (double) width / 2.0, (double) height / 2.0, -(double) height / 2.0, 0, 1000)
    // Move into model view
    glMatrixMode(GL_MODELVIEW);
    // Load the identity matrix
    glLoadIdentity();
    glfwSetCursorPosCallback(window_, cursor_position_callback);
    glfwSetScrollCallback(window_, scroll_callback);


}

void Window::pollEvents() {

    glfwPollEvents();
    int x, y;
    glfwGetWindowSize(window_, &x,&y);
    auto rx = camera->getRotation()->getX() + ((MousePos->getX())/(x/2)) * 5;
    auto ry = camera->getRotation()->getY() + ((MousePos->getY())/(y/2)) * 5;

    camera->getRotation()->setX(rx);
    camera->getRotation()->setY(ry);
    MousePos->setX(0);
    MousePos->setY(0);
    camera->setZoom(camera->getZoom()+(scroll/10));
    scroll = 0;

}

void Window::swapBuffer() {
    glfwSwapBuffers(window_);
}
