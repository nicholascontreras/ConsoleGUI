#include "Dimensions.h"

#include <stdexcept>

namespace cg {
    Dimensions::Dimensions(int width, int height) : width(width), height(height) {
        if(width < 0) {
            throw std::invalid_argument("Width cannot be negative!");
        }
        if(height < 0) {
            throw std::invalid_argument("Height cannot be negative!");
        }
    }

    bool Dimensions::operator==(const Dimensions rhs) const {
        return width == rhs.width && height == rhs.height;
    }

    bool Dimensions::operator>=(const Dimensions rhs) const {
        return width >= rhs.width && height >= rhs.height;
    }

    bool Dimensions::operator<=(const Dimensions rhs) const {
        return width <= rhs.width && height <= rhs.height;
    }
}
