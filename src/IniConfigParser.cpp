
#include "IniConfigParser.h"

bool IniConfigParser::load(const std::string& filename) {
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

std::string IniConfigParser::get(const std::string& key) const {
    auto it = data.find(key);
    return it != data.end() ? it->second : "";
}

void IniConfigParser::set(const std::string& key, const std::string& value) {
    data[key] = value;
}

bool IniConfigParser::save(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;
    for (const auto& kv : data) {
        out << kv.first << "=" << kv.second << "\n";
    }
    return true;
}