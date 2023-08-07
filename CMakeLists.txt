cmake_minimum_required(VERSION 3.1)
project(3DRenderer)

set(CMAKE_CXX_STANDARD 17)
message(STATUS "Project source dir: ${PROJECT_SOURCE_DIR}")

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories("C:/Program Files/stb")


file(GLOB SOURCES "src/*.cpp")

add_executable(3DRenderer main.cpp ${SOURCES})

if(WIN32)
    file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")
    target_sources(3DRenderer PRIVATE ${HEADER_LIST})

    set(SDL2_DIR "C:/Program Files/SDL2")
    set(CMAKE_PREFIX_PATH "C:/Program Files/glew-2.2.0")
    set(GLEW_INCLUDE_DIR "C:/Program Files/glew-2.2.0/include")
    set(GLEW_LIBRARY "C:/Program Files/glew-2.2.0/lib/Release/x64/glew32.lib")

    message(STATUS "Copying GLEW DLLs...")
    file(COPY "C:/Program Files/glew-2.2.0/bin/Release/x64/glew32.dll"
        DESTINATION ${CMAKE_BINARY_DIR}/Debug)

else()
    # Assuming that on UNIX systems, the libraries are installed in standard paths
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR}  ${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIRS})

    target_compile_options(3DRenderer PRIVATE -fdiagnostics-color=always -Wall -Werror -std=c++17 -g)
if(MSVC)
    target_link_libraries(3DRenderer ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} Vulkan::Vulkan)
else()
    target_link_libraries(3DRenderer ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} Vulkan::Vulkan)
endif()
