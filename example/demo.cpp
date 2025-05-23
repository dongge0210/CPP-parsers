#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "../include/ConfigParserFactory.h"

int main() {
    std::vector<std::string> files = {
        "example/config.json",
        "example/config.yaml",
        "example/config.xml",
        "example/config.toml",
        "example/config.ini"
    };
    for (const auto& file : files) {
        auto parser = createParser(file);
        if (!parser) {
            std::cout << "No parser for: " << file << std::endl;
            continue;
        }
        if (!parser->load(file)) {
            std::cout << "Failed to load: " << file << std::endl;
            continue;
        }
        std::cout << "File: " << file << std::endl;
        std::cout << "  username: " << parser->get("username") << std::endl;
        std::cout << "  password: " << parser->get("password") << std::endl;
        parser->set("username", "bob");
        parser->set("password", "654321");
        parser->save(file + ".out");
        std::cout << "  [Modified and saved as " << file << ".out]\n" << std::endl;
    }
    return 0;
}