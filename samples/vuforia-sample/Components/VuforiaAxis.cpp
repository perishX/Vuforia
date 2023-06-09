#include "VuforiaAxis.h"
#include "GLUtils.h"
#include "Shaders.h"
#include "Models.h"

VuforiaAxis::VuforiaAxis() {}

VuforiaAxis::~VuforiaAxis() {}

bool VuforiaAxis::init() {
    mVertexColorShaderProgramID = GLUtils::createProgramFromBuffer(vertexColorVertexShaderSrc, vertexColorFragmentShaderSrc);
    mVertexColorVertexPositionHandle = glGetAttribLocation(mVertexColorShaderProgramID, "vertexPosition");
    mVertexColorColorHandle = glGetAttribLocation(mVertexColorShaderProgramID, "vertexColor");
    mVertexColorMvpMatrixHandle = glGetUniformLocation(mVertexColorShaderProgramID, "modelViewProjectionMatrix");

    return true;
}

void VuforiaAxis::render(const VuMatrix44F& projectionMatrix, const VuMatrix44F& modelViewMatrix, const VuVector3F& scale, float lineWidth) {
    VuMatrix44F scaledModelViewMatrix;
    VuMatrix44F modelViewProjectionMatrix;

    scaledModelViewMatrix = vuMatrix44FScale(scale, modelViewMatrix);
    modelViewProjectionMatrix = vuMatrix44FMultiplyMatrix(projectionMatrix, scaledModelViewMatrix);

    ///////////////////////////////////////////////////////
    // Render with vertex color shader
    glEnable(GL_DEPTH_TEST);
    glUseProgram(mVertexColorShaderProgramID);

    glEnableVertexAttribArray(mVertexColorVertexPositionHandle);
    glVertexAttribPointer(mVertexColorVertexPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)&axisVertices[0]);

    glEnableVertexAttribArray(mVertexColorColorHandle);
    glVertexAttribPointer(mVertexColorColorHandle, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)&axisColors[0]);

    glUniformMatrix4fv(mVertexColorMvpMatrixHandle, 1, GL_FALSE, (GLfloat*)modelViewProjectionMatrix.data);

    // Draw
    float stateLineWidth;
    glGetFloatv(GL_LINE_WIDTH, &stateLineWidth);

    glLineWidth(lineWidth);

    glDrawElements(GL_LINES, NUM_AXIS_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*)&axisIndices[0]);

    // disable input data structures
    glDisableVertexAttribArray(mVertexColorVertexPositionHandle);
    glDisableVertexAttribArray(mVertexColorColorHandle);
    glUseProgram(0);
    glDisable(GL_DEPTH_TEST);

    glLineWidth(stateLineWidth);

    GLUtils::checkGlError("Render axis");
}