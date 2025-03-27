#include "Shader.h"
#include "../../src/Platform/OpenGL/OpenGLShader.h"

namespace JKYJ
{
	std::unique_ptr<Shader> Shader::Create(const std::string& name, const std::string& filepath)
	{
		 return std::make_unique<OpenGLShader>(name, filepath);
	}

	std::unique_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		return std::make_unique<OpenGLShader>(name, vertexSrc, fragmentSrc);
	}

	void ShaderLibrary::Add(const std::string& name,std::unique_ptr<Shader>& shader)
	{
		m_Shaders[name] = std::move(shader);
	}

	void ShaderLibrary::Add(std::unique_ptr<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	std::unique_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(name, filepath);
		Add(name, shader);
		return shader;
	}

	Shader& ShaderLibrary::Get(const std::string& name)
	{
		return *m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}