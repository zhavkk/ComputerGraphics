#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <vector>
#include <cmath>
#include <chrono>

struct Point {
    float x;
    float y;
};

Point bezierPoint(float t, const std::vector<Point>& controlPoints)
{
    if (controlPoints.size() != 4)
        return {0, 0};

    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    Point p;
    p.x = uuu * controlPoints[0].x;
    p.x += 3 * uu * t * controlPoints[1].x;
    p.x += 3 * u * tt * controlPoints[2].x;
    p.x += ttt * controlPoints[3].x;

    p.y = uuu * controlPoints[0].y;
    p.y += 3 * uu * t * controlPoints[1].y;
    p.y += 3 * u * tt * controlPoints[2].y;
    p.y += ttt * controlPoints[3].y;

    return p;
}

void drawBezier(const std::vector<Point>& controlPoints)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    //glLineWidth(3.0f); // Устанавливаем ширину линии в 3 пикселя
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1.0f; t += 0.001f)
    {
        Point p = bezierPoint(t, controlPoints);
        glVertex2f(p.x, p.y);
    }
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f); 
    for (const auto& cp : controlPoints)
    {
        glVertex2f(cp.x, cp.y);
    }
    glEnd();
}

struct AnimatedObject {
    Point position;
    float size;
};

int main()
{
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;

    sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bezier Animation", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    std::vector<Point> controlPoints = {
        {100, 100},
        {200, 500},
        {600, 500},
        {700, 100}
    };

    AnimatedObject obj;
    obj.size = 20.0f;

    float t = 0.0f;
    float speed = 0.5f; // Начальная скорость
    auto lastTime = std::chrono::high_resolution_clock::now();

    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                running = false;
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    speed += 0.1f;
                if (event.key.code == sf::Keyboard::Down)
                    speed = std::max(0.1f, speed - 0.1f);
            }
        }

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        t += speed * deltaTime.count() * 0.1f;
        if (t > 1.0f)
            t -= 1.0f;

        obj.position = bezierPoint(t, controlPoints);

        obj.size = 10.0f + 20.0f * std::sin(t * M_PI);

        glClear(GL_COLOR_BUFFER_BIT);

        drawBezier(controlPoints);

        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(obj.position.x, obj.position.y);
        int numSegments = 20;
        for (int i = 0; i <= numSegments; ++i)
        {
            float angle = i * 2.0f * M_PI / numSegments;
            float dx = cos(angle) * obj.size;
            float dy = sin(angle) * obj.size;
            glVertex2f(obj.position.x + dx, obj.position.y + dy);
        }
        glEnd();

        window.display();
    }

    return 0;
}
