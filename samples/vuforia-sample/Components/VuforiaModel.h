//
// Created by 73965 on 2023/6/9.
//

#ifndef VUFORIA_MODEL_H
#define VUFORIA_MODEL_H

#include <string>

#include <GLES3/gl31.h>
#include <GLES2/gl2ext.h>

#include <VuforiaEngine/VuforiaEngine.h>

#include <vector>
#include <android/asset_manager.h>

class VuforiaModel {
private:
    std::string modelPath{};

    int mVertexCount;
    std::vector<float> mVertices;
    std::vector<float> mTexCoords;
    GLuint mTextureUnit = -1;

    bool readAsset(AAssetManager* assetManager, const char* filename, std::vector<char>& data);
    bool loadObjModel(const std::vector<char>& data, int& numVertices, std::vector<float>& vertices, std::vector<float>& texCoords);
public:
    VuforiaModel();
    ~VuforiaModel();
    bool init(AAssetManager* assetManager,std::string path);
    void render(VuMatrix44F& projectionMatrix, VuMatrix44F& modelViewMatrix);
    void setTexture(int width, int height, unsigned char* bytes);

    GLuint mTextureUniformColorShaderProgramID = 0;
    GLint mTextureUniformColorVertexPositionHandle = 0;
    GLint mTextureUniformColorTextureCoordHandle = 0;
    GLint mTextureUniformColorMvpMatrixHandle = 0;
    GLint mTextureUniformColorTexSampler2DHandle = 0;
    GLint mTextureUniformColorColorHandle = 0;
};


#endif //VUFORIA_MODEL_H
