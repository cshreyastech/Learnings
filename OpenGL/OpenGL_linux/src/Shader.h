#ifndef _SHADER_
#define _SHADER_

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

struct ShaderProgramSource
{
  std::string VertexSource;
  std::string FragmentSource;
};


class Shader
{
private:
  std::string m_FilePath;
  unsigned int m_RendererID;
  // caching for uniforms
public:
  Shader(const std::string& filepath);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  // Set uniforms
  void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
  unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
  unsigned int CompileShader(unsigned int type, const std::string& source);
  unsigned int GetUniformLocation(const std::string& name);
  ShaderProgramSource ParseShader(const std::string& filepath);
};
#endif