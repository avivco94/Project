#include "MoveCommand.h"
#include "CollisionManager.h"

MoveCommand::MoveCommand(std::shared_ptr<MoveableSpriteObject> ma, sf::Vector2f vec)
	: m_ma(ma), m_vec(vec) {}

MoveCommand::~MoveCommand() {}

void MoveCommand::execute() {
	m_ma->move(m_vec);
}

void MoveCommand::undo() {
	m_ma->move(-m_vec);
}