#pragma once
#include "IConfigParser.h"
#include <tinyxml2.h>
#include <fstream>
#include <string>
#include <sstream>

class XmlConfigParser : public IConfigParser {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* root = nullptr;
public:
    bool load(const std::string& filename) override;
    std::string get(const std::string& key) const override;
    void set(const std::string& key, const std::string& value) override;
    bool save(const std::string& filename) const override;
};