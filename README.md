#  Modern C++20 Resource Manager

A lightweight, **header-only** C++20 resource manager designed for games and real-time applications. It handles automatic caching, path normalization, and safe memory management using smart pointers.

## Features
* **Header-Only:** Drop `ResourceManager.hpp` into your project and go.
* **Smart Caching:** Prevents loading duplicate files from disk.
* **Modern C++17:** Built with `std::shared_ptr`, `std::filesystem`, and type safety.
* **Automatic Cleanup:** Easily unload resources no longer in use.


##  Quick Start

```cpp
#include "ResourceManager.hpp"

struct Texture {
    bool loadFromFile(const std::string& path) { return true; }
};

int main() {
    Core::ResourceManager<Texture> textures;

    // Load from disk
    auto hero = textures.load("assets/hero.png");

    // Loaded from cache instantly!
    auto duplicate = textures.load("assets/hero.png");

    // Clean up unused memory
    textures.unloadUnused();
}
