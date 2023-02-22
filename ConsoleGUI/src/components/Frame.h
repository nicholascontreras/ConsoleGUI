#pragma once

#include <memory>
#include <thread>
#include <mutex>

#include "Component.h"

namespace cg {
    class Frame {
    public:
        static void show();
        static void hide();

        static bool getIsBeingShown();

        static void setChild(std::unique_ptr<Component> c);
    private:
        static bool isBeingShown;

        static std::unique_ptr<Component> child;

        static void runGraphics();
    };
}
