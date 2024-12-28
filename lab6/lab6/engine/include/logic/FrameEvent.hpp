#pragma once

#include "Event.hpp"
#include <functional>

namespace cge {

class FrameEvent : public Event {
  public:
    using Event::action;

    FrameEvent(std::function<void()> action)
        : Event{[]() { return true; }, action} {}
};

} // namespace cge
