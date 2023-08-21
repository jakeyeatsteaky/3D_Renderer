cmake_minimum_required(VERSION 3.1)
project(3DRenderer)

set(CMAKE_CXX_STANDARD 17)
message(STATUS "Project source dir: ${PROJECT_SOURCE_DIR}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

if(MSVC)
    add_compile_options(/W4 /WX /Zi)
else()
    add_compile_options(-fdiagnostics-color=always -Wall -Werror -std=c++17 -g)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty_src/include)
include_directories("C:/Program Files/stb")

file(GLOB SOURCES "src/*.cpp" "thirdparty_src/src/*.cpp")
add_executable(3DRenderer main.cpp ${SOURCES})

if(WIN32)
    file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")
    file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
    target_sources(3DRenderer PRIVATE ${HEADER_LIST})

    set(SDL2_DIR "C:/Program Files/SDL2")
    set(CMAKE_PREFIX_PATH "C:/Program Files/glew-2.2.0")
    set(GLEW_INCLUDE_DIR "C:/Program Files/glew-2.2.0/include")
    set(GLEW_LIBRARY "C:/Program Files/glew-2.2.0/lib/Release/x64/glew32.lib")

    message(STATUS "Copying GLEW DLLs...")
    file(COPY "C:/Program Files/glew-2.2.0/bin/Release/x64/glew32.dll"
        DESTINATION ${CMAKE_BINARY_DIR}/Debug)

    # Specify the paths to the shader source files
    set(VERT_SHADER_FILE "${PROJECT_SOURCE_DIR}/shaders/vulk_shader.vert")
    set(FRAG_SHADER_FILE "${PROJECT_SOURCE_DIR}/shaders/vulk_shader.frag")
    
    # Specify the paths to the output SPV files
    set(VERT_SPV_FILE "${PROJECT_SOURCE_DIR}/shaders/binaries/vert.spv")
    set(FRAG_SPV_FILE "${PROJECT_SOURCE_DIR}/shaders/binaries/frag.spv")
    
    # Compile vertex shader
    execute_process(
        COMMAND C:/VulkanSDK/1.3.243.0/Bin/glslc.exe ${VERT_SHADER_FILE} -o ${VERT_SPV_FILE}
        RESULT_VARIABLE VERT_COMPILE_RESULT
    )
    if(VERT_COMPILE_RESULT)
        message(FATAL_ERROR "Failed to compile vertex shader")
    endif()
    
    # Compile fragment shader
    execute_process(
        COMMAND C:/VulkanSDK/1.3.243.0/Bin/glslc.exe ${FRAG_SHADER_FILE} -o ${FRAG_SPV_FILE}
        RESULT_VARIABLE FRAG_COMPILE_RESULT
    )
    if(FRAG_COMPILE_RESULT)
        message(FATAL_ERROR "Failed to compile fragment shader")
endif()


else()
    # Assuming that on UNIX systems, the libraries are installed in standard paths
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIRS})

target_link_libraries(3DRenderer ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} Vulkan::Vulkan)
