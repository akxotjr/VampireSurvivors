#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Sprite.h"

Button::Button()
{

}

Button::~Button()
{

}

void Button::Init()
{
	Super::Init();

	SetButtonState(BS_Default);
}

void Button::Update()
{
	POINT mousePos = InputManager::GetInstance()->GetMousePos();
	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();

	if (_state == BS_Clicked)
	{
		_sumTime += deltaTime;
		if (_sumTime >= 0.15f)
		{
			_sumTime = 0.f;
			SetButtonState(BS_Default);
		}
	}

	if (IsMouseInRect())
	{
		if (InputManager::GetInstance()->GetButton(KeyType::LeftMouse))
		{
			SetButtonState(BS_Pressed);
			// OnPressed
		}
		else
		{
			if (_state == BS_Pressed)
			{
				SetButtonState(BS_Clicked);
				// OnClicked
				if (_onClick)
					_onClick();
				else
					MessageBox(NULL, L"onClick is null", L"Error", MB_OK);
			}
		}
	}
	else
	{
		SetButtonState(BS_Default);
	}
}

void Button::Render(HDC hdc)
{
	if (_currentSprite)
	{
		const Vec2Int size = _currentSprite->GetSize();
		::TransparentBlt(hdc,
			(int32)_pos.x - size.x / 2,
			(int32)_pos.y - size.y / 2,
			size.x,
			size.y,
			_currentSprite->GetDC(),
			_currentSprite->GetPos().x,
			_currentSprite->GetPos().y,
			size.x,
			size.y,
			_currentSprite->GetTransparent());

		TextOut(hdc, (int32)_pos.x - 50, (int32)_pos.y - 160, _text.c_str(), _text.length());
	}
	else
	{
		Utils::DrawRect(hdc, _pos, _size.x, _size.y);
	}

}

void Button::SetButtonState(ButtonState state)
{
	_state = state;

	if (_sprites[state])
		SetCurrentSprite(_sprites[state]);
}
