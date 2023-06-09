#include "VuforiaModelTarget.h"
#include "GLUtils.h"
#include "Shaders.h"
#include "Models.h"

VuforiaModelTarget::VuforiaModelTarget() {}

VuforiaModelTarget::~VuforiaModelTarget() {}

bool VuforiaModelTarget::init(AAssetManager* assetManager,std::string path) {
    vuforiaModel.init(assetManager,path);
    vuforiaAxis.init();

    mModelTargetGuideViewTextureUnit = -1;
    return true;
}

void VuforiaModelTarget::renderModelTargetGuideView(VuMatrix44F& projectionMatrix, VuMatrix44F& modelViewMatrix, const VuImageInfo& image,
                                VuBool guideViewImageHasChanged) {
    VuMatrix44F modelViewProjectionMatrix = vuMatrix44FMultiplyMatrix(projectionMatrix, modelViewMatrix);


    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE0);

    // The guide view image is updated if the device orientation changes.
    // This is indicated by the guideViewImageHasChanged flag. In that case,
    // recreate the texture with the latest content of the image.
    if (mModelTargetGuideViewTextureUnit == -1 || guideViewImageHasChanged == VU_TRUE)
    {
        // Free the previous texture
        if (mModelTargetGuideViewTextureUnit != -1)
        {
            GLUtils::destroyTexture(mModelTargetGuideViewTextureUnit);
        }

        mModelTargetGuideViewTextureUnit = GLUtils::createTexture(image);
    }
    glBindTexture(GL_TEXTURE_2D, mModelTargetGuideViewTextureUnit);

    glEnableVertexAttribArray(vuforiaModel.mTextureUniformColorVertexPositionHandle);
    glVertexAttribPointer(vuforiaModel.mTextureUniformColorVertexPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)&squareVertices[0]);

    glEnableVertexAttribArray(vuforiaModel.mTextureUniformColorTextureCoordHandle);
    glVertexAttribPointer(vuforiaModel.mTextureUniformColorTextureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)&squareTexCoords[0]);

    glUseProgram(vuforiaModel.mTextureUniformColorShaderProgramID);
    glUniformMatrix4fv(vuforiaModel.mTextureUniformColorMvpMatrixHandle, 1, GL_FALSE, (GLfloat*)modelViewProjectionMatrix.data);
    glUniform4f(vuforiaModel.mTextureUniformColorColorHandle, 1.0f, 1.0f, 1.0f, 0.7f);
    glUniform1i(vuforiaModel.mTextureUniformColorTexSampler2DHandle, 0); // texture unit, not handle

    // Draw
    glDrawElements(GL_TRIANGLES, NUM_SQUARE_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*)&squareIndices[0]);

    // disable input data structures
    glDisableVertexAttribArray(vuforiaModel.mTextureUniformColorTextureCoordHandle);
    glDisableVertexAttribArray(vuforiaModel.mTextureUniformColorVertexPositionHandle);
    glUseProgram(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLUtils::checkGlError("Render guide view");

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void VuforiaModelTarget::renderModelTarget(VuMatrix44F& projectionMatrix, VuMatrix44F& modelViewMatrix){
    vuforiaModel.render(projectionMatrix,modelViewMatrix);
    VuVector3F axis10cmSize{ 0.1f, 0.1f, 0.1f };
    vuforiaAxis.render(projectionMatrix, modelViewMatrix, axis10cmSize, 4.0f);
}

void VuforiaModelTarget::setTexture(int width, int height, unsigned char *bytes) {
    vuforiaModel.setTexture(width,height,bytes);
}