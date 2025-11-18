
#include "pch.h"
#include "YamlConfigParser.h"

bool YamlConfigParser::load(const std::string& filename) {
    try {
        node = YAML::LoadFile(filename);
        return node ? true : false;
    } catch (const YAML::Exception& e) {
        // Handle or log the exception, e.g., std::cerr << e.what() << std::endl;
        return false;
    }
}

std::string YamlConfigParser::get(const std::string& key) const {
    if (node && node[key]) {
        try {
            return node[key].as<std::string>();
        } catch (const YAML::Exception& e) {
            // Handle or log, key might exist but not be a string
            return "";
        }
    }
    return "";
}

void YamlConfigParser::set(const std::string& key, const std::string& value) {
    if (!node) {
        node = YAML::Node(YAML::NodeType::Map);
    }
    node[key] = value;
}

bool YamlConfigParser::save(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return false;
    if (node) {
        out << node;
    } else {
        // Optionally write an empty structure or handle as an error
        out << YAML::Node(YAML::NodeType::Map);
    }
    return true;
}