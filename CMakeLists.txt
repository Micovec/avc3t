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
set_property(TARGET avc3t PROPERTY CXX_STANDARD 26)

# Enable all warnings
if(MSVC)
   # Force to always compile with W4
   if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
       string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
   else()
       set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
   endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
   set(CMAKE_CXX_FLAGS -Wc++23-extensions)
endif()



#########################
# Includes
#########################

# Glm
target_include_directories(${PROJECT_NAME} PRIVATE vendor/glm)

# GLFW
if (EMSCRIPTEN)
    set(LFLAGS "-s USE_GLFW=3 -s MAX_WEBGL_VERSION=2 -s FULL_ES3 -o hello.html -sALLOW_MEMORY_GROWTH -sASSERTIONS -fexceptions")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "${LFLAGS}")
else()
    target_include_directories(${PROJECT_NAME} PRIVATE vendor/glfw/include)
    set(ADDITIONAL_LINK_LIBS ${ADDITIONAL_LINK_LIBS} nfd)
endif()

#set(LFLAGS "-s USE_GLFW=3 -s OFFSCREEN_FRAMEBUFFER=1 -s MAX_WEBGL_VERSION=2 -s LEGACY_GL_EMULATION -sFULL_ES3")
# -DCMAKE_EXE_LINKER_FLAGS=-sUSE_GLFW=3 -sMAX_WEBGL_VERSION=2 -sFULL_ES3

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
set(ASSIMP_BUILD_ZLIB ON)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL OFF)
add_subdirectory(vendor/assimp)

# GLM
add_subdirectory(vendor/glm)

# GLFW
if (NOT EMSCRIPTEN)
    set(GLFW_LIBRARY_TYPE STATIC)
    add_subdirectory(vendor/glfw)
endif()

# Native file dialog
if (NOT EMSCRIPTEN)
    add_subdirectory(vendor/nativefiledialog-extended)
endif()

#########################
# Link libraries
#########################

target_link_libraries(${PROJECT_NAME} assimp ${ADDITIONAL_LINK_LIBS} glfw ${OPENGL_LIBRARIES})

#########################
# Compile
#########################

install(TARGETS ${PROJECT_NAME})
