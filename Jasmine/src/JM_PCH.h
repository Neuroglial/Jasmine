#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Jasmine/Core/Log.h"
#include "Jasmine/Debug/Instrumentor.h"

void ReadFile(std::string& dr, const char* path);
std::string ReadFile(const char* path);

void GetValue(std::string& value, const char* key, const char* src);
std::string GetValue(const char* key, const char* src);

void PrintError(uint32_t error);

#ifdef JM_PLATFORM_WINDOWS
#include <Windows.h>
#endif