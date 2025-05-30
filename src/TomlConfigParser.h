#pragma once
#include "IConfigParser.h"
#include <toml++/toml.h>
#include <fstream>
#include <string>

class TomlConfigParser : public IConfigParser {
    toml::table tbl;
public:
    bool load(const std::string& filename) override;
    std::string get(const std::string& key) const override;
    void set(const std::string& key, const std::string& value) override;
    bool save(const std::string& filename) const override;
};