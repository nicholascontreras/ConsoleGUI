#pragma once

#include <string>
#include <memory>

#include "../util/Rectangle.h"
#include "AsciiCanvas.h"

namespace cg::draw {
    class DrawingClip {
    public:
        inline const static struct {
            char NW = 'j';
            char SW = 'k';
            char SE = 'l';
            char NE = 'm';
            char NSEW = 'n';
            char EW = 'q';
            char NSE = 't';
            char NSW = 'u';
            char NEW = 'v';
            char SEW = 'w';
            char NS = 'x';
        } LINE_SEGMENTS;

        DrawingClip(Dimensions size, std::shared_ptr<AsciiCanvas> canvas);
        DrawingClip createSubclip(Rectangle subclip) const;

        void drawText(Point p, std::string s);
        inline void drawText(Point p, char c) { drawText(p, std::string(1, c)); };

        void drawLineSegment(Point p, std::string s);
        inline void drawLineSegment(Point p, char c) { drawLineSegment(p, std::string(1, c)); };
    private:
        Rectangle absoluteClip;
        std::shared_ptr<AsciiCanvas> canvas;

        DrawingClip(Rectangle absoluteClip, std::shared_ptr<AsciiCanvas> canvas);

        Point getAbsolutePoint(Point pointInClip);
        void verifyInClip(Point point);
    };
}