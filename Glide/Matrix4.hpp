#pragma once

#include "glm/matrix.hpp"

namespace gl
{
const glm::vec3 & GetPosition(const glm::mat4 & mat);
const glm::vec3 & GetForward(const glm::mat4 & mat);
const glm::vec3 & GetUp(const glm::mat4 & mat);
const glm::vec3 & GetRight(const glm::mat4 & mat);
}