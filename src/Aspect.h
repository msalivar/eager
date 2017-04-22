#pragma once

#include "Entity381.h"
#include "Types.h"

class Aspect 
{
public:
    explicit Aspect(Entity381* ent);
	virtual ~Aspect();

	virtual void Tick(float dt) = 0;
	Entity381 *entity;
	ASPECT_TYPE aspectType;
};

class Renderable : public Aspect
{
public:
	Renderable(Entity381* ent);
	~Renderable();
	virtual void Tick(float dt);
};


class Physics : public Aspect
{
public:
	Physics(Entity381* ent);
	~Physics();
	virtual void Tick(float dt);
};