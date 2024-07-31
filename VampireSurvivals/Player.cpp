#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Flipbook.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "CameraComponent.h"

Player::Player()
{
	_flipbookIdle[0] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierIdleRight");
	_flipbookIdle[1] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierIdleLeft");

	_flipbookMove = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierMove");
	_flipbookAttack = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierAttack");
	
	CameraComponent* camera = new CameraComponent();
	
	AddComponent(camera);
}

Player::~Player()
{
}

void Player::Init()
{
	Super::Init();
	//SetState(PlayerState::Move);
	SetState(PlayerState::Idle);
	//SetCellPos({ 5, 5 }, true);
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
	case PlayerState::Attack:
		UpdateAttack();
		break;
	}
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::UpdateAnimation()
{
	switch (_state)
	{
	case PlayerState::Idle:
		if (_keyPressed)
			SetFlipbook(_flipbookMove);
		else
			SetFlipbook(_flipbookIdle[_dir%2]);
		break;
	case PlayerState::Move:
		SetFlipbook(_flipbookMove);
		break;
	case PlayerState::Attack:
		SetFlipbook(_flipbookAttack);
		break;
	}
}

void Player::UpdateIdle()
{
	//float deltaTime = TimeManager::GetInstance()->GetDeltaTime();

	_keyPressed = true;
	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	if (InputManager::GetInstance()->GetButton(KeyType::W))
	{
		SetDir(DIR_UP);

		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		//if (CanGo(nextPos))
		//{
		//	//SetCellPos(nextPos);
		//	SetState(PlayerState::Move);
		//}
		SetState(PlayerState::Move);
	}
	else  if (InputManager::GetInstance()->GetButton(KeyType::S))
	{
		SetDir(DIR_DOWN);
		SetState(PlayerState::Move);
	}
	else if (InputManager::GetInstance()->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
		SetState(PlayerState::Move);
	}
	else if (InputManager::GetInstance()->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		SetState(PlayerState::Move);
	}
	else if (InputManager::GetInstance()->GetButton(KeyType::Q))
	{
		SetDir(_dir);
		SetState(PlayerState::Attack);
	}
	else
	{
		_keyPressed = false;
		if (_state == PlayerState::Idle)
			UpdateAnimation();
	}
}

void Player::UpdateMove()
{
	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();
	if (deltaTime < 10.f)
	{
		Vec2 dir = (_destPos - _pos);
		SetState(PlayerState::Idle);
		//_pos = _destPos;
	}
	else
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

void Player::UpdateAttack()
{
	UpdateAnimation();
}

//void Player::SetCellPos(Vec2Int cellPos, bool teleport)
//{
//	_cellPos = cellPos;
//
//	DevScene* scene = dynamic_cast<DevScene*>(SceneManager::GetInstance()->GetCurrentScene().get());
//	if (scene == nullptr)
//		return;
//
//	_destPos = scene->ConvertPos(cellPos);
//
//	if (teleport)
//		_pos = _destPos;
//}
//
//bool Player::HasReachedDest()
//{
//	Vec2 dir = (_destPos - _pos);
//	return (dir.Length() < 10.f);
//}
//
//bool Player::CanGo(Vec2Int cellPos)
//{
//	DevScene* scene = dynamic_cast<DevScene*>(SceneManager::GetInstance()->GetCurrentScene().get());
//	if (scene == nullptr)
//		return false;
//
//	return scene->CanGo(cellPos);
//}
