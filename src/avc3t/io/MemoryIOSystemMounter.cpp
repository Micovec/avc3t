#include "MemoryIOSystemMounter.h"
#include <iostream>

namespace AVC3T {
    void MemoryIOSystemMounter::Mount(MemoryIOSystem& memoryIOSystem) {
        MountObjects(memoryIOSystem);
        MountShaders(memoryIOSystem);
    }

    void MemoryIOSystemMounter::MountObjects(MemoryIOSystem& memoryIOSystem) {
        memoryIOSystem.OpenFile(SCENE_OBJECT_CONE_MTL_FILENAME).WriteText(SCENE_OBJECT_CONE_MTL);
        memoryIOSystem.OpenFile(SCENE_OBJECT_CONE_OBJ_FILENAME).WriteText(SCENE_OBJECT_CONE_OBJ);
        memoryIOSystem.OpenFile(SCENE_OBJECT_CONE_PNG_FILENAME).WriteRaw(SCENE_OBJECT_CONE_PNG, sizeof(SCENE_OBJECT_CONE_PNG));

        memoryIOSystem.OpenFile(SCENE_OBJECT_CUBE_MTL_FILENAME).WriteText(SCENE_OBJECT_CUBE_MTL);
        memoryIOSystem.OpenFile(SCENE_OBJECT_CUBE_OBJ_FILENAME).WriteText(SCENE_OBJECT_CUBE_OBJ);
        memoryIOSystem.OpenFile(SCENE_OBJECT_CUBE_PNG_FILENAME).WriteRaw(SCENE_OBJECT_CUBE_PNG, sizeof(SCENE_OBJECT_CUBE_PNG));

        memoryIOSystem.OpenFile(SCENE_OBJECT_CYLINDER_MTL_FILENAME).WriteText(SCENE_OBJECT_CYLINDER_MTL);
        memoryIOSystem.OpenFile(SCENE_OBJECT_CYLINDER_OBJ_FILENAME).WriteText(SCENE_OBJECT_CYLINDER_OBJ);
        memoryIOSystem.OpenFile(SCENE_OBJECT_CYLINDER_PNG_FILENAME).WriteRaw(SCENE_OBJECT_CYLINDER_PNG, sizeof(SCENE_OBJECT_CYLINDER_PNG));

        memoryIOSystem.OpenFile(SCENE_OBJECT_SPHERE_MTL_FILENAME).WriteText(SCENE_OBJECT_SPHERE_MTL);
        memoryIOSystem.OpenFile(SCENE_OBJECT_SPHERE_OBJ_FILENAME).WriteText(SCENE_OBJECT_SPHERE_OBJ);
        memoryIOSystem.OpenFile(SCENE_OBJECT_SPHERE_PNG_FILENAME).WriteRaw(SCENE_OBJECT_SPHERE_PNG, sizeof(SCENE_OBJECT_SPHERE_PNG));

        memoryIOSystem.OpenFile(SCENE_OBJECT_TRANSPARENT_CUBE_MTL_FILENAME).WriteText(SCENE_OBJECT_TRANSPARENT_CUBE_MTL);
        memoryIOSystem.OpenFile(SCENE_OBJECT_TRANSPARENT_CUBE_OBJ_FILENAME).WriteText(SCENE_OBJECT_TRANSPARENT_CUBE_OBJ);
        memoryIOSystem.OpenFile(SCENE_OBJECT_TRANSPARENT_CUBE_PNG_FILENAME).WriteRaw(SCENE_OBJECT_TRANSPARENT_CUBE_PNG, sizeof(SCENE_OBJECT_TRANSPARENT_CUBE_PNG));

        memoryIOSystem.OpenFile(SCENE_OBJECT_VECTOR_MTL_FILENAME).WriteText(SCENE_OBJECT_VECTOR_MTL);
        memoryIOSystem.OpenFile(SCENE_OBJECT_VECTOR_OBJ_FILENAME).WriteText(SCENE_OBJECT_VECTOR_OBJ);
        memoryIOSystem.OpenFile(SCENE_OBJECT_VECTOR_PNG_FILENAME).WriteRaw(SCENE_OBJECT_VECTOR_PNG, sizeof(SCENE_OBJECT_VECTOR_PNG));
    }
    void MemoryIOSystemMounter::MountShaders(MemoryIOSystem& memoryIOSystem) {
        memoryIOSystem.OpenFile(SHADER_DEFAULT_FILENAME).WriteText(SHADER_DEFAULT);
        memoryIOSystem.OpenFile(SHADER_LINES_FILENAME).WriteText(SHADER_LINES);
    }
}