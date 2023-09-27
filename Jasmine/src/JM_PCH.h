#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Jasmine/Core/Log.h"

void ReadFile(std::string& dr, const char* path);
std::string ReadFile(const char* path);

void GetValue(std::string& value, const char* key, const char* src);
std::string GetValue(const char* key, const char* src);

#ifdef JM_PLATFORM_WINDOWS
#include <Windows.h>
#endif