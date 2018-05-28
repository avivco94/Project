#pragma once
#include <memory>
#include "Updates.h"
#include "ICommand.h"

class CommandController {
	public:
		CommandController();
		~CommandController();
		void addCommandAndExecute(std::shared_ptr<ICommand> c);
		void undoPressed();
		void redoPressed();

	private:
		int m_index = 0;
};