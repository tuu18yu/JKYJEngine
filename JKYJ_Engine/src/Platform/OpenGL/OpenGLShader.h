#pragma once

#include "../../Renderer/Shader.h"

namespace JKYJ
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader() {}

		const std::string& GetName() const { return m_name; }

		void Bind() const override;
		void Unbind() const override;
	private:
		std::string m_name;
	};
}