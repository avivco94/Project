#include "DefaultBullet.h"



DefaultBullet::DefaultBullet(BulletInfo& bi) 
	: IBullet(bi.m_id, bi.m_pid, bi.m_rect, bi.m_currPos, bi.m_direction, bi.m_rotation, bi.m_durtion, bi.m_speed, bi.m_type) {
	IBullet::m_passed = {0, 0};
}

DefaultBullet::~DefaultBullet() {}
