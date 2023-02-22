#include "Rectangle.h"

namespace cg {
    Rectangle::Rectangle() : upperLeft(0, 0), bottomRight(0, 0) {};

    Rectangle::Rectangle(Point upperLeft, Point bottomRight) :
        upperLeft(upperLeft),
        bottomRight(bottomRight) {
    }

    Rectangle::Rectangle(Point upperLeft, Dimensions dimensions) : 
        upperLeft(upperLeft),
        bottomRight(upperLeft.getX() + dimensions.getWidth(), upperLeft.getY() + dimensions.getHeight()) {
    }

    Point Rectangle::getUpperLeft() const {
        return upperLeft;
    }

    Point Rectangle::getBottomRight() const {
        return bottomRight;
    }

    Dimensions Rectangle::getDimensions() const {
        return Dimensions(bottomRight.getX() - upperLeft.getX(), bottomRight.getY() - upperLeft.getY());
    }
}
