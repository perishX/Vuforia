//
// Created by 73965 on 2023/6/9.
//

#ifndef VUFORIA_ORIGIN_H
#define VUFORIA_ORIGIN_H

#include <string>

#include <GLES3/gl31.h>
#include <GLES2/gl2ext.h>

#include <VuforiaEngine/VuforiaEngine.h>

#include <vector>

class VuforiaOrigin {
private:
    GLuint mUniformColorShaderProgramID = 0;
    GLint mUniformColorVertexPositionHandle = 0;
    GLint mUniformColorMvpMatrixHandle = 0;
    GLint mUniformColorColorHandle = 0;
public:
    VuforiaOrigin();
    ~VuforiaOrigin();
    bool init();
    void render(const VuMatrix44F& projectionMatrix, const VuMatrix44F& modelViewMatrix, float scale, const VuVector4F& color);
};


#endif //VUFORIA_ORIGIN_H
