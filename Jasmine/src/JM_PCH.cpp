#include "JM_PCH.h"

void ReadFile(std::string& dr, const char* path)
{
    FILE* fp = nullptr;
    fopen_s(&fp, path, "r");

    if (fp != nullptr) {

        fseek(fp, 0, SEEK_END);
        int fileCount = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        dr.resize(fileCount+1);
        auto charCount = fread(dr.data(), sizeof(char), fileCount, fp);
        dr[charCount] = '\0';

        fclose(fp);
    }
}

std::string ReadFile(const char* path)
{
    std::string dr;
    ReadFile(dr, path);
    return dr;
}

void GetValue(std::string& value, const char* key, const char* src)
{
    auto* fi = strstr(src, key);
    if (fi) {
        fi += strlen(key);
        std::string_view vi = fi;
        auto begin = vi.find_first_not_of(" ");
        value = vi.substr(begin, vi.find_first_of("\n") - begin);
    }
    else
    {
        value.clear();
    }
}

std::string GetValue(const char* key, const char* src)
{
    std::string value;
    GetValue(value, key, src);
    return value;
}
