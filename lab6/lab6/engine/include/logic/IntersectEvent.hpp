#pragma once

#include "../objects/ObjectBase.hpp"
#include "Event.hpp"

namespace cge {

bool intersects(const std::pair<glm::vec3, glm::vec3> &a,
                const std::pair<glm::vec3, glm::vec3> &b) {
    return (a.first.x <= b.second.x && a.second.x >= b.first.x) && // Проверка по X
           (a.first.y <= b.second.y && a.second.y >= b.first.y) && // Проверка по Y
           (a.first.z <= b.second.z && a.second.z >= b.first.z); // Проверка по Z
}

glm::vec3 intersectionDepth(const std::pair<glm::vec3, glm::vec3> &a,
                            const std::pair<glm::vec3, glm::vec3> &b) {
    if (!intersects(a, b)) {
        return glm::vec3(0.0f);
    }

    float overlapX = std::min(a.second.x, b.second.x) - std::max(a.first.x, b.first.x);
    float overlapY = std::min(a.second.y, b.second.y) - std::max(a.first.y, b.first.y);
    float overlapZ = std::min(a.second.z, b.second.z) - std::max(a.first.z, b.first.z);

    return glm::vec3(overlapX, overlapY, overlapZ);
}

class IntersectEvent : public Event {
  public:
    using Event::action;

    IntersectEvent(ObjectBase *obj1, ObjectBase *obj2,
                   std::function<void()> action)
        : Event{[obj1, obj2]() {
                    return intersects(obj1->getBoundingBox(), obj2->getBoundingBox());
                },
                action} {}
};

} // namespace cge
