#pragma once
#include "UI.h"

class Sprite;

enum ButtonState
{
	BS_Default,
	//BS_Hovered,
	BS_Pressed,
	BS_Clicked,
	// ...
	BS_MaxCount
};

class Button : public UI
{
	using Super = UI;
public:
	Button();
	virtual ~Button() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void	SetSize(Vec2Int size) { _size = size; }
	Sprite* GetSprite(ButtonState state) { return _sprites[state]; }

	void SetCurrentSprite(Sprite* sprite) { _currentSprite = sprite; }
	void SetSprite(Sprite* sprite, ButtonState state) { _sprites[state] = sprite; }
	void SetButtonState(ButtonState state);

	void SetText(const wstring& text) { _text = text; }

protected:
	Sprite* _currentSprite = nullptr;
	Sprite* _sprites[BS_MaxCount] = {};
	ButtonState _state = BS_Default;
	// ...
	float _sumTime = 0.f;

	wstring _text;

public:
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]()
			{
				(owner->*func)();
			};
	}

	template<typename T, typename Arg>
	void AddOnClickDelegate(T* owner, void(T::* func)(Arg), Arg arg)
	{
		_onClick = [owner, func, arg]()
			{
				(owner->*func)(arg);
			};
	}

	template<typename T, typename Arg1, typename Arg2>
	void AddOnClickDelegate(T* owner, void(T::* func)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
	{
		_onClick = [owner, func, arg1, arg2]()
			{
				(owner->*func)(arg1, arg2);
			};
	}


	// 함수 포인터 + 함수 객체
	std::function<void(void)> _onClick = nullptr;
};

