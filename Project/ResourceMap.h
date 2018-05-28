#pragma once
#include <memory>
#include <unordered_map>
#include <string>

template <typename T>
class ResourceMap {
	typedef std::unordered_map<std::string, std::shared_ptr<T>> ResourceMapType;
public:
	ResourceMap();
	~ResourceMap();
	//Add resource to map
	void addResource(const std::string& key, std::shared_ptr<T> resource);
	//Get resource from map
	std::shared_ptr<T> getResource(const std::string& key);
private:
	ResourceMapType m_map;
};

template <typename T>
ResourceMap<T>::ResourceMap() {}

template <typename T>
ResourceMap<T>::~ResourceMap() {}

template <typename T>
void ResourceMap<T>::addResource(const std::string& key, std::shared_ptr<T> resource) {
	m_map.insert(std::make_pair(key, resource));
}

template <typename T>
std::shared_ptr<T> ResourceMap<T>::getResource(const std::string& key) {
	auto it = m_map.find(key);
	if (it != m_map.end()) {
		return (*it).second;
	}
	return NULL;
}