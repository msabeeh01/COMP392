#pragma once
#include "lve_window.hpp"

namespace lve_MS{
    class FirstApp{
        public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        void run(){};

        private:
        LveWindow lveWindow{WIDTH, HEIGHT, "Vulkan"};
    };
}