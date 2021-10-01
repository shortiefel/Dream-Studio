/* !
@file    glslshader.h
@author  chiayida98@gmail.com
@date    01/10/2021

This file contains the declaration of class GLSLShader that encapsulates the
functionality required to load shader source; compile shader source; link
shader objects into a program object, validate program object; log msesages
from compiling linking, and validation steps; install program object in
appropriate shaders; and pass uniform variables from the client to the
program object.

*//*__________________________________________________________________________*/

/*                                                                      guard
----------------------------------------------------------------------------- */
#ifndef GLSLSHADER_H
#define GLSLSHADER_H

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Engine/Header/Math/MathLib.hpp"


#include "Engine/Header/pch.hpp"

namespace Engine {
    class GLSLShader {
    public:
        enum class ShaderType {
            VERTEX_SHADER = GL_VERTEX_SHADER,
            FRAGMENT_SHADER = GL_FRAGMENT_SHADER
        };


        // default ctor required to initialize GLSLShader object to safe state
        GLSLShader() : pgm_handle(0), is_linked(GL_FALSE) {
        }

        // This function not only compiles individual shader sources but links
        // multiple shader objects to create an exectuable shader program.
        // For each shader source, the function requires the full path to the file 
        // (containing shader source) and the type of shader program (vertex,
        // fragment, geometry, a tessellation type). This information is combined
        // as an std::pair object and the multiple pairs are supplied in a
        // std::vector object.
        // For each shader file, the function implements the six steps described in T
        // CompileShaderFromFile(). After the shader objects are created, a call to
        // Link() will create a shader executable program. This is followed by a call
        // to Validate() ensuring the program can execute in the current OpenGL state.
        GLboolean CompileLinkValidate(std::vector<std::pair<ShaderType, std::string>>);

        // This function does the following:
        // 1) Create a shader program object if one doesn't exist
        // 2) Using first parameter, create a shader object
        // 3) Load shader source code from file specified by second parameter to
        //    shader object
        // 4) Compile shader source by calling CompileShaderFromString
        // 5) Check compilation status and log any messages to data member 
        //    "log_string"
        // 6) If compilation is successful, attach this shader object to previously
        //    created shader program  object
        GLboolean CompileShaderFromFile(ShaderType shader_type, std::string const& file_name);

        // This function does the following:
        // 1) Create a shader program object if one doesn't exist
        // 2) Using first parameter, create a shader object
        // 3) Load the shader code from 2nd parameter to shader object
        // 4) Compile the shader source
        // 5) Check compilation status and log any messages to data member "log_string"
        // 6) If compilation is successful, attach this shader object to previously
        //    created shader program object ...
        GLboolean CompileShaderFromString(ShaderType shader_type, std::string const& shader_src);

        // Link shader objects attached to handle pgm_handle. This member function
        // will also verify the status of the link operation (successful or not?).
        // If the shader objects did not link into a program object, then the
        // member function must retrieve and write the program object's information
        // log to data member log_string. 
        GLboolean Link();

        // Install the shader program object whose handle is encapsulated
        // by member pgm_handle
        void Use();

        // De-install previously installed shader program object using Use().
        // More correctly, after the execution of this member function, the
        // current rendering state is referring to an invalid program object.
        void UnUse();

        // check whether the executable shader program object can execute given the
        // current OpenGL state ...
        // See the glValidateProgram() reference page for more information
        // The function returns true if validatation succeeded 
        GLboolean Validate();

        // return the handle to the shader program object
        GLuint GetHandle() const;

        // have the different object code linked into a shader program?
        GLboolean IsLinked() const;

        // return logged information from the GLSL compiler and linker and
        // validation information obtained after calling Validate() ...
        std::string GetLog() const;

        // as the name implies, this function deletes a program object
        void DeleteShaderProgram();

        // OpenGL is C-based API and therefore doesn't understand function
        // overloading or templates
        // Therefore, we need a family of functions to specify values of uniform
        // variables of different types for the current program object
        static void SetUniform(GLchar const* name, GLboolean val, GLuint prgm_handle);
        static void SetUniform(GLchar const* name, GLint val, GLuint prgm_handle);
        static void SetUniform(GLchar const* name, GLfloat val, GLuint prgm_handle);
        static void SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLuint prgm_handle);
        static void SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLfloat z, GLuint prgm_handle);
        static void SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLuint prgm_handle);
        static void SetUniform(GLchar const* name, Math::vec2 const& val, GLuint prgm_handle);
        static void SetUniform(GLchar const* name, Math::vec3 const& val, GLuint prgm_handle);
        //void SetUniform(GLchar const *name, Math::vec4 const& val, GLuint prgm_handle);
        static void SetUniform(GLchar const* name, Math::mat3 const& val, GLuint prgm_handle);
        //void SetUniform(GLchar const *name, Math::mat4 const& val, GLuint prgm_handle);



    private:
        GLuint pgm_handle = 0;  // handle to linked shader program object
        GLboolean is_linked = GL_FALSE; // has the program successfully linked?
        std::string log_string; // log for OpenGL compiler and linker messages

        // return true if file (given in relative path) exists, false otherwise
        GLboolean FileExists(std::string const& file_name);
    };
}

#endif /*GLSLSHADER_H */