#pragma once
#include <unordered_map>
#include "GameUpdater.h"
#include <memory>

struct PlayerInfo;
struct BulletInfo;

class GameInfo 
	: public GameUpdater {
	public:
		GameInfo();
		~GameInfo();
		void update(BulletInfo& bi) override;
		void update(PlayerInfo& pi) override;
		void update(ConnectionInfo& pi) override;
		void update(HitInfo & pi) override;
		const std::unordered_map<std::string, std::shared_ptr<PlayerInfo>>& getPlayers();
		const std::unordered_map<std::string, std::shared_ptr<BulletInfo>>& getBullets();
		std::shared_ptr<PlayerInfo> removePlayer(const std::string& id);
		//void updateWeapon();
	private:
		std::unordered_map<std::string, std::shared_ptr<PlayerInfo>> m_players;
		std::unordered_map<std::string, std::shared_ptr<BulletInfo>> m_bullets;
};

