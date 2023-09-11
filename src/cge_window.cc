#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "cge_window.hh"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <vulkan/vulkan.h>

namespace cge {
    //
    // CONSTRUCTOR 
    //
    CGE_Window::CGE_Window(
            uint32_t width, 
            uint32_t height, 
            std::string name) : _width(width), _height(height), _window_name(name) {
        this->_init_window();
    }

    CGE_Window::~CGE_Window() {
        if (this->_window)
            glfwDestroyWindow(this->_window);
        glfwTerminate();
        printf("Window destroyed\n");
    }

    //
    // Inititalization behavior
    // for GLFW window
    //
    void 
    CGE_Window::_init_window() {
        if (!glfwInit()) {
            fprintf(stderr, "Error: failed to initialize GLFW\n");
            exit(1);
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
        this->_window = glfwCreateWindow(
                            this->_width,
                            this->_height,
                            this->_window_name.c_str(),
                            nullptr,
                            nullptr
                        );
        if (!this->_window) {
            fprintf(stderr, "Error: failed to create GLFW window\n");
            exit(1);
            glfwTerminate();
        }
    }

    //
    // Open the GLFW window
    //
    void
    CGE_Window::_open_window() {
        if (this->_window) {
            while (!glfwWindowShouldClose(this->_window)) {
                glfwPollEvents();
            }
        } else {
            fprintf(stderr, "Error: window is not initialized\n");
            exit(1);
        }
    }

    void
    CGE_Window::_create_window_surface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, this->_window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("Error: failed to create window surface");
        }
    }

}
