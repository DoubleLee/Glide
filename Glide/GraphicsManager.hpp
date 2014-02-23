#pragma once

#include "BasicTypes.hpp"

struct GLFWwindow;

namespace gl
{

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	Bool WindowOpen() const;
	Void Update();

	GLFWwindow * mpWindow;
};

}