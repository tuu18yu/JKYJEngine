#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

namespace JKYJ
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		static std::unique_ptr<Shader> Create(const std::string& name, const std::string& filepath);
		static std::unique_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, std::unique_ptr<Shader>& shader);
		void Add(std::unique_ptr<Shader>& shader);
		
		std::unique_ptr<Shader> Load(const std::string& name, const std::string& filepath);

		Shader& Get(const std::string& name);

		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, std::unique_ptr<Shader>> m_Shaders;
	};

}