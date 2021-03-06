#pragma once
#include "SerializableInfo.h"
#include <string>
#include <sstream>

//Struct for sending and reciving the info between server and client
struct HitInfo 
	: public SerializableInfo
{
	public:
		HitInfo(std::string type);
		HitInfo(std::string shooter, std::string gotShot, std::string type);
		~HitInfo();
		void update(std::shared_ptr<GameUpdater> gu) override;
		std::string m_shooter;
		std::string m_gotShot;
		std::string m_type;
		static std::shared_ptr<SerializableInfo> create(const std::string & type, std::string & data) {
			return std::make_shared<HitInfo>(data);
		}
	protected:
		void serialize(std::stringstream& params) override;
		std::string deserializeInfo() const override;
	private:
		static bool m_registerit;
};

