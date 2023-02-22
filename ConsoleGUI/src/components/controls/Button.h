#pragma once

#include <string>

#include "../Component.h"

namespace cg {
    class Button : public Component {
    public:
        Button(std::string text);

        void drawComponent(draw::DrawingClip clip) const;

    private:
        std::string text;
    };
}
