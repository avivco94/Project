#pragma once

//A base abstract class for all commands 
class ICommand {
	public:
		virtual ~ICommand();
		virtual void execute() = 0;
		virtual void undo() = 0;
};

