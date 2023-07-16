cmake_minimum_required(VERSION 3.1)
project(3DRenderer)

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

    include_directories(${PROJECT_SOURCE_DIR}/include)
    include_directories(/usr/local/include)

    file(GLOB SOURCES "src/*.cpp")

    add_executable(3DRenderer main.cpp ${SOURCES})

    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(SDL2 REQUIRED)

    target_link_libraries(3DRenderer ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES})
else()
    message(FATAL_ERROR "This CMakeLists.txt is for Linux only!")
endif()
