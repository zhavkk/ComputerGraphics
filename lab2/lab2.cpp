#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <cmath>

struct Color {
    float r, g, b;
};

GLfloat lightPos[3] = { 1.0f, 1.0f, 1.0f };

float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationSpeedX = 0.5f;
float rotationSpeedY = 0.3f;

bool isPerspective = true;

float camX = 2.0f, camY = 2.0f, camZ = 2.0f; 
float lookX = 0.0f, lookY = 0.0f, lookZ = 0.0f; 
float cameraSpeed = 0.1f; 

Color calculateShading(const GLfloat* normal, const GLfloat* lightDir) {
    float dotProduct = normal[0] * lightDir[0] + normal[1] * lightDir[1] + normal[2] * lightDir[2];
    dotProduct = std::max(0.0f, dotProduct);

    Color color;
    color.r = dotProduct;
    color.g = dotProduct;
    color.b = dotProduct;

    return color;
}

void drawCube() {
    const GLfloat normals[6][3] = {
        { 0.0f, 0.0f, 1.0f },  { 0.0f, 0.0f, -1.0f },
        { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },  { 0.0f, -1.0f, 0.0f }
    };

    const GLfloat vertices[8][3] = {
        { -0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f },
        { 0.5f, 0.5f, -0.5f },   { -0.5f, 0.5f, -0.5f },
        { -0.5f, -0.5f, 0.5f },  { 0.5f, -0.5f, 0.5f },
        { 0.5f, 0.5f, 0.5f },    { -0.5f, 0.5f, 0.5f }
    };

    const GLint faces[6][4] = {
        { 4, 5, 6, 7 }, 
        { 0, 1, 2, 3 }, 
        { 0, 3, 7, 4 }, 
        { 1, 2, 6, 5 }, 
        { 3, 2, 6, 7 }, 
        { 0, 1, 5, 4 }  
    };

    GLfloat lightDir[3] = { lightPos[0], lightPos[1], lightPos[2] };
    float length = std::sqrt(lightDir[0] * lightDir[0] + lightDir[1] * lightDir[1] + lightDir[2] * lightDir[2]);
    for (int i = 0; i < 3; ++i) {
        lightDir[i] /= length;
    }

    for (int i = 0; i < 6; ++i) {
        Color shade = calculateShading(normals[i], lightDir);
        glColor3f(shade.r, shade.g, shade.b);

        glBegin(GL_QUADS);
        for (int j = 0; j < 4; ++j) {
            glVertex3fv(vertices[faces[i][j]]);
        }
        glEnd();
    }
}

void drawLightSource() {
    glColor3f(1.0f, 1.0f, 0.0f); 

    glPushMatrix();
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]); 

    glBegin(GL_QUADS);
    
    glVertex3f(-0.05f, -0.05f, 0.05f);
    glVertex3f(0.05f, -0.05f, 0.05f);
    glVertex3f(0.05f, 0.05f, 0.05f);
    glVertex3f(-0.05f, 0.05f, 0.05f);

    glVertex3f(-0.05f, -0.05f, -0.05f);
    glVertex3f(0.05f, -0.05f, -0.05f);
    glVertex3f(0.05f, 0.05f, -0.05f);
    glVertex3f(-0.05f, 0.05f, -0.05f);

    glVertex3f(-0.05f, -0.05f, -0.05f);
    glVertex3f(-0.05f, -0.05f, 0.05f);
    glVertex3f(-0.05f, 0.05f, 0.05f);
    glVertex3f(-0.05f, 0.05f, -0.05f);

    glVertex3f(0.05f, -0.05f, -0.05f);
    glVertex3f(0.05f, -0.05f, 0.05f);
    glVertex3f(0.05f, 0.05f, 0.05f);
    glVertex3f(0.05f, 0.05f, -0.05f);

    glVertex3f(-0.05f, 0.05f, -0.05f);
    glVertex3f(0.05f, 0.05f, -0.05f);
    glVertex3f(0.05f, 0.05f, 0.05f);
    glVertex3f(-0.05f, 0.05f, 0.05f);

    glVertex3f(-0.05f, -0.05f, -0.05f);
    glVertex3f(0.05f, -0.05f, -0.05f);
    glVertex3f(0.05f, -0.05f, 0.05f);
    glVertex3f(-0.05f, -0.05f, 0.05f);

    glEnd();
    
    glPopMatrix();
}

int main() {
    sf::Window window(sf::VideoMode(800, 600), "3D Cube with Camera Control", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    bool running = true;
    while (running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                running = false;
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    running = false;
                if (event.key.code == sf::Keyboard::P) {
                    isPerspective = !isPerspective;
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    if (isPerspective) {
                        gluPerspective(45.0, 800.0 / 600.0, 1.0, 10.0);
                    } else {
                        glOrtho(-2.0, 2.0, -1.5, 1.5, 1.0, 10.0);
                    }
                    glMatrixMode(GL_MODELVIEW);
                }
                if (event.key.code == sf::Keyboard::Up)
                    camZ -= cameraSpeed; 
                if (event.key.code == sf::Keyboard::Down)
                    camZ += cameraSpeed; 
                if (event.key.code == sf::Keyboard::Left)
                    camX -= cameraSpeed; 
                if (event.key.code == sf::Keyboard::Right)
                    camX += cameraSpeed; 
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0.0, 1.0, 0.0);

        rotationX += rotationSpeedX;
        rotationY += rotationSpeedY;
        glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

        drawCube();
        drawLightSource();

        window.display();
    }

    return 0;
}
