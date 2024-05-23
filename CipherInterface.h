#pragma once


class CipherInterface {
public:
    virtual  bool encode(std::string FileName) = 0;
    virtual bool decode(std::string FileName) = 0;
};
