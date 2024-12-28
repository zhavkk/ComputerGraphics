#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>

glm::vec3 interpolate(const glm::vec3& start, const glm::vec3& end, float t) {
    return start + t * (end - start);
}

void setCamera(const glm::vec3& position, const glm::vec3& target) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z, target.x, target.y, target.z, 0.0f, 1.0f, 0.0f);
}

void drawCube(float size) {
    float half = size / 2.0f;

glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); 
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);

        glColor3f(0.0f, 1.0f, 0.0f); 
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);

        glColor3f(0.0f, 0.0f, 1.0f); 
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);

        glColor3f(1.0f, 1.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);

        glColor3f(1.0f, 0.0f, 1.0f); 
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);

        // glColor3f(0.0f, 1.0f, 1.0f); 
        // glVertex3f(1.0f, 1.0f, 1.0f);
        // glVertex3f(1.0f, -1.0f, 1.0f);
        // glVertex3f(1.0f, -1.0f, -1.0f);
        // glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();

}

void drawScene() {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); 
    drawCube(2.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0f, 0.0f, -5.0f); 
    drawCube(1.5f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.0f, 0.0f, 5.0f); 
    drawCube(1.0f);
    glPopMatrix();
}

int main() {
    sf::Window window(sf::VideoMode(800, 600), "3D Scene with Camera Transitions", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    std::vector<glm::vec3> cameraPositions = {
        glm::vec3(0.0f, 5.0f, 10.0f),
        glm::vec3(10.0f, 5.0f, 0.0f),
        glm::vec3(-10.0f, 5.0f, -10.0f),
        glm::vec3(0.0f, 10.0f, 0.0f) 
    };
    // glm::vec3 positionA(0.0f, 5.0f, 10.0f);
    // glm::vec3 positionB(10.0f, 5.0f, 0.0f);

    glm::vec3 target(0.0f, 0.0f, 0.0f); 
    int currentIndex = 0;
    int nextIndex = 1;

    float t = 0.0f;
    float transitionSpeed = 0.01f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                transitionSpeed += 0.001f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                transitionSpeed = std::max(0.001f, transitionSpeed - 0.001f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                currentIndex = nextIndex;
                //nextIndex = (nextIndex + 1) % cameraPositions.size();
                nextIndex = (nextIndex + 1);
                t = 0.0f; 
            }
        }

        t += transitionSpeed;
        if (t >= 1.0f) {
            t = 0.0f;
            currentIndex = nextIndex;
            nextIndex = (nextIndex + 1) % cameraPositions.size();
        }

        glm::vec3 currentPos = interpolate(cameraPositions[currentIndex], cameraPositions[nextIndex], t);

        // glm::vec3 currentPos = interpolate(positionA, positionB, t);

        // // Обратный переход, если t превышает 1.0
        // if (t >= 1.0f) {
        //     std::swap(positionA, positionB); // Меняем точки местами
        //     t = 0.0f; // Сбрасываем интерполяцию
        // }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        setCamera(currentPos, target);

        drawScene();

        window.display();
    }

    return 0;
}
