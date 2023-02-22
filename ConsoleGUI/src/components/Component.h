#pragma once

#include <limits>

#include "../draw/DrawingClip.h"

#include "../util/Dimensions.h"

namespace cg {
    class Component {
    public:
        inline Component() : 
            minSize(0, 0), 
            maxSize(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()), 
            preferredSize(0, 0),
            renderSize(0, 0) {};
        virtual ~Component() = default;

        inline Dimensions getMinSize() const { return minSize; };
        inline Dimensions getMaxSize() const { return maxSize; };
        inline Dimensions getPreferredSize() const { return preferredSize; };
        inline Dimensions getSize() const { return renderSize; };

        virtual void updateSizeLimits();
        virtual void updateRenderSizes(Dimensions renderSize);
        virtual void drawComponent(draw::DrawingClip clip) const = 0;

    protected:
        void setMinSize(Dimensions minSize);
        void setMaxSize(Dimensions maxSize);
        void setPreferredSize(Dimensions preferredSize);
        void setRenderSize(Dimensions renderSize);

    private:
        Dimensions minSize;
        Dimensions maxSize;
        Dimensions preferredSize;

        Dimensions renderSize;
    };
}