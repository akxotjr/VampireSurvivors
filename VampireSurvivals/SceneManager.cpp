#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "GameScene.h"
#include "LobbyScene.h"
#include "StatUpgradeScene.h"
#include "TitleScene.h"

unique_ptr<SceneManager> SceneManager::instance = nullptr;

void SceneManager::Init()
{

}

void SceneManager::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);
}

//void SceneManager::Clear()
//{
//	//SAFE_DELETE(_scene);
//}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType) return;

	unique_ptr<Scene> newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::DevScene:
		newScene = make_unique<DevScene>();
		break;
	case SceneType::GameScene:
		newScene = make_unique<GameScene>();
		break;
	case SceneType::LobbyScene:
		newScene = make_unique<LobbyScene>();
		break;
	case SceneType::StatUpgradeScene:
		newScene = make_unique<StatUpgradeScene>();
		break;
	case SceneType::TitleScene:
		newScene = make_unique<TitleScene>();
		break;
	}
	
	if(_scene != nullptr)
		_scene->SetFinished();

	_scene = ::move(newScene);
	_sceneType = sceneType;

	_scene->Init();
}
