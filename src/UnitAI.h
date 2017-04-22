#pragma once

#include "Aspect.h"
#include "Command.h"
#include <list>

class UnitAI : public Aspect
{

public:

	std::list<Command*> commands;

	UnitAI(Entity381* ent);
	~UnitAI();

	void Tick(float dt);
	void SetCommand(Command *c);
	void AddCommand(Command *c);

};
