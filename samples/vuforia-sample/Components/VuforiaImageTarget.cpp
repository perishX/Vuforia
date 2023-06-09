#include "VuforiaImageTarget.h"
#include "GLUtils.h"
#include "Shaders.h"
#include "Models.h"

VuforiaImageTarget::VuforiaImageTarget() {}

VuforiaImageTarget::~VuforiaImageTarget() {}

bool VuforiaImageTarget::init() {
    // Setup for augmentation rendering
    mUniformColorShaderProgramID = GLUtils::createProgramFromBuffer(uniformColorVertexShaderSrc, uniformColorFragmentShaderSrc);
    mUniformColorVertexPositionHandle = glGetAttribLocation(mUniformColorShaderProgramID, "vertexPosition");
    mUniformColorMvpMatrixHandle = glGetUniformLocation(mUniformColorShaderProgramID, "modelViewProjectionMatrix");
    mUniformColorColorHandle = glGetUniformLocation(mUniformColorShaderProgramID, "uniformColor");

    return true;
}

void VuforiaImageTarget::render(VuMatrix44F& projectionMatrix, VuMatrix44F& modelViewMatrix, VuMatrix44F& scaledModelViewMatrix) {
    VuMatrix44F scaledModelViewProjectionMatrix = vuMatrix44FMultiplyMatrix(projectionMatrix, scaledModelViewMatrix);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float stateLineWidth;
    glGetFloatv(GL_LINE_WIDTH, &stateLineWidth);

    glUseProgram(mUniformColorShaderProgramID);

    glVertexAttribPointer(mUniformColorVertexPositionHandle, 3, GL_FLOAT, GL_TRUE, 0, (const GLvoid*)&squareVertices[0]);

    glEnableVertexAttribArray(mUniformColorVertexPositionHandle);

    glUniformMatrix4fv(mUniformColorMvpMatrixHandle, 1, GL_FALSE, &scaledModelViewProjectionMatrix.data[0]);

    // Draw translucent solid overlay
    // Color RGBA
    glUniform4f(mUniformColorColorHandle, 1.0, 0.0, 0.0, 0.1);
    glDrawElements(GL_TRIANGLES, NUM_SQUARE_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*)&squareIndices[0]);

    // Draw solid outline
    glUniform4f(mUniformColorColorHandle, 1.0, 0.0, 0.0, 1.0);
    glLineWidth(4.0f);
    glDrawElements(GL_LINES, NUM_SQUARE_WIREFRAME_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*)&squareWireframeIndices[0]);

    glDisableVertexAttribArray(mUniformColorVertexPositionHandle);

    GLUtils::checkGlError("Render Image Target");

    glLineWidth(stateLineWidth);

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}
