cmake_minimum_required(VERSION 3.16)
project(software_renderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENTIONS ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -O0")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)

#adding libraries
add_library(math_lib
    src/math/vector/Float2.cpp
    src/math/vector/Float3.cpp
    src/math/vector/Float4.cpp
    src/math/matrix/Matrix4.cpp
    src/math/Transform.cpp
)

target_include_directories(math_lib PUBLIC src)

add_library(render_lib
    src/render/Camera.cpp
    src/render/Framebuffer.cpp
    src/render/Renderer.cpp
    src/render/Scene.cpp
)

target_include_directories(render_lib PUBLIC src)

add_library(obj_lib
    src/obj/Obj.cpp
)

target_include_directories(obj_lib PUBLIC src)

add_library(geometry_lib
    src/geometry/Triangle.cpp
    src/geometry/SceneObject.cpp
    src/geometry/Bresenhams_Line.cpp
)

target_include_directories(geometry_lib PUBLIC src)


add_library(imgui
    lib/imgui/imgui.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_tables.cpp
    lib/imgui/imgui_widgets.cpp

    lib/imgui/backends/imgui_impl_sdl3.cpp
    lib/imgui/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(imgui PUBLIC
    lib/imgui
    lib/imgui/backends
)

# linking libraries
target_link_libraries(render_lib PRIVATE SDL3::SDL3)

target_link_libraries(render_lib PUBLIC math_lib)

target_link_libraries(render_lib PUBLIC geometry_lib)

target_link_libraries(obj_lib PUBLIC math_lib)


target_link_libraries(imgui
    PUBLIC SDL3::SDL3
)

# adding executables
add_executable(main
    src/main.cpp
)

target_link_libraries(main PRIVATE render_lib obj_lib imgui)

add_executable(testing 
    src/Testing/matrix.cpp
)

target_link_libraries(testing PRIVATE math_lib)
