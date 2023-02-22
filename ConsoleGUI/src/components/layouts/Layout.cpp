#include "Layout.h"

namespace cg {

    std::vector<std::unique_ptr<Component>>& Layout::getChildren() {
        return children;
    }

    const std::vector<std::unique_ptr<Component>>& Layout::getChildren() const {
        return children;
    }

    void Layout::addChild(std::unique_ptr<Component> c) {
        children.push_back(std::move(c));
    }

    void Layout::updateRenderSizes(Dimensions renderSize) {
        setRenderSize(renderSize);
        updateRenderSizesForChildren();
    }
}
