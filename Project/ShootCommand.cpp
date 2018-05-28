#include "ShootCommand.h"



ShootCommand::ShootCommand(std::shared_ptr<Player> ma) 
	: m_ma(ma) {}

ShootCommand::~ShootCommand() {}

void ShootCommand::execute() {
	m_ma->shoot();
}

void ShootCommand::undo() {
	//TODO
}