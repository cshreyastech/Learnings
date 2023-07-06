#include "Shader.h"
#include "Renderer.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_Renderer_ID(0)
{
  ShaderProgramSource source = ParseShader(filepath);
  m_Renderer_ID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
  GLCall(glDeleteProgram(m_Renderer_ID));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
  std::ifstream stream(filepath);

  enum class ShaderType
  {
    NONE = -1, VERTEX = 0, FRAGMENT = 1
  };

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;

  while (getline(stream, line))
  {
    if (line.find("#shader") != std::string::npos)
    {
      if (line.find("vertex") != std::string::npos)
        type = ShaderType::VERTEX;
      else if (line.find("fragment") != std::string::npos)
        type = ShaderType::FRAGMENT;
    }
    else
      ss[(int)type] << line << '\n';
  }

  return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
  GLCall(unsigned int id = glCreateShader(type));
  const char* src = source.c_str();
  GLCall(glShaderSource(id, 1, &src, nullptr));
  GLCall(glCompileShader(id));

  int result;
  GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
  if (result == GL_FALSE)
  {
    int length;
    GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    // Stack side allocation of dynamic memory
    char* message = (char*)alloca(length * sizeof(char));
    GLCall(glGetShaderInfoLog(id, length, &length, message));
    ML_LOG_TAG(Error, APP_TAG, "Failed to compile %s shader!", 
      (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));

    GLCall(glDeleteShader(id));
    return 0;

  }
  return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
  GLCall(unsigned int program = glCreateProgram());
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  GLCall(glAttachShader(program, vs));
  GLCall(glAttachShader(program, fs));
  GLCall(glLinkProgram(program));
  GLCall(glValidateProgram(program));

  GLCall(glDeleteShader(vs));
  GLCall(glDeleteShader(fs));

  return program;
}


void Shader::Bind() const
{
  GLCall(glUseProgram(m_Renderer_ID));
}

void Shader::Unbind() const
{
  GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
  ML_LOG_TAG(Info, APP_TAG, "SetUniform1i: %s", name.c_str());

  GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
  // ML_LOG_TAG(Info, APP_TAG, "SetUniform1f: %s", name.c_str());
  GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
  // ML_LOG_TAG(Info, APP_TAG, "SetUniform4f: %s", name.c_str());
  GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
  // ML_LOG_TAG(Info, APP_TAG, "SetUniformMat4f: %s", name.c_str());
  GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    return m_UniformLocationCache[name];

  GLCall(int location = glGetUniformLocation(m_Renderer_ID, name.c_str()));
  if (location == -1)
    // std::cout << "Warning: uniform '" << name << "' doesn't exit!" << std::endl;
    ML_LOG_TAG(Info, APP_TAG, "Warning: uniform %s doesn't exit!", name.c_str());
 
    m_UniformLocationCache[name] = location;
	return location;
}

