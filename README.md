TinyResourceManager Lightweight header-only C++20 resource manager for games and real-time apps.

Features:

•	Header-only: drop ResourceManager.hpp into your project
•	Smart caching: avoids duplicate disk loads
•	Modern C++20 (stdshared_ptr, stdfilesystem, concepts)
•	Automatic cleanup of unused resources

Quick start:

1.	Copy ResourceManager.hpp into your include path
2.	#include "ResourceManager.hpp"
3.	Use CoreResourceManager<T> to load resources:
4.	Example:
5.	#include "ResourceManager.hpp"
#include <iostream>

struct DummyResource {
	bool loadFromFile(const std::string& path) {
		std::cout << "DummyResource::loadFromFile called with: " << path << '\n';
		return true;
	}
};

int main() {
	Core::ResourceManager<DummyResource> mgr;

	auto res = mgr.load("test.txt");
	std::cout << "isLoaded(test.txt): " << (mgr.isLoaded("test.txt") ? "yes" : "no") << '\n';
	std::cout << "size: " << mgr.size() << '\n';

	// release the shared_ptr and free unused resources
	res.reset();
	std::cout << "unloadUnused: " << mgr.unloadUnused() << '\n';

	return 0;
}

•	C++20 compiler (MSVC/Clang/GCC)
•	CMake >= 3.15 (if using provided build files)

License MIT 
   
