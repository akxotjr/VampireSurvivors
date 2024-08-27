#include "pch.h"
#include "Goblin.h"
#include "ResourceManager.h"

Goblin::Goblin()
{
	_flipbookIdle[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinIdleUp");
	_flipbookIdle[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinIdleDown");
	_flipbookIdle[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinIdleLeft");
	_flipbookIdle[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinIdleRight");

	_flipbookAttack[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinAttackUp");
	_flipbookAttack[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinAttackDown");
	_flipbookAttack[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinAttackLeft");
	_flipbookAttack[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinAttackRight");

	_flipbookMove[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinMoveUp");
	_flipbookMove[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinMoveDown");
	_flipbookMove[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinMoveLeft");
	_flipbookMove[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinMoveRight");

	_flipbookHurt[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinHurtUp");
	_flipbookHurt[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinHurtDown");
	_flipbookHurt[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinHurtLeft");
	_flipbookHurt[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinHurtRight");

	_flipbookDeath[Dir::DIR_UP] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinDeathUp");
	_flipbookDeath[Dir::DIR_DOWN] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinDeathDown");
	_flipbookDeath[Dir::DIR_LEFT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinDeathLeft");
	_flipbookDeath[Dir::DIR_RIGHT] = ResourceManager::GetInstance()->GetFlipbook(L"FB_GoblinDeathRight");
}

Goblin::~Goblin()
{
}

void Goblin::Init()
{
	Super::Init();
}

void Goblin::Update()
{
	Super::Update();
}

void Goblin::Render(HDC hdc)
{
	Super::Render(hdc);
}
