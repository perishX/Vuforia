#ifndef VUFORIA_MODEL_TARGET_H
#define VUFORIA_MODEL_TARGET_H

#include <string>

#include <GLES3/gl31.h>
#include <GLES2/gl2ext.h>

#include <VuforiaEngine/VuforiaEngine.h>

#include <vector>

#include "VuforiaModel.h"
#include "VuforiaAxis.h"

class VuforiaModelTarget{
private:
    GLuint mModelTargetGuideViewTextureUnit = -1;
    VuforiaModel vuforiaModel;
    VuforiaAxis vuforiaAxis;
public:
    VuforiaModelTarget();
    ~VuforiaModelTarget();
    bool init(AAssetManager* assetManager,std::string path);
    void renderModelTargetGuideView(VuMatrix44F& projectionMatrix, VuMatrix44F& modelViewMatrix, const VuImageInfo& image,
                VuBool guideViewImageHasChanged);
    void renderModelTarget(VuMatrix44F& projectionMatrix, VuMatrix44F& modelViewMatrix);
    void setTexture(int width, int height, unsigned char* bytes);
};

#endif