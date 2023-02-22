#pragma once

namespace cg {
    class Dimensions {
    public:
        Dimensions(int width, int height);

        inline int getWidth() const { return width; };
        inline int getHeight() const { return height; };

        bool operator==(const Dimensions rhs) const;
        bool operator>=(const Dimensions rhs) const;
        bool operator<=(const Dimensions rhs) const;

        inline bool operator>(const Dimensions rhs) const { return !(*this <= rhs); };
        inline bool operator<(const Dimensions rhs) const { return !(*this >= rhs); };

    private:
        int width, height;
    };
}
