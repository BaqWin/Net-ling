#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

std::string createTempFile(const std::vector<std::string>& lines, const std::string& filePath);
