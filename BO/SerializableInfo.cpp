#include "SerializableInfo.h"

SerializableInfo::SerializableInfo(std::string type) : m_type(type) {}

std::string SerializableInfo::deserialize() {
	return m_type + " " + deserializeInfo();
}
