#pragma once
#pragma once
#include <string>

class TransformInterface {
public:
    virtual void convert(const std::string& inputFile, const std::string& outputFile) = 0;
};