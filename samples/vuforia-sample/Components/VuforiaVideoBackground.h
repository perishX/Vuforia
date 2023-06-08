#ifndef VUFORIA_VIDEO_BACKGROUND_H
#define VUFORIA_VIDEO_BACKGROUND_H

#include <string>

#include <GLES3/gl31.h>
#include <GLES2/gl2ext.h>

class VuforiaVideoBackground
{
private:
    std::string targetPath{};
    std::string vertexShaderPath{};
    std::string fragmentShaderPath{};
    std::string modelPath{};

    GLuint mVbShaderProgramID = 0;
    GLint mVbVertexPositionHandle = 0;
    GLint mVbTextureCoordHandle = 0;
    GLint mVbMvpMatrixHandle = 0;
    GLint mVbTexSampler2DHandle = 0;

public:
    bool render();
};

#endif