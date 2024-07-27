#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	Super::Init();
}

void Player::Update()
{
	Super::Update();

	switch (_state)
	{
	case PlayerState::Idle:
		UpdateIdle();
		break;
	case PlayerState::Move:
		UpdateMove();
		break;
	case PlayerState::Skill:
		break;
	}
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::UpdateIdle()
{

}

void Player::UpdateMove()
{
	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();
	//if (deltaTime < 10.f)
	//{
	//	Vec2 dir = (_destPos - _pos);
	//	SetState(PlayerState::Idle);
	//	_pos = _destPos;
	//}
	//else

	if (InputManager::GetInstance()->GetButton(KeyType::W))
	{
		SetDir(Dir::DIR_UP);
	}
	else if (InputManager::GetInstance()->GetButton(KeyType::A))
	{
		SetDir(Dir::DIR_LEFT);
	}
	else if (InputManager::GetInstance()->GetButton(KeyType::S))
	{
		SetDir(Dir::DIR_DOWN);
	}
	else if (InputManager::GetInstance()->GetButton(KeyType::D))
	{
		SetDir(Dir::DIR_RIGHT);
	}

	{
		switch (_dir)
		{
		case DIR_UP:
			_pos.y -= 200 * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += 200 * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= 200 * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += 200 * deltaTime;
			break;
		}
	}
}
