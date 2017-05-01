#include "UnitAI.h"

UnitAI::UnitAI(Entity381* ent) : Aspect(ent)
{
	commands.clear();
	this->aspectType = ASPECT_TYPE::AI;
}

UnitAI::~UnitAI()
{

}

void UnitAI::AddCommand(Command *c)
{
	commands.push_back(c);
}

void UnitAI::SetCommand(Command* c)
{
	commands.clear();
	commands.push_front(c);
}

void UnitAI::Tick(float dt)
{
}


