#include "GridLayout.h"

#include <stdexcept>
#include <cmath>
#include <limits>

#include "../../util/Dimensions.h"
#include "../../util/util.h"

namespace cg {
    GridLayout::GridLayout(int numCols) : numCols(numCols) {
        if(numCols <= 0) {
            throw std::invalid_argument("Cols must be positive!");
        }
    }

    void GridLayout::updateSizeLimits() {
        
        Dimensions largestMinSize(0, 0);
        Dimensions smallestMaxSize(util::MAX_SAFE_INT, util::MAX_SAFE_INT);
        Dimensions largestPreferredSize(0, 0);

        for(std::unique_ptr<Component>& curChild : getChildren()) {
            curChild->updateSizeLimits();

            if(curChild->getMinSize() > largestMinSize) {
                largestMinSize = curChild->getMinSize();
            }
            if(curChild->getMaxSize() < smallestMaxSize) {
                smallestMaxSize = curChild->getMaxSize();
            }
            if(curChild->getPreferredSize() > largestPreferredSize) {
                largestPreferredSize = curChild->getPreferredSize();
            }
        }

        if(largestMinSize > smallestMaxSize) {
            throw std::logic_error("Cannot resolve grid sizing, cell minimum renderSize is larger than maximum renderSize!");
        }
        if(largestPreferredSize < largestMinSize) {
            throw std::logic_error("Cannot resolve grid sizing, cell preferred renderSize is smaller than minimum renderSize!");
        }
        if(largestPreferredSize > smallestMaxSize) {
            throw std::logic_error("Cannot resolve grid sizing, cell preferred renderSize is larger than maximum renderSize!");
        }

        int numRows = (int)ceil((double)getChildren().size() / numCols);

        Dimensions myPreferredSize(numCols * largestPreferredSize.getWidth(), numRows * largestPreferredSize.getHeight());
        Dimensions myMinSize(numCols * largestMinSize.getWidth(), numRows * largestMinSize.getHeight());
        Dimensions myMaxSize(numCols * smallestMaxSize.getWidth(), numRows * smallestMaxSize.getHeight());

        setPreferredSize(myPreferredSize);
        setMinSize(myMinSize);
        setMaxSize(myMaxSize);
    }

    void GridLayout::drawComponent(draw::DrawingClip clip) const {
        int numRows = (int)ceil((double)getChildren().size() / numCols);
        int cellWidth = getSize().getWidth() / numCols;
        int cellHeight = getSize().getHeight() / numRows;
        Dimensions cellDimensions(cellWidth, cellHeight);

        int row = 0, col = 0;
        for(const std::unique_ptr<Component>& curChild : getChildren()) {
            Rectangle curCellRect({col * cellWidth, row * cellHeight}, cellDimensions);
            draw::DrawingClip curClip = clip.createSubclip(curCellRect);
            curChild->drawComponent(curClip);

            col++;
            if(col == numCols) {
                row++;
                col = 0;
            }
        }
    }

    void GridLayout::updateRenderSizesForChildren() {
        int numRows = (int)ceil((double)getChildren().size() / numCols);
        int cellWidth = getSize().getWidth() / numCols;
        int cellHeight = getSize().getHeight() / numRows;
        Dimensions cellDimensions(cellWidth, cellHeight);

        for(std::unique_ptr<Component>& curChild : getChildren()) {
            curChild->updateRenderSizes(cellDimensions);
        }
    }
}
