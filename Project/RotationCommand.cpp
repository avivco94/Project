#include "RotationCommand.h"



RotationCommand::RotationCommand(std::shared_ptr<MoveableSpriteObject> ma, float rotation) 
	: m_ma(ma), m_rotation(rotation) {}


RotationCommand::~RotationCommand() {}

void RotationCommand::execute() {
	m_lastRotation = m_ma->getRotation();
	m_ma->setRotation(m_rotation);
}
void RotationCommand::undo() {
	m_ma->setRotation(m_lastRotation);
}
