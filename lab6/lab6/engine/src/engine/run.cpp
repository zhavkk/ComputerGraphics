#include "../../include/engine/Scene.hpp"
#include <thread>

namespace cge {

void Scene::handleEvents(Scene* s) {
    while(s->window.isOpen()) {
        glm::vec2 mouse_offset(0);
        glm::f32 mouse_scroll = 0;

        {
            sf::Event event;
            while (s->window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    s->window.close();
                }
                if (event.KeyPressed &&
                    event.key.code == sf::Keyboard::Escape) {
                    s->window.close();
                }
                if (event.type == sf::Event::MouseWheelScrolled) {
                    mouse_scroll = event.mouseWheelScroll.delta;
                }
            }

            int mouseX = sf::Mouse::getPosition(s->window).x;
            int mouseY = sf::Mouse::getPosition(s->window).y;

            mouse_offset.x = mouseX - (float)s->window.getSize().x / 2;
            mouse_offset.y = mouseY - (float)s->window.getSize().y / 2;

            sf::Mouse::setPosition(
                static_cast<sf::Vector2i>(s->window.getSize()) / 2, s->window);
        }

        for (auto& event : s->event_container) {
            if (event->condition()) {
                event->action();
            }
        }
        if (mouse_offset != glm::vec2(0) || mouse_scroll != 0) {
            for (auto& event : s->mouse_event_container) {
                event->action(mouse_offset.x, mouse_offset.y, mouse_scroll);
            }
        }
    }
}

void Scene::run() {
    back_color.x = glm::clamp(back_color.x, 0, 255);
    back_color.y = glm::clamp(back_color.y, 0, 255);
    back_color.z = glm::clamp(back_color.z, 0, 255);
    GLenum error = glGetError();
    if (!window.setActive(true)) {
        throw std::runtime_error("Failed to activate OpenGL context.");
    }
    // std::thread t(handleEvents, this);
    while (window.isOpen()) {
        glm::vec2 mouse_offset(0);
        glm::f32 mouse_scroll = 0;

        {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.KeyPressed &&
                    event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (event.type == sf::Event::MouseWheelScrolled) {
                    mouse_scroll = event.mouseWheelScroll.delta;
                }
            }

            int mouseX = sf::Mouse::getPosition(window).x;
            int mouseY = sf::Mouse::getPosition(window).y;

            mouse_offset.x = mouseX - (float)window.getSize().x / 2;
            mouse_offset.y = mouseY - (float)window.getSize().y / 2;

            sf::Mouse::setPosition(
                static_cast<sf::Vector2i>(window.getSize()) / 2, window);
        }

        for (auto& event : event_container) {
            if (event->condition()) {
                event->action();
            }
        }
        if (mouse_offset != glm::vec2(0) || mouse_scroll != 0) {
            for (auto& event : mouse_event_container) {
                event->action(mouse_offset.x, mouse_offset.y, mouse_scroll);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window.clear({back_color.r, back_color.g, back_color.b});

        simple_shader.use();
        simple_shader.set("cameraMatrix", camera->getMatrix(window));
        simple_shader.set("cameraPos", camera->getPosition());

        simple_shader.setArr("light_dirs", light_dirs);
        simple_shader.setArr("light_points", light_points);
        simple_shader.setArr("dl_colors", dl_colors);
        simple_shader.setArr("pl_colors", pl_colors);

        simple_shader.set("dl_size", dl_colors.size());
        simple_shader.set("pl_size", pl_colors.size());

        for (auto object_ptr : object_container) {
            object_ptr->draw(simple_shader);
        }

        obj_shader.use();
        obj_shader.set("cameraMatrix", camera->getMatrix(window));
        obj_shader.set("cameraPos", camera->getPosition());

        obj_shader.setArr("light_dirs", light_dirs);
        obj_shader.setArr("light_points", light_points);
        obj_shader.setArr("dl_colors", dl_colors);
        obj_shader.setArr("pl_colors", pl_colors);

        obj_shader.set("dl_size", dl_colors.size());
        obj_shader.set("pl_size", pl_colors.size());

        std::cout << '\r' << model_container.size();
        for (auto object_ptr : model_container) {
            object_ptr->draw(obj_shader);
        }

        window.display();
    }
    // t.join();
}

} // namespace cge
