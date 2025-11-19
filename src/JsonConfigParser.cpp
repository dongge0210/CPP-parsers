#include "pch.h"
#include "JsonConfigParser.h"

bool JsonConfigParser::load(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;
    try {
        in >> data;
        return true;
    } catch (const nlohmann::json::exception& e) {
        return false;
    }
}

std::string JsonConfigParser::get(const std::string& key) const {
    if (data.contains(key)) {
        if (data[key].is_string()) {
            return data[key].get<std::string>();
        }
        return data[key].dump();
    }
    return "";
}

void JsonConfigParser::set(const std::string& key, const std::string& value) {
    data[key] = value;
}

bool JsonConfigParser::save(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;
    try {
        out << data.dump(2);
        return true;
    } catch (const nlohmann::json::exception& e) {
        return false;
    }
}