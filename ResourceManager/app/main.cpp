#include "ResourceManager.hpp"
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
