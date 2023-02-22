#include "Point.h"

#include <stdexcept>

namespace cg {
    Point::Point(int x, int y) : x(x), y(y) {
        if(x < 0) {
            throw std::invalid_argument("X cannot be negative!");
        }
        if(y < 0) {
            throw std::invalid_argument("Y cannot be negative!");
        }
    }
}
