#pragma once
#include "IConfigParser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

class JsonConfigParser : public IConfigParser {
    nlohmann::json data;
public:
    bool load(const std::string& filename) override;
    std::string get(const std::string& key) const override;
    void set(const std::string& key, const std::string& value) override;
    bool save(const std::string& filename) const override;
};