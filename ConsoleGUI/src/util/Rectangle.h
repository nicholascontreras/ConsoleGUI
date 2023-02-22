#pragma once

#include "Point.h"
#include "Dimensions.h"

namespace cg {
    class Rectangle {
    public:
        Rectangle();
        Rectangle(Point upperLeft, Point bottomRight);
        Rectangle(Point upperLeft, Dimensions dimensions);

        Point getUpperLeft() const;
        Point getBottomRight() const;
        Dimensions getDimensions() const;
    private:
        Point upperLeft, bottomRight;
    };
}