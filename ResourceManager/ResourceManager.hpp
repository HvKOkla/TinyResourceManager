#pragma once
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <filesystem>

namespace Core {

    template <typename T>
    class ResourceManager {
    public:
        ResourceManager() = default;
        ~ResourceManager() = default;

        
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        
        ResourceManager(ResourceManager&&) noexcept = default;
        ResourceManager& operator=(ResourceManager&&) noexcept = default;

   
        std::shared_ptr<T> load(const std::filesystem::path& filepath) {
            std::string key = filepath.lexically_normal().string();

            
            if (auto it = m_resources.find(key); it != m_resources.end()) {
                std::cout << "[RESOURCE] Cache hit : " << key << '\n';
                return it->second;
            }

            
            auto resource = std::make_shared<T>();

            
            if (!resource->loadFromFile(key)) {
                std::cerr << "[RESOURCE ERROR] Echec du chargement : " << key << '\n';
                return nullptr;
            }

            
            m_resources[key] = resource;
            std::cout << "[RESOURCE] Chargee depuis le disque : " << key << '\n';
            return resource;
        }

        bool isLoaded(const std::filesystem::path& filepath) const {
            std::string key = filepath.lexically_normal().string();
            return m_resources.find(key) != m_resources.end();
        }

      
        std::size_t unloadUnused() {
            std::size_t count = 0;
            for (auto it = m_resources.begin(); it != m_resources.end(); ) {
                
                if (it->second.use_count() == 1) {
                    std::cout << "[RESOURCE] Liberation mémoire : " << it->first << '\n';
                    it = m_resources.erase(it);
                    ++count;
                }
                else {
                    ++it;
                }
            }
            return count;
        }


        void clear() {
            m_resources.clear();
        }

        [[nodiscard]] std::size_t size() const noexcept {
            return m_resources.size();
        }

    private:
        
        std::unordered_map<std::string, std::shared_ptr<T>> m_resources;
    };

} // namespace Core

#endif // RESOURCE_MANAGER_HPP
