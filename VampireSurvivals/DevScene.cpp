#include "pch.h"
#include "DevScene.h"
#include "Actor.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	shared_ptr<Actor> actor = make_shared<Actor>();
	AddActor(::move(actor));
}

void DevScene::Update()
{

}

void DevScene::Render(HDC hdc)
{
}