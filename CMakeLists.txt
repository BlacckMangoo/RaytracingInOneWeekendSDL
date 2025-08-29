
cmake_minimum_required(VERSION 3.16)

project(Raytracing LANGUAGES CXX)

find_package(SDL3 REQUIRED CONFIG)

add_executable(raytracing
    renderer.cpp
    HeaderFiles/vec3.h
    HeaderFiles/Ray.h
    HeaderFiles/hittable.h
    HeaderFiles/sphere.h
    HeaderFiles/hittableList.h
    HeaderFiles/utility.h
    HeaderFiles/camera.h
    HeaderFiles/color.h
    HeaderFiles/interval.h
)

target_include_directories(raytracing PRIVATE ${CMAKE_SOURCE_DIR}/HeaderFiles)
target_link_libraries(raytracing PRIVATE SDL3::SDL3)
set_property(TARGET raytracing PROPERTY CXX_STANDARD 20)

if(WIN32)
    add_custom_command(TARGET raytracing POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE_DIR:raytracing>
    )
endif()
