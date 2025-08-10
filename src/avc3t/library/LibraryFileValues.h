#pragma once

#include <cstdint>

#include "LibraryRecordNames.h"

namespace AVC3T {
    constexpr char SCENE_OBJECT_CONE_MTL[] = {
#embed SCENE_OBJECT_CONE_MTL_FILENAME
        , '\0'};

    constexpr char SCENE_OBJECT_CONE_OBJ[] = {
#embed SCENE_OBJECT_CONE_OBJ_FILENAME
        , '\0'};

    constexpr uint8_t SCENE_OBJECT_CONE_PNG[] = {
#embed SCENE_OBJECT_CONE_PNG_FILENAME
    };

    constexpr char SCENE_OBJECT_CUBE_MTL[] = {
#embed SCENE_OBJECT_CUBE_MTL_FILENAME
        , '\0'};

    constexpr char SCENE_OBJECT_CUBE_OBJ[] = {
#embed SCENE_OBJECT_CUBE_OBJ_FILENAME
        , '\0'};

    constexpr uint8_t SCENE_OBJECT_CUBE_PNG[] = {
#embed SCENE_OBJECT_CUBE_PNG_FILENAME
    };

    constexpr char SCENE_OBJECT_CYLINDER_MTL[] = {
#embed SCENE_OBJECT_CYLINDER_MTL_FILENAME
        , '\0'};

    constexpr char SCENE_OBJECT_CYLINDER_OBJ[] = {
#embed SCENE_OBJECT_CYLINDER_OBJ_FILENAME
        , '\0'};

    constexpr uint8_t SCENE_OBJECT_CYLINDER_PNG[] = {
#embed SCENE_OBJECT_CYLINDER_PNG_FILENAME
    };

    constexpr char SCENE_OBJECT_SPHERE_MTL[] = {
#embed SCENE_OBJECT_SPHERE_MTL_FILENAME
        , '\0'};

    constexpr char SCENE_OBJECT_SPHERE_OBJ[] = {
#embed SCENE_OBJECT_SPHERE_OBJ_FILENAME
        , '\0'};

    constexpr uint8_t SCENE_OBJECT_SPHERE_PNG[] = {
#embed SCENE_OBJECT_SPHERE_PNG_FILENAME
    };

    constexpr char SCENE_OBJECT_TRANSPARENT_CUBE_MTL[] = {
#embed SCENE_OBJECT_TRANSPARENT_CUBE_MTL_FILENAME
        , '\0'};

    constexpr char SCENE_OBJECT_TRANSPARENT_CUBE_OBJ[] = {
#embed SCENE_OBJECT_TRANSPARENT_CUBE_OBJ_FILENAME
        , '\0'};

    constexpr uint8_t SCENE_OBJECT_TRANSPARENT_CUBE_PNG[] = {
#embed SCENE_OBJECT_TRANSPARENT_CUBE_PNG_FILENAME
    };

    constexpr char SCENE_OBJECT_VECTOR_MTL[] = {
#embed SCENE_OBJECT_VECTOR_MTL_FILENAME
        , '\0'};

    constexpr char SCENE_OBJECT_VECTOR_OBJ[] = {
#embed SCENE_OBJECT_VECTOR_OBJ_FILENAME
        , '\0'};

    constexpr uint8_t SCENE_OBJECT_VECTOR_PNG[] = {
#embed SCENE_OBJECT_VECTOR_PNG_FILENAME
    };

    constexpr char SHADER_DEFAULT[] = {
#embed SHADER_DEFAULT_FILENAME
        , '\0'};

    constexpr char SHADER_LINES[] = {
#embed SHADER_LINES_FILENAME
        , '\0'};
}
