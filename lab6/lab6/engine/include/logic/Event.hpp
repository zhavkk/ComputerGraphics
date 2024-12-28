#pragma once

#include <functional>

namespace cge {

struct Event {
    std::function<bool()> condition;
    std::function<void()> action;
};

} // namespace cge
