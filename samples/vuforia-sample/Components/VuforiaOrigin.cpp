//
// Created by 73965 on 2023/6/9.
//

#include "VuforiaOrigin.h"
#include "GLUtils.h"
#include "Shaders.h"
#include "Models.h"

VuforiaOrigin::VuforiaOrigin() {}

VuforiaOrigin::~VuforiaOrigin() {}

bool VuforiaOrigin::init() {
    mUniformColorShaderProgramID = GLUtils::createProgramFromBuffer(uniformColorVertexShaderSrc, uniformColorFragmentShaderSrc);
    mUniformColorVertexPositionHandle = glGetAttribLocation(mUniformColorShaderProgramID, "vertexPosition");
    mUniformColorMvpMatrixHandle = glGetUniformLocation(mUniformColorShaderProgramID, "modelViewProjectionMatrix");
    mUniformColorColorHandle = glGetUniformLocation(mUniformColorShaderProgramID, "uniformColor");

    return true;
}

void VuforiaOrigin::render(const VuMatrix44F& projectionMatrix, const VuMatrix44F& modelViewMatrix, float scale, const VuVector4F& color) {
    VuMatrix44F scaledModelViewMatrix;
    VuMatrix44F modelViewProjectionMatrix;
    VuVector3F scaleVec{ scale, scale, scale };

    scaledModelViewMatrix = vuMatrix44FScale(scaleVec, modelViewMatrix);
    modelViewProjectionMatrix = vuMatrix44FMultiplyMatrix(projectionMatrix, scaledModelViewMatrix);

    ///////////////////////////////////////////////////////////////
    // Render with const ambient diffuse light uniform color shader
    glEnable(GL_DEPTH_TEST);
    glUseProgram(mUniformColorShaderProgramID);

    glEnableVertexAttribArray(mUniformColorVertexPositionHandle);

    glVertexAttribPointer(mUniformColorVertexPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)&cubeVertices[0]);

    glUniformMatrix4fv(mUniformColorMvpMatrixHandle, 1, GL_FALSE, (GLfloat*)modelViewProjectionMatrix.data);
    glUniform4f(mUniformColorColorHandle, color.data[0], color.data[1], color.data[2], color.data[3]);

    // Draw
    glDrawElements(GL_TRIANGLES, NUM_CUBE_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*)&cubeIndices[0]);

    // disable input data structures
    glDisableVertexAttribArray(mUniformColorVertexPositionHandle);
    glUseProgram(0);
    glDisable(GL_DEPTH_TEST);

    GLUtils::checkGlError("Render cube");
}
