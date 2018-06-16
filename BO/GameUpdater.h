#pragma once
struct PlayerInfo;
struct BulletInfo;
struct ConnectionInfo;
struct HitInfo;
struct DeathInfo;
struct KnifeAttackInfo;

//A abstract class for all objects that need to update the game from server (for the game screen) 
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
		virtual void update(KnifeAttackInfo& bi) = 0;
};

