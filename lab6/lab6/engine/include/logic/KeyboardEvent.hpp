#pragma once

#include "Event.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

namespace cge {

class KeyboardEvent : public Event {
  public:
    using Event::action;
    KeyboardEvent(sf::Keyboard::Key key, std::function<void()> action)
        : Event{[key]() { return sf::Keyboard::isKeyPressed(key); }, action} {}
};

} // namespace cge
