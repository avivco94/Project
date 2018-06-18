#pragma once
class ICommand {
	public:
		virtual ~ICommand();
		//Execute command
		virtual void execute() = 0;
		//Undo command
		virtual void undo() = 0;
};

