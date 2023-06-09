//
// Created by 73965 on 2023/6/9.
//

#ifndef GLUTILS_H
#define GLUTILS_H

#include <Log.h>
#include <VuforiaEngine/VuforiaEngine.h>

#include <GLES3/gl31.h>
#include <vector>

class GLUtils {
private:
    /// Enable this flag to debug OpenGL errors
    static const bool DEBUG_GL = false;

public:
    /// Prints GL error information.
    static void checkGlError(const char* operation);

    /// Initialize a shader.
    static GLuint initShader(GLenum shaderType, const char* source);

    /// Create a shader program.
    static GLuint createProgramFromBuffer(const char* vertexShaderBuffer, const char* fragmentShaderBuffer);

    /// Create a texture from a Vuforia Image
    static GLuint createTexture(const VuImageInfo& image);

    /// Create a texture from a byte vector
    static unsigned int createTexture(int width, int height, unsigned char* data, GLenum format = GL_RGBA);

    /// Clean up texture
    static bool destroyTexture(GLuint textureId);
};


#endif //GLUTILS_H
