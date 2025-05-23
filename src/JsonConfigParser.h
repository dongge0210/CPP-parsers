#pragma once
#include "IConfigParser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

class JsonConfigParser : public IConfigParser {
    nlohmann::json data;
public:
    bool load(const std::string& filename) override {
        std::ifstream in(filename);
        if (!in) return false;
        in >> data;
        return true;
    }
    std::string get(const std::string& key) const override {
        if (data.contains(key)) return data[key].dump();
        return "";
    }
    void set(const std::string& key, const std::string& value) override {
        data[key] = value;
    }
    bool save(const std::string& filename) const override {
        std::ofstream out(filename);
        if (!out) return false;
        out << data.dump(2);
        return true;
    }
};