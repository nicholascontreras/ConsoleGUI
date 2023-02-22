#include "Component.h"

#include <stdexcept>

namespace cg {
    void Component::updateSizeLimits() {}

    void Component::updateRenderSizes(Dimensions renderSize) {
        setRenderSize(renderSize);
    }

    void Component::setMinSize(Dimensions minSize) {
        if(minSize > maxSize) {
            throw std::logic_error("Min Size cannot be larger than Max Size!");
        }
        this->minSize = minSize;
    }

    void Component::setMaxSize(Dimensions maxSize) {
        if(maxSize < minSize) {
            throw std::logic_error("Max Size cannot be smaller than Min Size!");
        }
        this->maxSize = maxSize;
    }

    void Component::setPreferredSize(Dimensions preferredSize) {
        if(preferredSize < minSize || preferredSize > maxSize) {
            throw std::logic_error("Preferred Size must be between Min and Max!");
        }
        this->preferredSize = preferredSize;
    }

    void Component::setRenderSize(Dimensions renderSize) {
        if(renderSize < minSize || renderSize > maxSize) {
            throw std::logic_error("Render Size must be between Min and Max!");

        }
        this->renderSize = renderSize;
    }
}
