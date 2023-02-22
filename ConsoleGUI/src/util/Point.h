#pragma once

namespace cg {
    class Point {
    public:
        Point(int x, int y);
        inline int getX() const { return x; };
        inline int getY() const { return y; };
    private:
        int x, y;
    };
}
