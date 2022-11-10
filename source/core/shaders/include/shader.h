#ifndef SHADER_H
#define SHADER_H

#include "glwrapper.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace boids 
{
    class Shader
    {
        public:
            GLuint id;

            Shader(const char* vertex_path, const char* fragment_path);
            ~Shader();

            void use();

            void set_mat_4(const std::string &name, const GLfloat* mat) const;
    };
}

#endif // SHADER_H
