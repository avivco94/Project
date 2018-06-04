#pragma once
struct PlayerInfo;
struct BulletInfo;
struct ConnectionInfo;
struct HitInfo;
struct DeathInfo;

class GameUpdater
{
	public:
		GameUpdater();
		~GameUpdater();
		virtual void update(BulletInfo& bi) = 0;
		virtual void update(PlayerInfo& pi) = 0;
		virtual void update(ConnectionInfo& pi) = 0;
		virtual void update(HitInfo& bi) = 0;
		virtual void update(DeathInfo& bi) = 0;
		
};

