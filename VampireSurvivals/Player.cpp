#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Flipbook.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "CameraComponent.h"
#include "Projectile.h"

Player::Player()
{
	_flipbookIdle[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierIdleRight");
	_flipbookIdle[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierIdleLeft");

	_flipbookMove[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierMoveRight");
	_flipbookMove[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierMoveLeft");

	_flipbookAttack[Sight::Right] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierAttackRight");
	_flipbookAttack[Sight::Left] = ResourceManager::GetInstance()->GetFlipbook(L"FB_SoldierAttackLeft");


	CameraComponent* camera = new CameraComponent();
	
	AddComponent(camera);
}

Player::~Player()
{
}

void Player::Init()
{
	Super::Init();
	SetState(PlayerState::Idle);
}

void Player::Update()
{
	Super::Update();
	
	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();

	_sumTime += deltaTime;
	if (_sumTime > _coolTime)
	{
		SetState(PlayerState::Attack);
		if (_sumTime > _coolTime + 0.5f)
		{
			ShootArrow();
			_sumTime = 0.f;
		}
	}
	else
	{
		UpdateDir();
		if (!_keyPressed)
		{
			SetState(PlayerState::Idle);
		}
		else
		{
			SetState(PlayerState::Move);
			if (_dir & (1 << 1))
			{
				_pos.x += 100 * deltaTime;
				_sight = Sight::Right;
			}
			if (_dir & (1 << 2))
			{
				_pos.x -= 100 * deltaTime;
				_sight = Sight::Left;
			}
			if (_dir & (1 << 3))
			{
				_pos.y -= 100 * deltaTime;
			}
			if (_dir & (1 << 4))
			{
				_pos.y += 100 * deltaTime;
			}
		}
	}
	UpdateAnimation();
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::UpdateDir()
{
	uint8 dir = 0;
	if (InputManager::GetInstance()->GetButton(KeyType::D))
	{
		dir |= (1<<1);
	}
	if (InputManager::GetInstance()->GetButton(KeyType::A))
	{
		dir |= (1<<2);
	}
	if (InputManager::GetInstance()->GetButton(KeyType::W))
	{
		dir |= (1<<3);
	}
	if (InputManager::GetInstance()->GetButton(KeyType::S))
	{
		dir |= (1<<4);
	}

	if ((dir & (1<<1) && dir & (1<<2)) || (dir & (1<<3) && (dir & (1<<4))) || dir == 0)
	{
		_keyPressed = false;
		return;
	}
	_keyPressed = true;
	_dir = (Dir)dir;
}

void Player::UpdateAnimation()
{
	
	switch (_state)
	{
	case PlayerState::Idle:
		if (_keyPressed)
			SetFlipbook(_flipbookMove[_sight]);
		else
			SetFlipbook(_flipbookIdle[_sight]);
		break;
	case PlayerState::Move:
		SetFlipbook(_flipbookMove[_sight]);
		break;
	case PlayerState::Attack:
		SetFlipbook(_flipbookAttack[_sight]);
		break;
	}
}

void Player::ShootArrow()
{
	Vec2 mousePos = {};
	mousePos.x = InputManager::GetInstance()->GetMousePos().x;
	mousePos.y = InputManager::GetInstance()->GetMousePos().y;
	Vec2 attackDir = mousePos - Vec2(400,300);

	if (mousePos.x >= _pos.x)
		_sight = Sight::Right;
	else
		_sight = Sight::Left;

	{
		Sprite* sprite = ResourceManager::GetInstance()->GetSprite(L"Arrow");

		Projectile* arrow = new Projectile();
		arrow->SetSprite(sprite);
		arrow->SetLayer(LAYER_PROJECTILE);
		arrow->SetPos(_pos);
		arrow->SetDestPos(mousePos);
		arrow->SetAttackDir(attackDir);
		arrow->SetRotate(arrow->GetAttackDir());

		Scene* scene = SceneManager::GetInstance()->GetCurrentScene();
		scene->AddActor(arrow);
	}
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
