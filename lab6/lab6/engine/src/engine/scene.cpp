#include "../../include/engine/Scene.hpp"

#include <filesystem>

namespace cge {

std::string getShaderDir() {
    std::filesystem::path currentFilePath(__FILE__);
    std::filesystem::path projectRoot =
        currentFilePath.parent_path().parent_path().parent_path();

    std::filesystem::path shaderPath = projectRoot / "shaders";

    return shaderPath.string();
}

Scene::Scene(const std::string &name)
    : scene_name(name),
      window(sf::VideoMode::getDesktopMode(), name, sf::Style::Fullscreen,
             sf::ContextSettings{24, 8, 4, 3, 3}) {

    window.setVerticalSyncEnabled(true);

    if (!window.setActive(true)) {
        throw std::runtime_error("Failed to activate OpenGL context.");
    }
    auto status = glewInit();
    if (status != GLEW_OK) {
        throw std::runtime_error(
            reinterpret_cast<const char *>(glewGetErrorString(status)));
    }
    glewExperimental = GL_TRUE;
    glEnable(GL_DEPTH_TEST);

    {
        Shader tmp(getShaderDir() + "/vertex.glsl",
                   getShaderDir() + "/fragment.glsl");
        simple_shader = tmp;
        tmp.ID = 0;
    }

    {
        Shader tmp(getShaderDir() + "/obj_vertex.glsl",
                   getShaderDir() + "/obj_fragment.glsl");
        obj_shader = tmp;
        tmp.ID = 0;
    }
}

Scene &Scene::add(ObjectBase &obj) {
    object_container.insert(&obj);
    return *this;
}
Scene &Scene::add(Model &obj) {
    model_container.insert(&obj);
    return *this;
}
Scene &Scene::add(const DirectLight &light) {
    light_dirs.push_back(light.getDirection());
    dl_colors.push_back(light.getColor());
    return *this;
}
Scene &Scene::add(const PointLight &light) {
    light_points.push_back(light.getPosition());
    pl_colors.push_back(light.getColor());
    return *this;
}
Scene &Scene::handle(Event &event) {
    event_container.insert(&event);
    return *this;
}
Scene &Scene::handle(MouseEvent &event) {
    mouse_event_container.insert(&event);
    return *this;
}
Scene &Scene::use(Camera &cam) {
    camera = &cam;
    return *this;
}
Scene &Scene::use(FPCamera &cam) { return use(static_cast<Camera &>(cam)); }
Scene &Scene::use(TPCamera &cam) { return use(static_cast<Camera &>(cam)); }
Scene &Scene::remove(ObjectBase &obj) {
    object_container.erase(&obj);
    return *this;
}
Scene &Scene::remove(Model &obj) {
    model_container.erase(&obj);
    return *this;
}

Scene &Scene::background(const glm::ivec3 &color) {
    back_color = color;
    return *this;
}

} // namespace cge
