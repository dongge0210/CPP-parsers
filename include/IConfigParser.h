#pragma once
#include <string>

class IConfigParser {
public:
    virtual ~IConfigParser() {}
    virtual bool load(const std::string& filename) = 0;
    virtual std::string get(const std::string& key) const = 0;
    virtual void set(const std::string& key, const std::string& value) = 0;
    virtual bool save(const std::string& filename) const = 0;
};