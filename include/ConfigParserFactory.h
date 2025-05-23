#pragma once
#include "JsonConfigParser.h"
#include "YamlConfigParser.h"
#include "XmlConfigParser.h"
#include "TomlConfigParser.h"
#include "IniConfigParser.h"
#include <memory>
#include <algorithm>

inline std::unique_ptr<IConfigParser> createParser(const std::string& filename) {
    auto ext_pos = filename.find_last_of('.');
    if (ext_pos == std::string::npos) return nullptr;
    std::string ext = filename.substr(ext_pos + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    if (ext == "json") return std::make_unique<JsonConfigParser>();
    if (ext == "yaml" || ext == "yml") return std::make_unique<YamlConfigParser>();
    if (ext == "xml") return std::make_unique<XmlConfigParser>();
    if (ext == "toml") return std::make_unique<TomlConfigParser>();
    if (ext == "ini") return std::make_unique<IniConfigParser>();
    return nullptr;
}