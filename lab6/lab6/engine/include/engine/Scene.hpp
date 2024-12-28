#pragma once

#include "../camera/Camera.hpp"
#include "../camera/FPCamera.hpp"
#include "../camera/TPCamera.hpp"
#include "../light/DirectLight.hpp"
#include "../light/PointLight.hpp"
#include "../logic/Event.hpp"
#include "../logic/MouseEvent.hpp"
#include "../objects/Model.hpp"
#include "../objects/ObjectBase.hpp"
#include <SFML/Graphics.hpp>
#include <any>
#include <memory>
#include <unordered_set>
#include <atomic>

namespace cge {

class Scene {
  public:
    Scene(const std::string &name);

    Scene &add(ObjectBase &obj);
    Scene &add(Model &obj);
    Scene &add(const DirectLight &light);
    Scene &add(const PointLight &light);
    Scene &use(Camera &cam);
    Scene &use(TPCamera &cam);
    Scene &use(FPCamera& cam);
    Scene &background(const glm::ivec3 &color);
    Scene &handle(Event &event);
    Scene &handle(MouseEvent &event);

    Scene &remove(ObjectBase &obj);
    Scene &remove(Model &obj);

    void run();

  private:
    static void handleEvents(Scene*);

    std::string scene_name;
    sf::RenderWindow window;
    std::unordered_set<ObjectBase *> object_container;
    std::unordered_set<Model *> model_container;
    std::unordered_set<Event *> event_container;
    std::unordered_set<MouseEvent *> mouse_event_container;
    std::vector<glm::vec3> light_dirs, light_points;
    std::vector<glm::ivec3> dl_colors, pl_colors;
    Camera *camera;
    Shader simple_shader, obj_shader;
    glm::ivec3 back_color;
};

} // namespace cge
