#pragma once
#include "IConfigParser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

class JsonConfigParser : public IConfigParser {
public:
    nlohmann::json& GetData() { return data_; }
    const nlohmann::json& GetData() const { return data_; }

    bool load(const std::string& filename) override {
        std::ifstream in(filename);
        if (!in) return false;
        in >> data_;
        return true;
    }
    std::string get(const std::string& key) const override {
        if (data_.contains(key)) return data_[key].dump();
        return "";
    }
    void set(const std::string& key, const std::string& value) override {
        data_[key] = value;
    }
    bool save(const std::string& filename) const override {
        std::ofstream out(filename);
        if (!out) return false;
        out << data_.dump(2);
        return true;
    }

private:
    nlohmann::json data_;
};