#ifndef RBSHADER_H
#define RBSHADER_H

#include "core/platform_includes.h"

class Shader {
public:
	Shader() {}
	~Shader() {}

	GLuint GetProgramID() { return _programID; }
	GLuint GetAttributeLocation(std::string name);
	GLuint GetUniformLocation(std::string name);
	
	void Load(const char *vertex_file_path, const char *fragment_file_path);
	
private:
	GLuint _programID;
};

#endif