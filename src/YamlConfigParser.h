#pragma once
#include "IConfigParser.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <string>

class YamlConfigParser : public IConfigParser {
    YAML::Node node;
public:
    bool load(const std::string& filename) override;
    std::string get(const std::string& key) const override;
    void set(const std::string& key, const std::string& value) override;
    bool save(const std::string& filename) const override;
};