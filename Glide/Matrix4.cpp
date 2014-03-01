#include "Matrix4.hpp"

namespace gl
{
const glm::vec3 & GetPosition(const glm::mat4 & mat)
	{
	return reinterpret_cast<const glm::vec3&> (mat[3]);
	}

const glm::vec3 & GetForward(const glm::mat4 & mat)
	{
	return reinterpret_cast<const glm::vec3&> (mat[2]);
	}

const glm::vec3 & GetUp(const glm::mat4 & mat)
	{
	return reinterpret_cast<const glm::vec3&> (mat[1]);
	}

const glm::vec3 & GetRight(const glm::mat4 & mat)
	{
	return reinterpret_cast<const glm::vec3&> (mat[0]);
	}
}