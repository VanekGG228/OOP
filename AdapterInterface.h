#pragma once
#include <string>
class AdapterInterface {
public:
    virtual void convertJsonToXml(const std::string& inputFile, const std::string& outputFile) = 0;
    
    virtual void convertXmlToJson(const std::string& inputFile, const std::string& outputFile) = 0;
    virtual void clear() = 0;
};