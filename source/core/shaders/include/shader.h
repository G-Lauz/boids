#ifndef SHADER_H
#define SHADER_H

#include "glwrapper.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        GLuint id;

        Shader(const char* vertex_path, const char* fragment_path);
        ~Shader();

        void use();
};

#endif // SHADER_H
