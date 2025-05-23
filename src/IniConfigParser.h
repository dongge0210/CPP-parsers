#pragma once
#include "IConfigParser.h"
#include <INIReader.h> // inih 库的 C++ 封装
#include <fstream>
#include <string>
#include <map>

class IniConfigParser : public IConfigParser {
    std::map<std::string, std::string> data;
    std::string lastFile;
public:
    bool load(const std::string& filename) override {
        data.clear();
        lastFile = filename;
        INIReader reader(filename);
        if (reader.ParseError()) return false;
        for (auto& section : reader.Sections()) {
            for (auto& key : reader.Keys(section)) {
                data[key] = reader.Get(section, key, "");
            }
        }
        return true;
    }
    std::string get(const std::string& key) const override {
        auto it = data.find(key);
        return it != data.end() ? it->second : "";
    }
    void set(const std::string& key, const std::string& value) override {
        data[key] = value;
    }
    bool save(const std::string& filename) const override {
        std::ofstream out(filename);
        if (!out) return false;
        for (const auto& kv : data) {
            out << kv.first << "=" << kv.second << "\n";
        }
        return true;
    }
};