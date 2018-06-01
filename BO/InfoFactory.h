#pragma once
#include "SerializableInfo.h"
#include <unordered_map>
#include <functional>
#include <memory>

class InfoFactory
{
	public:
		static InfoFactory& getInstance();
		std::shared_ptr<SerializableInfo> get(const std::string& data);
	private:
		InfoFactory();
		~InfoFactory();
		template <typename T>
		std::shared_ptr<SerializableInfo> insert(const std::string& data);
		std::unordered_map<std::string, std::function<std::shared_ptr<SerializableInfo>(const std::string&)>> m_map;
};

template<typename T>
inline std::shared_ptr<SerializableInfo> InfoFactory::insert(const std::string & data) {
	return std::make_shared<T>(data);
}
