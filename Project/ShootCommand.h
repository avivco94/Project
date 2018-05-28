#pragma once
#include "ICommand.h"
#include "Player.h"
#include <memory>

class ShootCommand :
	public ICommand {
	public:
		ShootCommand(std::shared_ptr<Player> ma);
		~ShootCommand();
		void execute() override;
		void undo() override;
	private:
		std::shared_ptr<Player> m_ma;
};

