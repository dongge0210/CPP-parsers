#include "pch.h"
#include "XmlConfigParser.h"

bool XmlConfigParser::load(const std::string& filename) {
    doc.Clear(); // Clear previous document state
    root = nullptr; // Reset root pointer
    if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
        return false;
    root = doc.FirstChildElement("root");
    return root != nullptr;
}

std::string XmlConfigParser::get(const std::string& key) const {
    if (!root) return "";
    for (tinyxml2::XMLElement* child = root->FirstChildElement("item"); child; child = child->NextSiblingElement("item")) {
        const char* k = child->Attribute("key");
        if (k && key == k) {
            return child->GetText() ? child->GetText() : "";
        }
    }
    return "";
}

void XmlConfigParser::set(const std::string& key, const std::string& value) {
    if (!root) {
        // If doc is empty, add XML declaration first
        tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
        doc.InsertFirstChild(decl);
        root = doc.NewElement("root");
        doc.InsertEndChild(root); // Insert root after declaration
    }
    for (tinyxml2::XMLElement* child = root->FirstChildElement("item"); child; child = child->NextSiblingElement("item")) {
        const char* k = child->Attribute("key");
        if (k && key == k) {
            child->SetText(value.c_str());
            return;
        }
    }
    tinyxml2::XMLElement* item = doc.NewElement("item");
    item->SetAttribute("key", key.c_str());
    item->SetText(value.c_str());
    root->InsertEndChild(item);
}

bool XmlConfigParser::save(const std::string& filename) const {
    // Use const_cast to work around tinyxml2's non-const SaveFile method
    return const_cast<tinyxml2::XMLDocument&>(doc).SaveFile(filename.c_str()) == tinyxml2::XML_SUCCESS;
}