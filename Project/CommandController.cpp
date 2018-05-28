#include "CommandController.h"

CommandController::CommandController() {}
CommandController::~CommandController() {}

void CommandController::addCommandAndExecute(std::shared_ptr<ICommand> c) {
	//TODO
	//if (m_index < (int)Updates<std::shared_ptr<ICommand>>::getInstance().size())
		Updates<std::shared_ptr<ICommand>>::getInstance().clear();
	Updates<std::shared_ptr<ICommand>>::getInstance().add(c);
	c->execute();
	m_index++;
}
void CommandController::undoPressed() {
	if (m_index >= 0)
		Updates<std::shared_ptr<ICommand>>::getInstance()[m_index--]->undo();
}
void CommandController::redoPressed() {
	if (m_index < (int)Updates<std::shared_ptr<ICommand>>::getInstance().size())
		Updates<std::shared_ptr<ICommand>>::getInstance()[m_index++]->execute();
}