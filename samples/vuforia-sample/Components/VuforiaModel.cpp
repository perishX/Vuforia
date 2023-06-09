//
// Created by 73965 on 2023/6/9.
//

#include <MemoryStream.h>
#include "VuforiaModel.h"
#include "GLUtils.h"
#include "Shaders.h"
#include "Models.h"
#include "tiny_obj_loader.h"

VuforiaModel::VuforiaModel() {}

VuforiaModel::~VuforiaModel() {}

bool VuforiaModel::init(AAssetManager* assetManager,std::string path) {
    mTextureUniformColorShaderProgramID = GLUtils::createProgramFromBuffer(textureColorVertexShaderSrc, textureColorFragmentShaderSrc);
    mTextureUniformColorVertexPositionHandle = glGetAttribLocation(mTextureUniformColorShaderProgramID, "vertexPosition");
    mTextureUniformColorTextureCoordHandle = glGetAttribLocation(mTextureUniformColorShaderProgramID, "vertexTextureCoord");
    mTextureUniformColorMvpMatrixHandle = glGetUniformLocation(mTextureUniformColorShaderProgramID, "modelViewProjectionMatrix");
    mTextureUniformColorTexSampler2DHandle = glGetUniformLocation(mTextureUniformColorShaderProgramID, "texSampler2D");
    mTextureUniformColorColorHandle = glGetUniformLocation(mTextureUniformColorShaderProgramID, "uniformColor");

    std::vector<char> data; // for reading model files

    modelPath=path;
    // Load model
    {
//        if (!readAsset(assetManager, "Astronaut.obj", data))
        if (!readAsset(assetManager, modelPath.c_str(), data))
        {
            return false;
        }
        if (!loadObjModel(data, mVertexCount, mVertices, mTexCoords))
        {
            return false;
        }
        data.clear();
        mTextureUnit = -1;
    }
    return true;
}

void VuforiaModel::render(VuMatrix44F& projectionMatrix, VuMatrix44F& modelViewMatrix) {
    VuMatrix44F modelViewProjectionMatrix = vuMatrix44FMultiplyMatrix(projectionMatrix, modelViewMatrix);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(mTextureUniformColorShaderProgramID);

    glEnableVertexAttribArray(mTextureUniformColorVertexPositionHandle);
    glVertexAttribPointer(mTextureUniformColorVertexPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)mVertices.data());

    glEnableVertexAttribArray(mTextureUniformColorTextureCoordHandle);
    glVertexAttribPointer(mTextureUniformColorTextureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)mTexCoords.data());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureUnit);

    glUniformMatrix4fv(mTextureUniformColorMvpMatrixHandle, 1, GL_FALSE, (GLfloat*)modelViewProjectionMatrix.data);
    glUniform4f(mTextureUniformColorColorHandle, 1.0f, 1.0f, 1.0f, 1.0f);
    glUniform1i(mTextureUniformColorTexSampler2DHandle, 0); // texture unit, not handle

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, mVertexCount);

    // disable input data structures
    glDisableVertexAttribArray(mTextureUniformColorTextureCoordHandle);
    glDisableVertexAttribArray(mTextureUniformColorVertexPositionHandle);
    glUseProgram(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLUtils::checkGlError("Render model");

    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}

void VuforiaModel::setTexture(int width, int height, unsigned char *bytes) {
    if (mTextureUnit != -1)
    {
        GLUtils::destroyTexture(mTextureUnit);
        mTextureUnit = -1;
    }
    mTextureUnit = GLUtils::createTexture(width, height, bytes);
}

bool VuforiaModel::readAsset(AAssetManager *assetManager, const char *filename,
                             std::vector<char> &data) {
    LOG("Reading asset %s", filename);
    AAsset* asset = AAssetManager_open(assetManager, filename, AASSET_MODE_STREAMING);
    if (asset == nullptr)
    {
        LOG("Error opening asset file %s", filename);
        return false;
    }
    auto assetSize = AAsset_getLength(asset);
    data.reserve(assetSize);
    char buf[BUFSIZ];
    int nb_read = 0;
    while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
    {
        std::copy(&buf[0], &buf[BUFSIZ], std::back_inserter(data));
    }
    AAsset_close(asset);
    if (nb_read < 0)
    {
        LOG("Error reading asset file %s", filename);
        return false;
    }
    return true;
}

bool VuforiaModel::loadObjModel(const std::vector<char> &data, int &numVertices,
                                std::vector<float> &vertices, std::vector<float> &texCoords) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    MemoryInputStream aFileDataStream(data.data(), data.size());
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &aFileDataStream);
    if (!ret || !err.empty())
    {
        LOG("Error loading model (%s)", err.c_str());
        return false;
    }
    if (!warn.empty())
    {
        LOG("Warning loading model (%s)", warn.c_str());
    }

    numVertices = 0;
    vertices.clear();
    texCoords.clear();
    // Loop over shapes
    // s is the index into the shapes vector
    // f is the index of the current face
    // v is the index of the current vertex
    for (size_t s = 0; s < shapes.size(); ++s)
    {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f)
        {
            int fv = shapes[s].mesh.num_face_vertices[f];
            numVertices += fv;

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; ++v)
            {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                vertices.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
                vertices.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
                vertices.push_back(attrib.vertices[3 * idx.vertex_index + 2]);

                // The model may not have texture coordinates for every vertex
                // If a texture coordinate is missing we just set it to 0,0
                // This may not be suitable for rendering some OBJ model files
                if (idx.texcoord_index < 0)
                {
                    texCoords.push_back(0.f);
                    texCoords.push_back(0.f);
                }
                else
                {
                    texCoords.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
                    texCoords.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
                }
            }
            index_offset += fv;
        }
    }
    return true;
}