#pragma once
#include "IConfigParser.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <string>

class YamlConfigParser : public IConfigParser {
    YAML::Node node;
public:
    bool load(const std::string& filename) override {
        node = YAML::LoadFile(filename);
        return node ? true : false;
    }
    std::string get(const std::string& key) const override {
        if (node[key]) return node[key].as<std::string>();
        return "";
    }
    void set(const std::string& key, const std::string& value) override {
        node[key] = value;
    }
    bool save(const std::string& filename) const override {
        std::ofstream out(filename);
        if (!out) return false;
        out << node;
        return true;
    }
};