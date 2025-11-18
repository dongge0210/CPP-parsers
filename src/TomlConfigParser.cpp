
#include "pch.h"
#include "TomlConfigParser.h"
#include <iostream> // For error reporting, optional

bool TomlConfigParser::load(const std::string& filename) {
    try {
        tbl = toml::parse_file(filename);
        return true;
    } catch (const toml::parse_error& err) {
        // std::cerr << "TOML parsing error: " << err.what() << std::endl;
        return false;
    } catch (const std::exception& ex) {
        // std::cerr << "An exception occurred: " << ex.what() << std::endl;
        return false;
    }
}

std::string TomlConfigParser::get(const std::string& key) const {
    if (auto node_view = tbl.get(key)) { // Use tbl.get() for safer access
        if (node_view->is_string()) {
            return node_view->as_string()->get();
        }
        // Optionally handle other types or return their string representation
        // For now, only return if it's explicitly a string
    }
    return "";
}

void TomlConfigParser::set(const std::string& key, const std::string& value) {
    tbl.insert_or_assign(key, value);
}

bool TomlConfigParser::save(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;
    out << tbl;
    return true;
}