// #include <SFML/Graphics.hpp>
#include <camera/FPCamera.hpp>
#include <camera/TPCamera.hpp>
#include <engine/Scene.hpp>
#include <logic/EveryNSec.hpp>
#include <logic/FrameEvent.hpp>
#include <logic/IntersectEvent.hpp>
#include <logic/KeyboardEvent.hpp>
#include <objects/Cube.hpp>
#include <objects/Flat.hpp>
#include <objects/Model.hpp>
#include <random>

int getRandomInt(int min, int max) {
    static std::random_device rd; // Инициализация случайного устройства
    static std::mt19937 gen(rd()); // Генератор случайных чисел Mersenne Twister

    std::uniform_int_distribution<int> dist(
        min, max); // Распределение в диапазоне [min, max]
    return dist(gen);
}

constexpr int WIN_SCORE = 5;

int main() {
    cge::Scene scene("Bolt");

    sf::Image grass;
    grass.loadFromFile(
        "/home/zhava/Desktop/KGlabs/lab6/lab6/files/dirt2.png");

    sf::Image walltex;
    walltex.loadFromFile(
        "/home/zhava/Desktop/KGlabs/lab6/lab6/files/grass.png");

    sf::Image house_walltex;
    walltex.loadFromFile(
        "/home/zhava/Desktop/KGlabs/lab6/lab6/files/grass.png");

    cge::Flat floor("floor", grass, {0, 0, 1}, {1, 0, 0});
    floor.scale(glm::vec3(50));
    floor.translate({0, -0.002, 0});
    // cge::Flat global_floor("floor", grass, {0, 0, 1}, {1, 0, 0});
    // global_floor.translate({0, -0.01, 1});
    // global_floor.scale(glm::vec3(100));

    cge::Cube wall1("wall", walltex), wall2("wall", walltex),
        wall3("wall", walltex), wall4("wall", walltex);
    wall1.scale({1, 1, 75});
    wall1.translate({-25, 0, 0});
    wall2.scale({75, 1, 1});
    wall2.translate({0, 0, 25});
    wall3.scale({1, 1, 75});
    wall3.translate({25, 0, 0});
    wall4.scale({75, 1, 1});
    wall4.translate({0, 0, -25});

    // cge::Cube house_wall1("house_wall", house_walltex), house_wall2("house_wall", house_walltex),
    //     house_wall3("house_wall", house_walltex), house_wall4("house_wall", house_walltex);
    // house_wall1.scale({1, 1, 10});
    // house_wall1.translate({0, 0, 3});
    // house_wall2.scale({10, 1, 1});
    // house_wall2.translate({0, 0, 6});
    // house_wall3.scale({1, 1, 10});
    // house_wall3.translate({0, 0, 3});
    // house_wall4.scale({10, 1, 1});
    // house_wall4.translate({0, 0, 6});

    cge::Model character(
        "/home/zhava/Desktop/KGlabs/lab6/lab6/files/Models/Porsche_911_GT2.obj");
    // cge::Camera cam(glm::vec3(-2, 1, -2), glm::vec3(0));
    cge::CameraSettings customsSettings = cge::CameraSettings::Default;
    customsSettings.far = 60;
    // customsSettings.ortho = true;
    cge::TPCamera cam(10.0f, customsSettings);
    character.scale(glm::vec3(0.9));

    sf::Image metal;
    metal.loadFromFile(
        "/home/zhava/Desktop/KGlabs/lab6/lab6/files/red.png");

    cge::Model bolt(
        "/home/zhava/Desktop/KGlabs/lab6/lab6/files/Models/Bolt.obj");
    bolt.scale(glm::vec3(0.001));
    bolt.translate({5, 1, 0});

    cge::Model house(
        "/home/zhava/Desktop/KGlabs/lab6/lab6/files/Models/Bambo_House.obj");
    house.scale(glm::vec3(1.0));
    house.translate({0, 0, 2});

    cam.bind(&character);

    character.translate({0, -character.getBoundingBox().first.y, 0});

    uint score = 0;
    // cge::FrameEvent falling([&bolt]() {
    //     auto pos = bolt.getPosition();
    //     bolt.translate(-bolt.getPosition());
    //     // bolt.rotateY(glm::radians(5.0f));
    //     bolt.translate(pos + glm::vec3{0, -0.05, 0});
    // });
    // cge::IntersectEvent fall_to_floor(
    //     &global_floor, &bolt, [&global_floor, &bolt]() {
    //         auto oldpos = bolt.getPosition();
    //         bolt.translate(-oldpos);
    //         bolt.translate({getRandomInt(-4, 4), 10, getRandomInt(-4, 4)});
    //     });

    cge::IntersectEvent character_catch(
        &character, &bolt, [&bolt, &character, &score]() {
            character.rotateY(glm::radians(5.0f));
        });

    cge::IntersectEvent check_wall1(&character, &wall1, [&character, &wall1]() {
        auto depth = cge::intersectionDepth(character.getBoundingBox(),
                                            wall1.getBoundingBox());
        glm::vec3 correction(0.0f);
        correction.x = depth.x;
        character.translate(correction);
    });
    cge::IntersectEvent check_wall2(&character, &wall2, [&character, &wall2]() {
        auto depth = cge::intersectionDepth(character.getBoundingBox(),
                                            wall2.getBoundingBox());
        glm::vec3 correction(0.0f);
        correction.z = depth.z;
        character.translate(-correction);
    });
    cge::IntersectEvent check_wall3(&character, &wall3, [&character, &wall3]() {
        auto depth = cge::intersectionDepth(character.getBoundingBox(),
                                            wall3.getBoundingBox());
        glm::vec3 correction(0.0f);
        correction.x = depth.x;
        character.translate(-correction);
    });
    cge::IntersectEvent check_wall4(&character, &wall4, [&character, &wall4]() {
        auto depth = cge::intersectionDepth(character.getBoundingBox(),
                                            wall4.getBoundingBox());
        glm::vec3 correction(0.0f);
        correction.z = depth.z;
        character.translate(correction);
    });

    cge::KeyboardEvent move1(sf::Keyboard::W, [&cam, &character]() {
        auto scale = character.getScale();
        character.scale(1.0f / character.getScale());
        auto dir = cam.getDirection();
        dir = glm::normalize(glm::vec3{dir.x, 0, dir.z});
        character.translate(dir * 0.1f);
        character.scale(scale);
    });
    cge::KeyboardEvent move2(sf::Keyboard::A, [&cam, &character]() {
        auto scale = character.getScale();
        character.scale(1.0f / character.getScale());
        auto dir = cam.getDirection();
        dir = glm::normalize(glm::vec3{dir.x, 0, dir.z});
        dir = glm::vec3(
            glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0, 1, 0)) *
            glm::vec4(dir, 1));
        character.translate(dir * 0.1f);
        character.scale(scale);
    });
    cge::KeyboardEvent move3(sf::Keyboard::S, [&cam, &character]() {
        auto scale = character.getScale();
        character.scale(1.0f / character.getScale());
        auto dir = cam.getDirection();
        dir = glm::normalize(glm::vec3{dir.x, 0, dir.z});
        dir = glm::vec3(glm::rotate(glm::mat4(1), glm::radians(180.0f),
                                    glm::vec3(0, 1, 0)) *
                        glm::vec4(dir, 1));
        character.translate(dir * 0.1f);
        character.scale(scale);
    });
    cge::KeyboardEvent move4(sf::Keyboard::D, [&cam, &character]() {
        auto scale = character.getScale();
        character.scale(1.0f / character.getScale());
        auto dir = cam.getDirection();
        dir = glm::normalize(glm::vec3{dir.x, 0, dir.z});
        dir = glm::vec3(glm::rotate(glm::mat4(1), glm::radians(-90.0f),
                                    glm::vec3(0, 1, 0)) *
                        glm::vec4(dir, 1));
        character.translate(dir * 0.1f);
        character.scale(scale);
    });


    float rotationSpeed = 5.0f;
    cge::KeyboardEvent rotateLeft(sf::Keyboard::Left, [&character, &rotationSpeed]() {
        character.rotateY(glm::radians(-rotationSpeed)); // Отрицательный угол для поворота влево
    });

    cge::KeyboardEvent rotateRight(sf::Keyboard::Right, [&character, &rotationSpeed]() {
        character.rotateY(glm::radians(rotationSpeed)); // Положительный угол для поворота вправо
    });

    cge::MouseEvent me([&cam](float ox, float oy, float zoom) {
        cam.processMouse(ox, oy);
        cam.processZoom(zoom);        
    });

    // cge::Event winning{[&score]() { return score >= WIN_SCORE; },
    //                    [&scene]() {
    //                        scene.background({getRandomInt(0, 255),
    //                                          getRandomInt(0, 255),
    //                                          getRandomInt(0, 255)});
    //                    }};

    cge::DirectLight sky_light({0, -0.5, -0.5}, glm::uvec3{250, 250, 255} / 2u);

    scene.add(floor)
        // .add(global_floor)
        .add(character)
        .add(sky_light)
        .add(sky_light)
        .add(wall1)
        .add(wall2)
        .add(wall3)
        .add(wall4)
        // .add(house_wall1)
        // .add(house_wall2)
        // .add(house_wall3)
        // .add(house_wall4)
        .add(bolt)
        .add(house)
        .use(cam)
        .background({200, 200, 255})
        // .handle(falling)
        // .handle(fall_to_floor)
        // .handle(character_catch)
        .handle(move1)
        .handle(move2)
        .handle(move3)
        .handle(move4)
        .handle(check_wall1)
        .handle(check_wall2)
        .handle(check_wall3)
        .handle(check_wall4)
        // .handle(winning)
        .handle(me);

    scene.run();
}