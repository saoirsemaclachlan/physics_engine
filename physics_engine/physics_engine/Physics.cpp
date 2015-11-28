#include <iostream>

#include "Physics.h"



Physics::Physics(std::vector<Object*>& objList)
    : mObjList(objList)
{
}

Physics::~Physics()
{
}

void Physics::initialise()
{
}

bool Physics::update()
{
	// broadphase
	// narrowphase

	for(const auto& obj : mObjList)
	{
		obj->phys().update();
	}

    return true;
}