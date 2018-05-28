#pragma once
#include "IBullet.h"
class DefaultBullet :
	public IBullet {
	public:
		DefaultBullet(BulletInfo& bi);
		~DefaultBullet();
};

