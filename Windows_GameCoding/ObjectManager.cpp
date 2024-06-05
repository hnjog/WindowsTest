#include "pch.h"
#include "ObjectManager.h"
#include"Object.h"

ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::Add(Object* object)
{
	if (object == nullptr)
		return;

	auto findIt = std::find(_objects.begin(), _objects.end(), object);

	if (findIt != _objects.end())
		return;

	_objects.push_back(object);
}

void ObjectManager::Remove(Object* object)
{
	if (object == nullptr)
		return;

	auto it = std::remove(_objects.begin(), _objects.end(), object);
	_objects.erase(it, _objects.end());

	SAFE_DELETE(object);
}

void ObjectManager::Clear()
{
	for (auto obj : _objects)
	{
		SAFE_DELETE(obj);
	}

	_objects.clear();
}
