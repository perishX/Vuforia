#ifndef VUFORIA_IMAGE_TARGET_H
#define VUFORIA_IMAGE_TARGET_H

#include <string>

#include <GLES3/gl31.h>
#include <GLES2/gl2ext.h>

#include <VuforiaEngine/VuforiaEngine.h>

#include <vector>

#include "VuforiaModel.h"
#include "VuforiaAxis.h"

class VuforiaImageTarget{
private:
    // For augmentation rendering
    GLuint mUniformColorShaderProgramID = 0;
    GLint mUniformColorVertexPositionHandle = 0;
    GLint mUniformColorMvpMatrixHandle = 0;
    GLint mUniformColorColorHandle = 0;

    VuforiaModel vuforiaModel;
    VuforiaAxis vuforiaAxis;
public:
    VuforiaImageTarget();
    ~VuforiaImageTarget();
    bool init(AAssetManager* assetManager,std::string path);
    void render(VuMatrix44F& projectionMatrix, VuMatrix44F& modelViewMatrix, VuMatrix44F& scaledModelViewMatrix);
    void setTexture(int width, int height, unsigned char* bytes);
};

#endif