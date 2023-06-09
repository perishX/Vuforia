#include "VuforiaVideoBackground.h"
#include "GLUtils.h"
#include "Shaders.h"

VuforiaVideoBackground::VuforiaVideoBackground() {}

VuforiaVideoBackground::~VuforiaVideoBackground() {}

bool VuforiaVideoBackground::init() {
    mVbShaderProgramID = GLUtils::createProgramFromBuffer(textureVertexShaderSrc, textureFragmentShaderSrc);
    mVbVertexPositionHandle = glGetAttribLocation(mVbShaderProgramID, "vertexPosition");
    mVbTextureCoordHandle = glGetAttribLocation(mVbShaderProgramID, "vertexTextureCoord");
    mVbMvpMatrixHandle = glGetUniformLocation(mVbShaderProgramID, "modelViewProjectionMatrix");
    mVbTexSampler2DHandle = glGetUniformLocation(mVbShaderProgramID, "texSampler2D");
    return true;
}

void VuforiaVideoBackground::render(const VuMatrix44F& projectionMatrix, const float* vertices, const float* textureCoordinates,
                                    const int numTriangles, const unsigned int* indices, int textureUnit) {
    GLboolean depthTest = GL_FALSE;
    GLboolean cullTest = GL_FALSE;

    glGetBooleanv(GL_DEPTH_TEST, &depthTest);
    glGetBooleanv(GL_CULL_FACE, &cullTest);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Load the shader and upload the vertex/texcoord/index data
    glUseProgram(mVbShaderProgramID);
    glVertexAttribPointer(static_cast<GLuint>(mVbVertexPositionHandle), 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(static_cast<GLuint>(mVbTextureCoordHandle), 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);

    glUniform1i(mVbTexSampler2DHandle, textureUnit);

    // Render the video background with the custom shader
    // First, we enable the vertex arrays
    glEnableVertexAttribArray(static_cast<GLuint>(mVbVertexPositionHandle));
    glEnableVertexAttribArray(static_cast<GLuint>(mVbTextureCoordHandle));

    // Pass the projection matrix to OpenGL
    glUniformMatrix4fv(mVbMvpMatrixHandle, 1, GL_FALSE, projectionMatrix.data);

    // Then, we issue the render call
    glDrawElements(GL_TRIANGLES, numTriangles * 3, GL_UNSIGNED_INT, indices);
//    glDrawElements(GL_LINEAR, numTriangles * 3, GL_UNSIGNED_INT, indices);
    // Finally, we disable the vertex arrays
    glDisableVertexAttribArray(static_cast<GLuint>(mVbVertexPositionHandle));
    glDisableVertexAttribArray(static_cast<GLuint>(mVbTextureCoordHandle));

    if (depthTest)
        glEnable(GL_DEPTH_TEST);

    if (cullTest)
        glEnable(GL_CULL_FACE);

    GLUtils::checkGlError("Render video background");

}