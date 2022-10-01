#include "MeshLoader.h"

#include <filesystem>
#include <fstream>
#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "../library/TextureLibrary.h"
#include "../utils/StringUtils.h"

namespace AVC3T {
    std::shared_ptr<Mesh> MeshLoader::LoadObj(const std::string& filename) {
        Assimp::Importer importer;

        const aiScene*   scene = importer.ReadFile(filename,
                                                   aiProcess_Triangulate |              // Triangulate polygons
                                                       aiProcess_PreTransformVertices | // Transforms scene hierarchy into
                                                                                        // one root with geometry-leafs only.
                                                                                        // For more see Doc.
                                                       aiProcess_GenSmoothNormals |     // Calculate normals per vertex.
                                                       aiProcess_JoinIdenticalVertices);

        if (scene == nullptr) {
            std::cerr << "Could not load mesh: " << importer.GetErrorString() << std::endl;
            throw "Could not load mesh: " + std::string(importer.GetErrorString());
        }

        if (scene->mNumMeshes != 1) {
            std::cerr << "This mesh loader can import only files with just one mesh" << std::endl;
            throw "This mesh loader can import only files with just one mesh";
        }

        const aiMesh* mesh = scene->mMeshes[0];

        // TODO replace this with std::vector
        float* textureCoords = new float[2 * mesh->mNumVertices]; // 2 floats per vertex

        if (mesh->HasTextureCoords(0)) {
            // we use 2D textures with 2 coordinates and ignore the third coordinate
            float* currentTextureCoord = textureCoords;
            for (unsigned int idx = 0; idx < mesh->mNumVertices; idx++) {
                aiVector3D vect        = (mesh->mTextureCoords[0])[idx];
                *currentTextureCoord++ = vect.x;
                *currentTextureCoord++ = vect.y;
            }
        }

        // copy all mesh faces into one big array (assimp supports faces with ordinary
        // number of vertices, we use only 3 -> triangles)
        // TODO replace this with std::vector
        unsigned int* indices = new unsigned int[mesh->mNumFaces * 3];
        for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
            indices[f * 3 + 0] = mesh->mFaces[f].mIndices[0];
            indices[f * 3 + 1] = mesh->mFaces[f].mIndices[1];
            indices[f * 3 + 2] = mesh->mFaces[f].mIndices[2];
        }

        const aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
        aiColor4D         color;

        if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &color) != AI_SUCCESS)
            color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
        const glm::vec3 ambientColor(color.r, color.g, color.b);

        if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color) != AI_SUCCESS)
            color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
        const glm::vec3               diffuseColor(color.r, color.g, color.b);

        std::shared_ptr<VertexArray>  va = std::make_shared<VertexArray>();
        std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(mesh->mNumVertices * (3 + 3 + 2) * sizeof(float)); // Vertex, normal, uv

        vb->AddData(mesh->mVertices, 3 * mesh->mNumVertices * static_cast<unsigned int>(sizeof(float)));
        vb->AddData(mesh->mNormals, 3 * mesh->mNumVertices * static_cast<unsigned int>(sizeof(float)));
        vb->AddData(textureCoords, 2 * mesh->mNumVertices * static_cast<unsigned int>(sizeof(float)));

        VertexBufferLayout layout;
        layout.PushFloat(3, mesh->mNumVertices);
        layout.PushFloat(3, mesh->mNumVertices);
        layout.PushFloat(2, mesh->mNumVertices);
        va->SetBuffer(vb, layout, mesh->mNumVertices);

        std::shared_ptr<IndexBuffer> ib = std::make_shared<IndexBuffer>(indices, mesh->mNumFaces * 3);

        // Image
        std::filesystem::path filenamePath = filename;
        std::filesystem::path directory    = filenamePath.parent_path();
        aiString              diffuseTexturePath;
        if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &diffuseTexturePath) != aiReturn_SUCCESS) {
            std::cerr << "Could not get texture from the object" << std::endl;
            throw "Could not get texture from the object";
        }

        delete[] indices;
        delete[] textureCoords;
        importer.FreeScene();

        std::string diffuseTextureFilename = directory.string() + static_cast<char>(std::filesystem::path::preferred_separator) + diffuseTexturePath.C_Str();

        return std::make_shared<Mesh>(va, ib, Material(ambientColor, diffuseColor, LoadTexture(diffuseTextureFilename)));
    }

    std::shared_ptr<Texture> MeshLoader::LoadTexture(const std::string& filename) {
        std::shared_ptr<Texture> libraryTexture = TextureLibrary::GetTexture(filename);
        if (libraryTexture != nullptr)
            return libraryTexture;

        // Opengl has 0,0 at the bottom left corner whereas png at top left -> flip it
        // horizontally
        stbi_set_flip_vertically_on_load(true);

        int                      width, height, nrComponents;
        unsigned char*           data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

        std::shared_ptr<Texture> texture = std::make_shared<Texture>(width, height, nrComponents, data);
        TextureLibrary::AddTexture(filename, texture);

        // Cleanup
        stbi_image_free(data);

        return texture;
    }
} // namespace AVC3T