#pragma once
#include "ICommand.h"
#include "Player.h"

class ChangeWeaponCommand :
	public ICommand
{
public:
	ChangeWeaponCommand(std::shared_ptr<Player> ma);
	~ChangeWeaponCommand();
	void execute() override;
	void undo() override;
private:
	std::shared_ptr<Player> m_ma;
};

