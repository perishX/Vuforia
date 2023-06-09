#ifndef VUFORIA_VIDEO_BACKGROUND_H
#define VUFORIA_VIDEO_BACKGROUND_H

#include <string>

#include <GLES3/gl31.h>
#include <GLES2/gl2ext.h>

#include <VuforiaEngine/VuforiaEngine.h>

#include <vector>

class VuforiaVideoBackground
{
private:
    std::string vertexShaderPath{};
    std::string fragmentShaderPath{};

    GLuint mVbShaderProgramID = 0;
    GLint mVbVertexPositionHandle = 0;
    GLint mVbTextureCoordHandle = 0;
    GLint mVbMvpMatrixHandle = 0;
    GLint mVbTexSampler2DHandle = 0;
public:
    VuforiaVideoBackground();
    ~VuforiaVideoBackground();
    bool init();
    void render(const VuMatrix44F& projectionMatrix, const float* vertices, const float* textureCoordinates,
                const int numTriangles, const unsigned int* indices, int textureUnit);
};

#endif