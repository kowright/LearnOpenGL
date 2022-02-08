cmake_minimum_required(VERSION 3.12)

# set(CMAKE_C_STANDARD 99)
project(LearnOpenGL VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


add_subdirectory(LearnOpenGL)
add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)

