cmake_minimum_required(VERSION 3.10)
project(LightingWithShaders)

# Найти OpenGL
find_package(OpenGL REQUIRED)

# Найти SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Указать стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавить исполняемый файл
add_executable(LightingWithShaders main.cpp)

# Указать директории для заголовков
target_include_directories(LightingWithShaders PRIVATE 
    ${OPENGL_INCLUDE_DIRS} 
    /usr/include
)

# Связывание библиотек
target_link_libraries(LightingWithShaders 
    OpenGL::GL 
    GLEW 
    GLU 
    sfml-system 
    sfml-window 
    sfml-graphics
)
