#include "pch.h"
#include "Orc.h"
#include "ResourceManager.h"

Orc::Orc()
{
	_flipbookIdle = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcIdle");
	_flipbookMove = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcMove");
	_flipbookAttack = ResourceManager::GetInstance()->GetFlipbook(L"FB_OrcAttack");

	//test
	SetPos({ 600,300 });
}

Orc::~Orc()
{
}

void Orc::Init()
{
	Super::Init();
}

void Orc::Update()
{
	Super::Update();
	SetFlipbook(_flipbookAttack);
}

void Orc::Render(HDC hdc)
{
	Super::Render(hdc);
}
