#include "test_utils.hpp"

std::string createTempFile(const std::vector<std::string>& lines, const std::string& filePath)
{
    if (std::filesystem::exists(filePath))
    {
        std::ofstream file(filePath, std::ofstream::trunc);
        for (const std::string& line : lines)
        {
            file << line << std::endl;
        }
        file.close();
    }
    else
    {
        std::ofstream file(filePath, std::ofstream::out);
        for (const std::string& line : lines)
        {
            file << line << std::endl;
        }
        file.close();
    }

    return filePath;
}
