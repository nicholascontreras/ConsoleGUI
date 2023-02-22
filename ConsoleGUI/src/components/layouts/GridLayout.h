#pragma once

#include "Layout.h"

namespace cg {
    class GridLayout : public Layout {
    public:
        GridLayout(int numCols);

        void updateSizeLimits() override;
        void drawComponent(draw::DrawingClip clip) const override;
    protected:

        void updateRenderSizesForChildren() override;
    private:
        int numCols;
    };
}