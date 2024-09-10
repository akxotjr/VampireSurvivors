#include "pch.h"
#include "EventManager.h"

unique_ptr<EventManager> EventManager::instance = nullptr;

void EventManager::Init()
{
}

void EventManager::Update()
{
	while (!_eventQueue.empty())
	{
		_eventQueue.front()();
		_eventQueue.pop();
	}
}

void EventManager::Render(HDC hdc)
{
}
