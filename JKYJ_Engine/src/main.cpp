#include "Core/Window.h"
#include "Renderer/Shader.h"

#include <iostream>

int main(void)
{
	std::unique_ptr<JKYJ::Window> window = JKYJ::Window::Create();

	JKYJ::ShaderLibrary lib;
	lib.Load("basic", "./res/shaders/Basic.shader");

    window->SetEventCallback([](JKYJ::Event& e)
	{
		std::cout << e.ToString();
	});
	window->OnUpdate();
}