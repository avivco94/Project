#pragma once

//A base abstract class for all commands 
class ICommand {
	public:
		virtual ~ICommand();
		//Execute command
		virtual void execute() = 0;
		//Undo command
		virtual void undo() = 0;
};

