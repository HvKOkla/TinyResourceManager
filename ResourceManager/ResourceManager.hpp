#pragma once

#include <filesystem>
#include <format>
#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <type_traits>
#include <utility>

namespace Core {

    
    namespace detail {
        template<typename, typename = void>
        struct is_loadable_resource : std::false_type {};
        template<typename T>
        struct is_loadable_resource<T, std::void_t<
            decltype(std::declval<T>().loadFromFile(std::declval<const std::string&>()))
        >> : std::bool_constant<
            std::is_same_v<decltype(std::declval<T>().loadFromFile(std::declval<const std::string&>())), bool> &&
            std::is_default_constructible_v<T>
        > {};
    }

    template <typename T>
    class ResourceManager {
    public:
        static_assert(detail::is_loadable_resource<T>::value, "T must be default-constructible and have bool loadFromFile(const std::string&).");
        ResourceManager() = default;
        ~ResourceManager() = default;

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        ResourceManager(ResourceManager&&) noexcept = default;
        ResourceManager& operator=(ResourceManager&&) noexcept = default;

        std::shared_ptr<T> load(const std::filesystem::path& filepath) {
            std::string key = filepath.lexically_normal().string();

            
            {
                std::shared_lock<std::shared_mutex> readLock(m_mutex);
                if (auto it = m_resources.find(key); it != m_resources.end()) {
                    std::cout << std::format("[RESOURCE] Cache hit : {}\n", key);
                    return it->second;
                }
            }

            
            auto resource = std::make_shared<T>();
            if (!resource->loadFromFile(key)) {
                std::cerr << std::format("[RESOURCE ERROR] Échec du chargement : {}\n", key);
                return nullptr;
            }

            
            {
                std::unique_lock<std::shared_mutex> writeLock(m_mutex);

                
                if (auto it = m_resources.find(key); it != m_resources.end()) {
                    std::cout << std::format("[RESOURCE] Cache hit (post-load) : {}\n", key);
                    return it->second;
                }

                m_resources[key] = resource;
                std::cout << std::format("[RESOURCE] Chargée depuis le disque : {}\n", key);
            }

            return resource;
        }

        [[nodiscard]] bool isLoaded(const std::filesystem::path& filepath) const {
            std::string key = filepath.lexically_normal().string();

            std::shared_lock<std::shared_mutex> readLock(m_mutex);
            return m_resources.contains(key);
        }

        std::size_t unloadUnused() {
            std::unique_lock<std::shared_mutex> writeLock(m_mutex);

            return std::erase_if(m_resources, [](const auto& pair) {
                const auto& [key, resource] = pair;
                bool isUnused = (resource.use_count() == 1);

                if (isUnused) {
                    std::cout << std::format("[RESOURCE] Libération mémoire : {}\n", key);
                }

                return isUnused;
                });
        }

        void clear() noexcept {
            std::unique_lock<std::shared_mutex> writeLock(m_mutex);
            m_resources.clear();
        }

        [[nodiscard]] std::size_t size() const noexcept {
            std::shared_lock<std::shared_mutex> readLock(m_mutex);
            return m_resources.size();
        }

    private:
        mutable std::shared_mutex m_mutex; 
        std::unordered_map<std::string, std::shared_ptr<T>> m_resources;
    };

} 
