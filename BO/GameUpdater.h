#pragma once
struct PlayerInfo;
struct BulletInfo;
struct ConnectionInfo;

class GameUpdater
{
	public:
		GameUpdater();
		~GameUpdater();
		virtual void update(BulletInfo& bi) = 0;
		virtual void update(PlayerInfo& pi) = 0;
		virtual void update(ConnectionInfo& pi) = 0;
};

