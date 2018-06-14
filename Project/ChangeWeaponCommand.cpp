#include "ChangeWeaponCommand.h"



ChangeWeaponCommand::ChangeWeaponCommand(std::shared_ptr<Player> ma) : m_ma(ma) {}

ChangeWeaponCommand::~ChangeWeaponCommand() {}

void ChangeWeaponCommand::execute() {
	m_ma->changeWeapon();
}

void ChangeWeaponCommand::undo()
{
}
