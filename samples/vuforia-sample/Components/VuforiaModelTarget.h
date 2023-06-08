#ifndef VUFORIA_MODEL_TARGET_H
#define VUFORIA_MODEL_TARGET_H

#include <string>

class VuforiaModelTarget{
private:
    std::string targetPath{};
    std::string vertexShaderPath{};
    std::string fragmentShaderPath{};
    std::string modelPath{};

    GLuint mTextureUniformColorShaderProgramID = 0;
    GLint mTextureUniformColorVertexPositionHandle = 0;
    GLint mTextureUniformColorTextureCoordHandle = 0;
    GLint mTextureUniformColorMvpMatrixHandle = 0;
    GLint mTextureUniformColorTexSampler2DHandle = 0;
    GLint mTextureUniformColorColorHandle = 0;
    GLuint mModelTargetGuideViewTextureUnit = -1;
public:
    bool renderTarget();
};

#endif