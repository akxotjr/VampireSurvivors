#pragma once

class EventManager
{
public:
	~EventManager() = default;

	static EventManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = make_unique<EventManager>();
		}
		return instance.get();
	}

	void Init();
	void Update();
	void Render(HDC hdc);

	using Event = ::function<void(void)>;
	void AddEvent(Event e)
	{
		_eventQueue.push(e);
	}

private:
	EventManager() = default;

	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;

	friend std::unique_ptr<EventManager> std::make_unique<EventManager>();

private:
	static unique_ptr<EventManager> instance;

	queue<Event> _eventQueue;
};

