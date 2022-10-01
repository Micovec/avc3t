cmake_minimum_required(VERSION 3.29)

project(avc3t)

file(GLOB_RECURSE sources
    src/avc3t/*.h
    src/avc3t/*.cpp)

# ImGui
file(GLOB imgui_sources
    src/vendor/imgui/*.h
    src/vendor/imgui/*.cpp
    src/vendor/imgui/backends/imgui_impl_opengl3.h
    src/vendor/imgui/backends/imgui_impl_opengl3.cpp
    src/vendor/imgui/backends/imgui_impl_glfw.h
    src/vendor/imgui/backends/imgui_impl_glfw.cpp
    src/vendor/imgui/misc/cpp/*.h
    src/vendor/imgui/misc/cpp/*.cpp)

file(GLOB glad
    src/vendor/glad/src/*.h
    src/vendor/glad/src/*.c)

add_executable(avc3t ${sources} ${imgui_sources} ${glad})
set_property(TARGET avc3t PROPERTY CXX_STANDARD 23)

# Enable all warnings
if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()


#########################
# Includes
#########################

# Glm
target_include_directories(${PROJECT_NAME} PRIVATE vendor/glm)

# GLFW
target_include_directories(${PROJECT_NAME} PRIVATE vendor/glfw/include)

# GLAD
target_include_directories(${PROJECT_NAME} PRIVATE src/vendor/glad/include)

# ImGui
target_include_directories(${PROJECT_NAME} PRIVATE src/vendor)
target_include_directories(${PROJECT_NAME} PRIVATE src/vendor/imgui)
target_include_directories(${PROJECT_NAME} PRIVATE src/vendor/imgui/backends)

# OpenGL package
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

#########################
# Build subprojects
#########################

# Assimp
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(vendor/assimp)

# GLM
add_subdirectory(vendor/glm)

# GLFW
set(GLFW_LIBRARY_TYPE STATIC)
add_subdirectory(vendor/glfw)

# Native file dialog
add_subdirectory(vendor/nativefiledialog-extended)

#########################
# Link libraries
#########################

target_link_libraries(avc3t glfw assimp nfd ${OPENGL_LIBRARIES})

#########################
# Compile
#########################

install(TARGETS ${PROJECT_NAME})
