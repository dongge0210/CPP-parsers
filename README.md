# CPP-parsers

用于C/C++的主流解析库集合，并实现统一接口调用。

本仓库以子模块形式收录了当前主流、实用、稳定的 C/C++ 配置/数据解析库（支持 JSON、YAML、XML、TOML、INI），并提供了一个统一的接口和 Demo，方便开发者以同一套 API 使用多种格式的数据文件。

---

**该库未经过测试！

## 收录的解析库

- [nlohmann/json](https://github.com/nlohmann/json) - 现代 C++ JSON 解析库
- [yaml-cpp](https://github.com/jbeder/yaml-cpp) - C++ YAML 解析库
- [tinyxml2](https://github.com/leethomason/tinyxml2) - 轻量级 C++ XML 解析库
- [tomlplusplus](https://github.com/marzer/tomlplusplus) - 现代 C++ TOML 解析库
- [inih](https://github.com/benhoyt/inih) - 超轻量 INI 配置解析库

---

## 统一接口说明

本项目设计了统一的 `IConfigParser` 接口，所有格式的解析器都实现了该接口。  
你可以通过工厂方法自动选择合适的解析器，轻松实现多格式配置/数据文件的读取与写入，调用方式完全一致。

---

## 示例代码

以 `example/demo.cpp` 为例，项目支持如下用法：

```cpp
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
```

你可以在 `example/` 目录下找到各种格式的示例配置文件。

---

## 目录结构

```plaintext
CPP-parsers/
├── extern/                  # 子模块：各解析库源代码
├── include/                 # 统一接口及工厂
├── src/                     # 各格式解析器实现
├── example/                 # 示例代码与配置文件
├── CMakeLists.txt           # 构建文件
└── README.md
```

---

## 如何克隆本项目（含子模块）

```bash
git clone --recurse-submodules https://github.com/dongge0210/CPP-parsers.git
# 或 clone 后初始化所有子模块
git submodule update --init --recursive
```

---

## 构建方法

本项目采用 CMake 构建，要求 CMake >= 3.14，C++17 标准及以上。

```bash
mkdir build && cd build
cmake ..
make
./demo
```

---

## 贡献与补充

- 如需补充其它解析库或改进统一接口，欢迎提 PR 或 issue！
- 欢迎提供各库更复杂的用法示例。

---

## License

见各子模块库自身 LICENSE。项目本身采用 MIT 协议。
