#pragma once

#include <vector>
#include <memory>

#include "../Component.h"
#include "../../util/Point.h"

namespace cg {

    class Layout : public Component {
    public:
        inline Layout() {};

        void addChild(std::unique_ptr<Component> c);

        virtual void updateSizeLimits() override = 0;
        void updateRenderSizes(Dimensions renderSize) override;

    protected:
        std::vector<std::unique_ptr<Component>>& getChildren();
        const std::vector<std::unique_ptr<Component>>& getChildren() const;

        virtual void updateRenderSizesForChildren() = 0;

    private:
        std::vector<std::unique_ptr<Component>> children;
    };
}
