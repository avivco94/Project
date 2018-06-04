#pragma once
#include <memory>
#include <map>
#include "Exceptions.h"
#include <functional>

template <typename T>
class Factory {
	public:
		static Factory& getInstance();
		template <class... Args>
		bool add(const std::string& symbol, std::shared_ptr<T>(*)(Args...));
		template <class... Args>
		std::shared_ptr<T> get(const std::string& symbol, Args &&... args);
	private:
		std::map<std::string, void *> m_map;

};


template <typename T>
Factory<T>& Factory<T>::getInstance() {
	static Factory instance;
	return instance;
}

template<typename T>
template<class ...Args>
bool Factory<T>::add(const std::string & symbol, std::shared_ptr<T>(*func)(Args ...)) {
	m_map[symbol] = func;
	return true;

}

template<typename T>
template<class ...Args>
inline std::shared_ptr<T> Factory<T>::get(const std::string & symbol, Args && ...args) {
	auto it = m_map.find(symbol);
	if (it != m_map.end()) {
		typedef std::shared_ptr<T>(*func)(const std::string & symbol, Args...);
		auto createFunc = reinterpret_cast<func>(it->second);
		return createFunc(symbol, args...);
	}
	return nullptr;
}
