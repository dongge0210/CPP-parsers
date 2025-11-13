#pragma once
#include "IConfigParser.h" // This should be resolvable by the compiler's include paths
#include "INIReader.h" // inih 库的 C++ 封装
#include <fstream>
#include <string>
#include <map>

class IniConfigParser : public IConfigParser {
    std::map<std::string, std::string> data;
    std::string lastFile;
public:
    bool load(const std::string& filename) override;
    std::string get(const std::string& key) const override;
    void set(const std::string& key, const std::string& value) override;
    bool save(const std::string& filename) const override;
};