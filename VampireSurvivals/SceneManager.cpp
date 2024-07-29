#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"

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

	//unique_ptr<Scene> newScene = nullptr;
	Scene* newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::DevScene:
		//newScene = make_unique<DevScene>();
		newScene = new DevScene();
		break;
		//case SceneType::EditScene:
		//	newScene = new EditScene();
		//	break;
	}

	_scene = newScene;
	_sceneType = sceneType;

	_scene->Init();
}
