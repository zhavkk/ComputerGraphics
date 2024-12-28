set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(engine)
include_directories(./engine/include)

include_directories(${sfml_SOURCE_DIR}/include)
include_directories(${assimp_SOURCE_DIR}/include)
add_executable(lab6 src/main.cpp)
target_link_libraries(lab6 computer-graphics-engine)

# cmake_minimum_required(VERSION 3.15)
# project(Lab6)

# # Установка стандарта C++
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Добавление поддиректории engine
# add_subdirectory(engine)
# include_directories(./engine/include)

# # Подключение библиотек SFML
# find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

# # Подключение библиотеки Assimp
# find_package(Assimp REQUIRED)

# # Поиск OpenGL
# find_package(OpenGL REQUIRED)

# # Поиск GLEW
# find_package(GLEW REQUIRED)

# # Основной исполняемый файл
# add_executable(lab6 src/main.cpp)

# # Линковка
# target_link_libraries(lab6 PRIVATE 
#     computer-graphics-engine
#     sfml-graphics sfml-system sfml-window
#     OpenGL::GL
#     GLEW::GLEW
#     assimp
# )

