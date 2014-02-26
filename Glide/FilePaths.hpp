#pragma once

#include <string>

namespace gl
{
std::string StripPath(const std::string & fileNamePath);

extern const std::string gConfigsFolder;
extern const std::string gTexturesFolder;
extern const std::string gScenesFolder;
extern const std::string gShadersFolder;
}