#include "first_app.hpp"

namespace lve_MS{
    void FirstApp::run(){
        while(!lveWindow.shouldClose()){
            glfwPollEvents();
        }
    };
}