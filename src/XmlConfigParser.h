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
    bool load(const std::string& filename) override {
        doc.Clear();
        if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
            return false;
        root = doc.FirstChildElement("root");
        return root != nullptr;
    }
    std::string get(const std::string& key) const override {
        if (!root) return "";
        for (auto* child = root->FirstChildElement("item"); child; child = child->NextSiblingElement("item")) {
            const char* k = child->Attribute("key");
            if (k && key == k) {
                return child->GetText() ? child->GetText() : "";
            }
        }
        return "";
    }
    void set(const std::string& key, const std::string& value) override {
        if (!root) {
            root = doc.NewElement("root");
            doc.InsertFirstChild(root);
        }
        for (auto* child = root->FirstChildElement("item"); child; child = child->NextSiblingElement("item")) {
            const char* k = child->Attribute("key");
            if (k && key == k) {
                child->SetText(value.c_str());
                return;
            }
        }
        auto* item = doc.NewElement("item");
        item->SetAttribute("key", key.c_str());
        item->SetText(value.c_str());
        root->InsertEndChild(item);
    }
    bool save(const std::string& filename) const override {
        return doc.SaveFile(filename.c_str()) == tinyxml2::XML_SUCCESS;
    }
};