#include "pch.h"
#include "DevScene.h"
#include "Actor.h"
#include "Player.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	shared_ptr<Player> player = make_shared<Player>();
	//AddActor(::move(actor));
	player->Init();
}

void DevScene::Update()
{

}

void DevScene::Render(HDC hdc)
{
}