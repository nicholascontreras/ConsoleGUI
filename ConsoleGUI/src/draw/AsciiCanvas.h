#pragma once

#include <vector>
#include <string>

#include "../util/Point.h"
#include "../util/Dimensions.h"

namespace cg::draw {
    class AsciiCanvas {
    public:
        AsciiCanvas(Dimensions size);

        void setText(Point p, std::string s);
        inline void setText(Point p, char c) { setText(p, std::string(1, c)); };

        void setLineSegment(Point p, std::string s);
        inline void setLineSegment(Point p, char c) { setLineSegment(p, std::string(1, c)); };

        void renderToTerminal();
    private:
        Dimensions size;
        std::vector<char> textCanvas;
        std::vector<char> lineCanvas;

        int indexOf(Point p);
        void verifyBlank(Point p);
        void verifyOnCanvas(Point p);
    };
}
