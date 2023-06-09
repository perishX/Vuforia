#ifndef VUFORIA_AXIS_H
#define VUFORIA_AXIS_H

#include <string>

#include <GLES3/gl31.h>
#include <GLES2/gl2ext.h>

#include <VuforiaEngine/VuforiaEngine.h>

#include <vector>

class VuforiaAxis {
private:
    GLuint mVertexColorShaderProgramID = 0;
    GLint mVertexColorVertexPositionHandle = 0;
    GLint mVertexColorColorHandle = 0;
    GLint mVertexColorMvpMatrixHandle = 0;
public:
    VuforiaAxis();
    ~VuforiaAxis();
    bool init();
    void render(const VuMatrix44F& projectionMatrix, const VuMatrix44F& modelViewMatrix, const VuVector3F& scale, float lineWidth);

};


#endif //VUFORIA_AXIS_H
