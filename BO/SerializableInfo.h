#pragma once
#include <string>
#include <sstream>
#include "GameInfo.h"

struct SerializableInfo {
	public:
		SerializableInfo(std::string type);
		virtual std::string deserialize();
		
		virtual void update(std::shared_ptr<GameUpdater> gu) = 0;
	protected:
		virtual void serialize(std::stringstream& params) = 0;
		virtual std::string deserializeInfo() const = 0;
		std::string m_type;
};

