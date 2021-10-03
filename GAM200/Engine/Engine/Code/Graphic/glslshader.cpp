/* Start Header**********************************************************************************/
/*
@file    GLSLShader.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    23/09/2021
\brief
This file contains definitions of member functions of class GLSLShader.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Graphic/GLSLShader.hpp"

namespace Engine 
{
    GLboolean GLSLShader::FileExists(std::string const& file_name) 
    {
        std::ifstream infile(file_name); return infile.good();
    }

    void GLSLShader::DeleteShaderProgram() 
    {
        if (pgm_handle > 0) 
        {
            glDeleteProgram(pgm_handle);
        }
    }

    GLboolean GLSLShader::CompileLinkValidate(std::vector<std::pair<ShaderType, std::string>> vec) 
    {
        for (auto& elem : vec) 
        {
            if (GL_FALSE == CompileShaderFromFile(elem.first, elem.second.c_str())) 
            {
                return GL_FALSE;
            }
        }
        if (GL_FALSE == Link()) 
        {
            return GL_FALSE;
        }
        if (GL_FALSE == Validate()) 
        {
            return GL_FALSE;
        }

        return GL_TRUE;
    }

    GLboolean GLSLShader::CompileShaderFromFile(ShaderType shader_type, const std::string& file_name) 
    {
        if (GL_FALSE == FileExists(file_name))
        {
            log_string = "File not found";
            return GL_FALSE;
        }

        if (pgm_handle <= 0) 
        {
            pgm_handle = glCreateProgram();
            if (0 == pgm_handle) 
            {
                log_string = "Cannot create program handle";
                return GL_FALSE;
            }
        }

        std::ifstream shader_file(file_name, std::ifstream::in);
        if (!shader_file) 
        {
            log_string = "Error opening file " + file_name;
            return GL_FALSE;
        }

        std::stringstream buffer;
        buffer << shader_file.rdbuf();
        shader_file.close();
        return CompileShaderFromString(shader_type, buffer.str());
    }

    GLboolean GLSLShader::CompileShaderFromString(ShaderType shader_type, const std::string& shader_src) 
    {
        if (pgm_handle <= 0)
        {
            pgm_handle = glCreateProgram();
            if (0 == pgm_handle) 
            {
                log_string = "Cannot create program handle";
                return GL_FALSE;
            }
        }

        GLuint shader_handle = 0;
        switch (shader_type) 
        {
        case ShaderType::VERTEX_SHADER: shader_handle = glCreateShader(GL_VERTEX_SHADER); break;
        case ShaderType::FRAGMENT_SHADER: shader_handle = glCreateShader(GL_FRAGMENT_SHADER); break;
        default:
            log_string = "Incorrect shader type";
            return GL_FALSE;
        }

        // load shader source code into shader object
        GLchar const* shader_code[] = { shader_src.c_str() };
        glShaderSource(shader_handle, 1, shader_code, NULL);

        // compile the shader
        glCompileShader(shader_handle);

        // check compilation status
        GLint comp_result;
        glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &comp_result);

        if (GL_FALSE == comp_result) 
        {
            log_string = "Vertex shader compilation failed\n";
            GLint log_len;
            glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &log_len);
            if (log_len > 0) 
            {
                GLchar* log = new GLchar[log_len];
                GLsizei written_log_len;
                glGetShaderInfoLog(shader_handle, log_len, &written_log_len, log);
                log_string += log;
                delete[] log;
            }
            return GL_FALSE;
        }
        else 
        { // attach the shader to the program object
            glAttachShader(pgm_handle, shader_handle);
            return GL_TRUE;
        }
    }

    GLboolean GLSLShader::Link() 
    {
        if (GL_TRUE == is_linked) 
        {
            return GL_TRUE;
        }

        if (pgm_handle <= 0) 
        {
            return GL_FALSE;
        }

        glLinkProgram(pgm_handle); // link the various compiled shaders

        // verify the link status
        GLint lnk_status;
        glGetProgramiv(pgm_handle, GL_LINK_STATUS, &lnk_status);
        if (GL_FALSE == lnk_status) 
        {
            log_string = "Failed to link shader program\n";
            GLint log_len;
            glGetProgramiv(pgm_handle, GL_INFO_LOG_LENGTH, &log_len);

            if (log_len > 0) 
            {
                GLchar* log_str = new GLchar[log_len];
                GLsizei written_log_len;
                glGetProgramInfoLog(pgm_handle, log_len, &written_log_len, log_str);
                log_string += log_str;
                delete[] log_str;
            }
            return GL_FALSE;
        }
        return is_linked = GL_TRUE;
    }

    void GLSLShader::Use() 
    {
        if (pgm_handle > 0 && is_linked == GL_TRUE) 
        {
            glUseProgram(pgm_handle);
        }
    }

    void GLSLShader::UnUse() 
    {
        glUseProgram(0);
    }

    GLboolean GLSLShader::Validate() 
    {
        if (pgm_handle <= 0 || is_linked == GL_FALSE) 
        {
            return GL_FALSE;
        }

        glValidateProgram(pgm_handle);

        GLint status;
        glGetProgramiv(pgm_handle, GL_VALIDATE_STATUS, &status);
        if (GL_FALSE == status) 
        {
            log_string = "Failed to validate shader program for current OpenGL context\n";
            GLint log_len;
            glGetProgramiv(pgm_handle, GL_INFO_LOG_LENGTH, &log_len);
            if (log_len > 0) 
            {
                GLchar* log_str = new GLchar[log_len];
                GLsizei written_log_len;
                glGetProgramInfoLog(pgm_handle, log_len, &written_log_len, log_str);
                log_string += log_str;
                delete[] log_str;
            }
            return GL_FALSE;
        }
        else 
        {
            return GL_TRUE;
        }
    }

    GLuint GLSLShader::GetHandle() const 
    {
        return pgm_handle;
    }

    GLboolean GLSLShader::IsLinked() const 
    {
        return is_linked;
    }

    std::string GLSLShader::GetLog() const 
    {
        return log_string;
    }

    void GLSLShader::SetUniform(GLchar const* name, GLboolean val, GLuint prgm_handle) 
    {
        GLint loc = glGetUniformLocation(prgm_handle, name);
        if (loc >= 0) 
        {
            glUniform1i(loc, val);
        }
        else 
        {
            std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
        }
    }

    void GLSLShader::SetUniform(GLchar const* name, GLint val, GLuint prgm_handle) 
    {
        GLint loc = glGetUniformLocation(prgm_handle, name);
        if (loc >= 0)
        {
            glUniform1i(loc, val);
        }
        else
        {
            std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
        }
    }

    void GLSLShader::SetUniform(GLchar const* name, GLfloat val, GLuint prgm_handle) 
    {
        GLint loc = glGetUniformLocation(prgm_handle, name);
        if (loc >= 0) 
        {
            glUniform1f(loc, val);
        }
        else 
        {
            std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
        }
    }

    void GLSLShader::SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLuint prgm_handle) 
    {
        GLint loc = glGetUniformLocation(prgm_handle, name);
        if (loc >= 0) 
        {
            glUniform2f(loc, x, y);
        }
        else 
        {
            std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
        }
    }

    void GLSLShader::SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLfloat z, GLuint prgm_handle) 
    {
        GLint loc = glGetUniformLocation(prgm_handle, name);
        if (loc >= 0) 
        {
            glUniform3f(loc, x, y, z);
        }
        else 
        {
            std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
        }
    }

    void GLSLShader::SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLuint prgm_handle) 
    {
        GLint loc = glGetUniformLocation(prgm_handle, name);
        if (loc >= 0) 
        {
            glUniform4f(loc, x, y, z, w);
        }
        else 
        {
            std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
        }
    }

    void GLSLShader::SetUniform(GLchar const* name, Math::vec2 const& val, GLuint prgm_handle) 
    {
        GLint loc = glGetUniformLocation(prgm_handle, name);
        if (loc >= 0) 
        {
            glUniform2f(loc, val.x, val.y);
        }
        else 
        {
            std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
        }
    }

    void GLSLShader::SetUniform(GLchar const* name, Math::vec3 const& val, GLuint prgm_handle)
    {
        GLint loc = glGetUniformLocation(prgm_handle, name);
        if (loc >= 0)
        {
            glUniform3f(loc, val.x, val.y, val.z);
        }
        else 
        {
            std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
        }
    }

    // no vec4 currently
    /*
    void GLSLShader::SetUniform(GLchar const *name, Math::vec4 const& val, GLuint prgm_handle) {
      GLint loc = glGetUniformLocation(prgm_handle, name);
      if (loc >= 0) {
        glUniform4f(loc, val.x, val.y, val.z, val.w);
      }
      else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
      }
    }
    */

    void GLSLShader::SetUniform(GLchar const* name, Math::mat3 const& val, GLuint prgm_handle) {
        GLint loc = glGetUniformLocation(prgm_handle, name);
        if (loc >= 0)
        {
            glUniformMatrix3fv(loc, 1, GL_FALSE, Math::value_ptr(val));
        }
        else 
        {
            std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
        }
    }

    void GLSLShader::SetUniform(GLchar const *name, Math::mat4 const& val, GLuint prgm_handle) 
    {
      GLint loc = glGetUniformLocation(prgm_handle, name);
      if (loc >= 0) 
      {
        glUniformMatrix3fv(loc, 1, GL_FALSE, Math::value_ptr(val));
      }
      else 
      {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
      }
    }


    /*

    GLint GLSLShader::GetUniformLocation(GLchar const* name) {
        return glGetUniformLocation(pgm_handle, name);
    }
    void GLSLShader::BindAttribLocation(GLuint index, GLchar const* name) {
        glBindAttribLocation(pgm_handle, index, name);
    }

    void GLSLShader::BindFragDataLocation(GLuint color_number, GLchar const* name) {
        glBindFragDataLocation(pgm_handle, color_number, name);
    }
    */
}