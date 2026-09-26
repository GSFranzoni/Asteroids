cmake_minimum_required(VERSION 3.16)

project(asteroids LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(SFML 2.5 REQUIRED COMPONENTS audio)

add_executable(asteroids
    src/main.cpp
    src/Asteroid.cpp
    src/Boss.cpp
    src/Physic.cpp
    src/Ship.cpp
    src/Shot.cpp
    src/Sound.cpp
    src/Timer.cpp
)

target_include_directories(asteroids PRIVATE include)
if(TARGET SFML::Audio)
    set(SFML_AUDIO_TARGET SFML::Audio)
else()
    set(SFML_AUDIO_TARGET sfml-audio)
endif()

target_link_libraries(asteroids PRIVATE OpenGL::GL OpenGL::GLU GLUT::GLUT ${SFML_AUDIO_TARGET})

if(MSVC)
    target_compile_options(asteroids PRIVATE /W4)
else()
    target_compile_options(asteroids PRIVATE -Wall -Wextra -pedantic)
endif()

# The executable expects assets relative to its working directory.
add_custom_command(TARGET asteroids POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:asteroids>/assets
)
