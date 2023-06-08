#ifndef VUFORIA_IMAGE_TARGET_H
#define VUFORIA_IMAGE_TARGET_H

#include <string>

class VuforiaImageTarget{
private:
    std::string targetPath{};
    std::string vertexShaderPath{};
    std::string fragmentShaderPath{};
    std::string modelPath{};

    GLuint mUniformColorShaderProgramID = 0;
    GLint mUniformColorVertexPositionHandle = 0;
    GLint mUniformColorMvpMatrixHandle = 0;
    GLint mUniformColorColorHandle = 0;
public:
    bool renderTarget();
};

#endif