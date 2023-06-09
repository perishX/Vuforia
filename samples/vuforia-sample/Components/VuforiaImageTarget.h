#ifndef VUFORIA_IMAGE_TARGET_H
#define VUFORIA_IMAGE_TARGET_H

#include <string>

#include <GLES3/gl31.h>
#include <GLES2/gl2ext.h>

#include <VuforiaEngine/VuforiaEngine.h>

#include <vector>

class VuforiaImageTarget{
private:
    std::string targetPath{};
    std::string vertexShaderPath{};
    std::string fragmentShaderPath{};
    std::string modelPath{};

    // For augmentation rendering
    GLuint mUniformColorShaderProgramID = 0;
    GLint mUniformColorVertexPositionHandle = 0;
    GLint mUniformColorMvpMatrixHandle = 0;
    GLint mUniformColorColorHandle = 0;
public:
    VuforiaImageTarget();
    ~VuforiaImageTarget();
    bool init();
    void render(VuMatrix44F& projectionMatrix, VuMatrix44F& modelViewMatrix, VuMatrix44F& scaledModelViewMatrix);
};

#endif