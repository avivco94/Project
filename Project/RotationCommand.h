#pragma once
#include "ICommand.h"
#include "MoveableSpriteObject.h"
#include <memory>

class RotationCommand :
	public ICommand
{
public:
	RotationCommand(std::shared_ptr<MoveableSpriteObject> ma, float rotation);
	~RotationCommand();
	void execute() override;
	void undo() override;

private:
	std::shared_ptr<MoveableSpriteObject> m_ma;
	float m_rotation;
	float m_lastRotation;
};

