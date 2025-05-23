#pragma once
#include "IConfigParser.h"
#include <toml++/toml.h>
#include <fstream>
#include <string>

class TomlConfigParser : public IConfigParser {
    toml::table tbl;
public:
    bool load(const std::string& filename) override {
        auto parse_result = toml::parse_file(filename);
        if (!parse_result) return false;
        tbl = std::move(*parse_result);
        return true;
    }
    std::string get(const std::string& key) const override {
        if (auto v = tbl[key]) return v->as_string() ? v->as_string()->get() : "";
        return "";
    }
    void set(const std::string& key, const std::string& value) override {
        tbl.insert_or_assign(key, value);
    }
    bool save(const std::string& filename) const override {
        std::ofstream out(filename);
        if (!out) return false;
        out << tbl;
        return true;
    }
};