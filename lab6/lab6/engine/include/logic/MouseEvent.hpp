#pragma once
#include "Event.hpp"

namespace cge {

struct MouseEvent {
    std::function<void(float, float, float)> action;
};

} // namespace cge