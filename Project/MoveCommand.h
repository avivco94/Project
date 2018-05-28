#pragma once
#include "ICommand.h"
#include "MoveableSpriteObject.h"
#include <memory>

class MoveCommand :
	public ICommand
{
	public:
		MoveCommand(std::shared_ptr<MoveableSpriteObject> ma, sf::Vector2f vec);
		~MoveCommand();
		void execute() override;
		void undo() override;
	private:
		std::shared_ptr<MoveableSpriteObject> m_ma;
		sf::Vector2f m_vec;
};

