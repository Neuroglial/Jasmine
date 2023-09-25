#include "JM_PCH.h"

char* ReadFile(const char* path)
{
    char* _string = nullptr;

    FILE* fp = nullptr;
    fopen_s(&fp, path, "r");

    if (fp != nullptr) {

        fseek(fp, 0, SEEK_END);
        long fileCount = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        _string = new char[fileCount + 1];
        _string[fileCount] = '\0';
        auto charCount = fread(_string, sizeof(char), fileCount, fp);
        _string[charCount] = '\0';

        fclose(fp);
    }

    return _string;
}