#include "OpenGLShader.h"
#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>

namespace JKYJ
{
	namespace Utils 
	{

		struct ShaderProgramSource
		{
			std::string VertexSrc;
			std::string FragmentSrc;
		};

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		static ShaderProgramSource ParseShader(const std::string& filepath)
		{
			std::ifstream stream(filepath);
			std::string line;
			std::stringstream ss[2];

			ShaderType type = ShaderType::NONE;

			while (getline(stream, line))
			{
				if (line.find("shader") != std::string::npos)
				{
					if (line.find("vertex") != std::string::npos)
					{
						type = ShaderType::VERTEX;
					}

					else if (line.find("fragment") != std::string::npos)
					{
						type = ShaderType::FRAGMENT;
					}
				}

				else
				{
					ss[(int) type] << line << "\n";
				}
			}

			return { ss[0].str(), ss[1].str() };
		}

		static unsigned int CompileShader(unsigned int type, const std::string& src)
		{
			unsigned int id = glCreateShader(type);
			const char* source = src.c_str(); // pointer to beginning of data (== &src[0])
			glShaderSource(id, 1, &source, nullptr); // nullptr assume end is nullptr
			glCompileShader(id);

			int result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				int length;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*) alloca(length * sizeof(char));
				glGetShaderInfoLog(id, length, &length, message);
				std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader\n";
				std::cout << message << "\n";

				glDeleteShader(id);
				return 0;
			}

			return id;
		}


		static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragShader)
		{
			unsigned int program = glCreateProgram();
			unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
			unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

			// link to 1 program
			glAttachShader(program, vs);
			glAttachShader(program, fs);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vs);
			glDeleteShader(fs);

			return program;
		}
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& filepath)
	{
		Utils::ShaderProgramSource sources = Utils::ParseShader(filepath);
		//std::cout << sources.VertexSrc << "\n";
		//std::cout << sources.FragmentSrc << "\n";
		m_name = name;
		Utils::CreateShader(sources.VertexSrc, sources.FragmentSrc);
	}
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		m_name = name;
		Utils::CreateShader(vertexSrc, fragmentSrc);
	}

	void OpenGLShader::Bind() const {}
	void OpenGLShader::Unbind() const {}
}