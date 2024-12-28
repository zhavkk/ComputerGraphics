#pragma once

#include "Event.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

namespace cge {

class EveryNSec : public Event {
  public:
    using Event::action;
    EveryNSec(float n, std::function<void()> action)
        : Event{[this, n]() mutable {
                    if (__clock.getElapsedTime().asSeconds() >= n) {
                        __clock.restart();
                        return true;
                    }
                    return false;
                },
                action} {}

  private:
    sf::Clock __clock;
};

} // namespace cge
